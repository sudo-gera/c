#!/usr/bin/env bash

tee | ( echo socks5h 127.0.0.1 23160 "$@" ; tee ) | nc 127.0.0.1 20124
