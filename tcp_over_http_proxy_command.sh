#!/usr/bin/env bash

set -xeuo pipefail

encoded_server_host="$1"

mkdir ~/.ssh

json="$(
    printf '%s\n' "${encoded_server_host}" | tr '.' '\n' | head -n 1 | base64 -d | base64 -d
)"

printf '%s\n' "${json}" | jq .line_for_known_hosts | sed "s?_tcp_over_http_host_placeholder_?${encoded_server_host}?g" >> ~/.ssh/known_hosts

url="$(printf '%s\n' "${json}" | jq .url)"

chmod 600 ~/.ssh/known_hosts

port=$(( $RANDOM % 20000 + 20000 ))

python3 ~/c/tcp_over_http_client.py --http-url "${url}" --tcp-host 127.0.0.1 --tcp-port "${port}" &
p=$!

trap "kill $p" EXIT

nc 127.0.0.1 "${port}"
