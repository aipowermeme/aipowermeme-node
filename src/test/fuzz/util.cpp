// Copyright (c) 2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/fuzz/util.h>

#include <util/overflow.h>
#include <version.h>

FuzzedSock::FuzzedSock(FuzzedDataProvider& fuzzed_data_provider)
    : m_fuzzed_data_provider{fuzzed_data_provider}
{
    m_socket = fuzzed_data_provider.ConsumeIntegralInRange<SOCKET>(INVALID_SOCKET - 1, INVALID_SOCKET);
}

FuzzedSock::~FuzzedSock()
{
    // Sock::~Sock() will be called after FuzzedSock::~FuzzedSock() and it will call
    // Sock::Reset() (not FuzzedSock::Reset()!) which will call CloseSocket(m_socket).
    // Avoid closing an arbitrary file descriptor (m_socket is just a random very high number which
    // theoretically may concide with a real opened file descriptor).
    Reset();
}

FuzzedSock& FuzzedSock::operator=(Sock&& other)
{
    assert(false && "Move of Sock into FuzzedSock not allowed.");
    return *this;
}

void FuzzedSock::Reset()
{
    m_socket = INVALID_SOCKET;
}

ssize_t FuzzedSock::Send(const void* data, size_t len, int flags) const
{
    constexpr std::array send_errnos{
        EACCES,
        EAGAIN,
        EALREADY,
        EBADF,
        ECONNRESET,
        EDESTADDRREQ,
        EFAULT,
        EINTR,
        EINVAL,
        EISCONN,
        EMSGSIZE,
        ENOBUFS,
        ENOMEM,
        ENOTCONN,
        ENOTSOCK,
        EOPNOTSUPP,
        EPIPE,
        EWOULDBLOCK,
    };
    if (m_fuzzed_data_provider.ConsumeBool()) {
        return len;
    }
    const ssize_t r = m_fuzzed_data_provider.ConsumeIntegralInRange<ssize_t>(-1, len);
    if (r == -1) {
        SetFuzzedErrNo(m_fuzzed_data_provider, send_errnos);
    }
    return r;
}

ssize_t FuzzedSock::Recv(void* buf, size_t len, int flags) const
{
    // Have a permanent error at recv_errnos[0] because when the fuzzed data is exhausted
    // SetFuzzedErrNo() will always return the first element and we want to avoid Recv()
    // returning -1 and setting errno to EAGAIN repeatedly.
    constexpr std::array recv_errnos{
        ECONNREFUSED,
        EAGAIN,
        EBADF,
        EFAULT,
        EINTR,
        EINVAL,
        ENOMEM,
        ENOTCONN,
        ENOTSOCK,
        EWOULDBLOCK,
    };
    assert(buf != nullptr || len == 0);
    if (len == 0 || m_fuzzed_data_provider.ConsumeBool()) {
        const ssize_t r = m_fuzzed_data_provider.ConsumeBool() ? 0 : -1;
        if (r == -1) {
            SetFuzzedErrNo(m_fuzzed_data_provider, recv_errnos);
        }
        return r;
    }
    std::vector<uint8_t> random_bytes;
    bool pad_to_len_bytes{m_fuzzed_data_provider.ConsumeBool()};
    if (m_peek_data.has_value()) {
        // `MSG_PEEK` was used in the preceding `Recv()` call, return `m_peek_data`.
        random_bytes.assign({m_peek_data.value()});
        if ((flags & MSG_PEEK) == 0) {
            m_peek_data.reset();
        }
        pad_to_len_bytes = false;
    } else if ((flags & MSG_PEEK) != 0) {
        // New call with `MSG_PEEK`.
        random_bytes = m_fuzzed_data_provider.ConsumeBytes<uint8_t>(1);
        if (!random_bytes.empty()) {
            m_peek_data = random_bytes[0];
            pad_to_len_bytes = false;
        }
    } else {
        random_bytes = m_fuzzed_data_provider.ConsumeBytes<uint8_t>(
            m_fuzzed_data_provider.ConsumeIntegralInRange<size_t>(0, len));
    }
    if (random_bytes.empty()) {
        const ssize_t r = m_fuzzed_data_provider.ConsumeBool() ? 0 : -1;
        if (r == -1) {
            SetFuzzedErrNo(m_fuzzed_data_provider, recv_errnos);
        }
        return r;
    }
    std::memcpy(buf, random_bytes.data(), random_bytes.size());
    if (pad_to_len_bytes) {
        if (len > random_bytes.size()) {
            std::memset((char*)buf + random_bytes.size(), 0, len - random_bytes.size());
        }
        return len;
    }
    if (m_fuzzed_data_provider.ConsumeBool() && std::getenv("FUZZED_SOCKET_FAKE_LATENCY") != nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds{2});
    }
    return random_bytes.size();
}

