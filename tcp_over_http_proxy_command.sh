#!/usr/bin/env bash

set -xeuo pipefail

server_url="$1"

ssh 'tee | ( port=$(( $RANDOM %% 20000 + 20000 )) ; python3 ~/c/tcp_over_http_client.py --http-url '"'"'%h'"'"' --tcp-host 127.0.0.1 --tcp-port $port & p=$! ; sleep 1 ; trap "kill $p" EXIT ; nc 127.0.0.1 $port ) | tee'