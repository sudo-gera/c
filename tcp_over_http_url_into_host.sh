#!/usr/bin/env bash

set -xeuo pipefail

server_url="$1"
server_key="$2"
server_alias="$3"



ssh -p "${port}" 127.0.0.1 -oHostKeyAlias="${random_host}"
