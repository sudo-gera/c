#!/usr/bin/env bash

tee | ( echo socks5h 127.0.0.1 20705 "$@" ; tee ) | nc 127.0.0.1 31173
