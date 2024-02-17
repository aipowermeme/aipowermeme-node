# syntax = edrevo/dockerfile-plus

FROM ubuntu:focal

INCLUDE+ ci/Dockerfile

# The inherited Dockerfile switches to non-privileged context and we've
# just started configuring this image, give us root access
USER root

# Make development environment more standalone
RUN apt-get update && \
    apt-get install $APT_ARGS \
    apt-cacher-ng \
    gdb \
    gpg \
    lsb-release \
    nano \
    openssh-client \
    screen \
    sudo \
    zsh \
    && \
    rm -rf /var/lib/apt/lists/*

# Discourage root access, this is an interactive instance
#
# Sometimes these commands are run repetitively _after_ the non-sudo
# user was introduced and therefore these commands would fail
# To mitigate the build halting, you can add "|| true" so that it
# unconditionally returns 0
#
# Also, we create the group `docker` and add our user to it to meet
# Gitian's requirements
#
RUN groupadd docker && \
    usermod -aG sudo,docker aipowermeme && \
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Disable noninteractive mode
ENV DEBIAN_FRONTEND="dialog"

# Expose AIPowerMeme P2P and RPC ports for main network and test networks
EXPOSE 16099 9999 26099 26100

# We're done, switch back to non-privileged user
USER aipowermeme
