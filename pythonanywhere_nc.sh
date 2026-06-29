#!/usr/bin/env bash
set -Eeuo pipefail

this_file="$(realpath -- "$0")"
this_dir="$(dirname -- "$this_file")"
cd "$this_dir"

python3 slow_pipe.py 16384 \
    | python3 line_by_line_b64.py encode ">>> " \
    | python3 pythonanywhere.py "$@" \
    | grep --line-buffer "<<<" \
    | python3 line_by_line_b64.py decode "<<< "