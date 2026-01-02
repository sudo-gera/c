#!/usr/bin/env bash

if [ $# -ne 1 ]
then
    echo 'expected exactly one arg.'
    exit 1
fi

sock="${1}"

if ! tmux -L "$sock" capture-pane -p >/dev/null 2>/dev/null
then
    echo "no tmux panes at ${sock@Q}."
    exit 1
fi

tmux detach -E "tmux -L ${sock@Q} a"
