#!/usr/bin/env bash
# Copyright (c) 2018-2020 The Dash Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
# use testnet settings,  if you need mainnet,  use ~/.aipowermeme/aipowermemed.pid file instead
export LC_ALL=C

aipowermeme_pid=$(<~/.aipowermeme/testnet3/aipowermemed.pid)
sudo gdb -batch -ex "source debug.gdb" aipowermemed ${aipowermeme_pid}