int FuzzedSock::Connect(const sockaddr*, socklen_t) const
{
    // Have a permanent error at connect_errnos[0] because when the fuzzed data is exhausted
    // SetFuzzedErrNo() will always return the first element and we want to avoid Connect()
    // returning -1 and setting errno to EAGAIN repeatedly.
    constexpr std::array connect_errnos{
        ECONNREFUSED,
        EAGAIN,
        ECONNRESET,
        EHOSTUNREACH,
        EINPROGRESS,
        EINTR,
        ENETUNREACH,
        ETIMEDOUT,
    };
    if (m_fuzzed_data_provider.ConsumeBool()) {
        SetFuzzedErrNo(m_fuzzed_data_provider, connect_errnos);
        return -1;
    }
    return 0;
}

int FuzzedSock::GetSockOpt(int level, int opt_name, void* opt_val, socklen_t* opt_len) const
{
    constexpr std::array getsockopt_errnos{
        ENOMEM,
        ENOBUFS,
    };
    if (m_fuzzed_data_provider.ConsumeBool()) {
        SetFuzzedErrNo(m_fuzzed_data_provider, getsockopt_errnos);
        return -1;
    }
    if (opt_val == nullptr) {
        return 0;
    }
    std::memcpy(opt_val,
                ConsumeFixedLengthByteVector(m_fuzzed_data_provider, *opt_len).data(),
                *opt_len);
    return 0;
}

bool FuzzedSock::Wait(std::chrono::milliseconds timeout, Event requested, Event* occurred) const
{
    constexpr std::array wait_errnos{
        EBADF,
        EINTR,
        EINVAL,
    };
    if (m_fuzzed_data_provider.ConsumeBool()) {
        SetFuzzedErrNo(m_fuzzed_data_provider, wait_errnos);
        return false;
    }
    if (occurred != nullptr) {
        *occurred = m_fuzzed_data_provider.ConsumeBool() ? requested : 0;
    }
    return true;
}

bool FuzzedSock::IsConnected(std::string& errmsg) const
{
    if (m_fuzzed_data_provider.ConsumeBool()) {
        return true;
    }
    errmsg = "disconnected at random by the fuzzer";
    return false;
}

void FillNode(FuzzedDataProvider& fuzzed_data_provider, CNode& node, bool init_version) noexcept
{
    const ServiceFlags remote_services = ConsumeWeakEnum(fuzzed_data_provider, ALL_SERVICE_FLAGS);
    const NetPermissionFlags permission_flags = ConsumeWeakEnum(fuzzed_data_provider, ALL_NET_PERMISSION_FLAGS);
    const int32_t version = fuzzed_data_provider.ConsumeIntegralInRange<int32_t>(MIN_PEER_PROTO_VERSION, std::numeric_limits<int32_t>::max());
    const bool filter_txs = fuzzed_data_provider.ConsumeBool();

    node.nServices = remote_services;
    node.m_permissionFlags = permission_flags;
    if (init_version) {
        node.nVersion = version;
        node.SetSendVersion(std::min(version, PROTOCOL_VERSION));
    }
    if (node.m_tx_relay != nullptr) {
        LOCK(node.m_tx_relay->cs_filter);
        node.m_tx_relay->fRelayTxes = filter_txs;
    }
}
