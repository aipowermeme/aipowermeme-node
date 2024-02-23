AIPowerMeme Node
=================

Meme have become an integral part of our online culture, providing a lighthearted way to express emotions, opinions, and ideas. With the rise of artificial intelligence (AI), the meme landscape has taken an intriguing turn. AI algorithms have started generating meme, adding a new dimension to the world of humor and creativity.

AIPowerMeme was born includes crypto-savvy tech enthusiasts who geek out over artificial intelligence and can’t resist a good meme chuckle.
With a techy twist and those who are always on the lookout for the next big, quirky investment, AIPowerMeme come.

Quick Start Compile on Ubuntu 18/20
---------------------

See [Ubuntu/Debian Builds](https://github.com/aipowermeme/aipowermeme-node/blob/lata/doc/build-unix.md) or the Docs folder for your platform

Disable QT when building:

```
git clone https://github.com/aipowermeme/aipowermeme-node.git
cd aipowermeme-node
find -name '*.sh' | xargs chmod +x 
chmod +x src/leveldb/build_detect_platform
cd depends 
chmod +x config.guess config.sub gen_id
NO_QT=1 make -j8

cd ..
autoreconf -fi
./configure --disable-tests --disable-bench --without-gui --prefix=`pwd`/depends/x86_64-pc-linux-gnu
make -j8
```

Install on System Start with systemd
--------------------------
In: `/etc/systemd/system/aipowermemed.service `
```
[Unit]
Description=aipowermemed
After=network.target

[Service]
PIDFile=/tmp/aipowermemed-99.pid
ExecStart=/root/aipowermeme-node/src/aipowermemed 

User=root
Group=root
Restart=always
LimitNOFILE=400000
TimeoutStopSec=30min

[Install]
WantedBy=multi-user.target

```

Sample aipowermeme.conf
--------------------------
 
```
rpcallowip=0.0.0.0/0
txindex=1
rpcuser=youruser
rpcpassword=yourpassword

```

## Coin Info
- Coin Name = `AIPowerMeme`
- Ticker = `APME`
- Algorithm = `X11`
- Premine = `100000` (Use for bounties, airdrops, marketing, development fee)
- Maximum Supply = `42100000`

## Block reward structure
- Block reward = `100`
- masternode reward = `27%`
- POW miner block reward = `63%`
- POW Maturity = `51` confirmation
- number of confirmation can be spend = `10` confirmation
- Masternode confirmations = `12` confirmation
- Smartnode Collateral = `1000`

## Website link
- [website](https://aipowermeme.io)

- [block explorer](https://apmeexplorer.net)

- [github](https://github.com/aipowermeme) 

- [wallet](https://github.com/aipowermeme/aipowermeme-source/releases)

- [twitter/x](https://twitter.com/aipowermeme)

## Bitcointalk: 

## Discord
- [discord](https://discord.gg/VS6hUk3cE4)
