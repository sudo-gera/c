#!/usr/bin/env bash

set -euo pipefail

python3 ~/tcpexec.py --host 127.0.0.1 --port _ -- "$@"
