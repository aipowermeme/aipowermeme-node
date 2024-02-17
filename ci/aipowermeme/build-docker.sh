#!/usr/bin/env bash
# Copyright (c) 2021-2022 The Dash Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"/../.. || exit

DOCKER_IMAGE=${DOCKER_IMAGE:-aipowermemepay/aipowermemed-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}
DOCKER_RELATIVE_PATH=contrib/containers/deploy

if [ -d $DOCKER_RELATIVE_PATH/bin ]; then
    rm $DOCKER_RELATIVE_PATH/bin/*
fi

mkdir $DOCKER_RELATIVE_PATH/bin
cp "$BASE_ROOT_DIR"/src/aipowermemed    $DOCKER_RELATIVE_PATH/bin/
cp "$BASE_ROOT_DIR"/src/aipowermeme-cli $DOCKER_RELATIVE_PATH/bin/
cp "$BASE_ROOT_DIR"/src/aipowermeme-tx  $DOCKER_RELATIVE_PATH/bin/
strip $DOCKER_RELATIVE_PATH/bin/aipowermemed
strip $DOCKER_RELATIVE_PATH/bin/aipowermeme-cli
strip $DOCKER_RELATIVE_PATH/bin/aipowermeme-tx

docker build --pull -t "$DOCKER_IMAGE":"$DOCKER_TAG" -f $DOCKER_RELATIVE_PATH/Dockerfile docker
