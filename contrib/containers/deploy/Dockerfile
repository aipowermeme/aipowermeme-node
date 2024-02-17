FROM phusion/baseimage:focal-1.0.0
LABEL maintainer="AIPowerMeme Developers <dev@aipowermeme.org>"
LABEL description="Dockerised AIPowerMeme, built from Travis"

ARG USER_ID
ARG GROUP_ID

ENV HOME /home/aipowermeme

# add user with specified (or default) user/group ids
ENV USER_ID ${USER_ID:-1000}
ENV GROUP_ID ${GROUP_ID:-1000}
RUN groupadd -g ${GROUP_ID} aipowermeme && \
    useradd -u ${USER_ID} -g aipowermeme -s /bin/bash -m -d /home/aipowermeme aipowermeme && \
    mkdir /home/aipowermeme/.aipowermeme && \
    chown ${USER_ID}:${GROUP_ID} -R /home/aipowermeme

COPY bin/* /usr/local/bin/

RUN chmod a+x /usr/local/bin/*

USER aipowermeme

VOLUME ["/home/aipowermeme"]

EXPOSE 16099 9999 26099 26100

WORKDIR /home/aipowermeme
