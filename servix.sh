#!/usr/bin/env bash

set -e -u -o pipefail

command="$1"
service_file="$2"

service_name="$(
        basename "$service_file" | rev | tr -d '\n' | tr '.' $'\n' | tail -n +2 | tr '\n' '.' | rev
)"

if [[ "$command" != 'start' ]] && [[ "$command" != 'restart' ]] && [[ "$command" != 'stop' ]] && [[ "$command" != 'fg-start' ]] && [[ "$command" != 'fg-restart' ]] && [[ "$command" != 'fg-stop' ]]
then
    echo 'Unknown command'
    exit 1
fi

if [[ "$command" == 'start' ]]
then
    tmux -L service new-session -d -s "$service_name" 2>/dev/null
fi

service_path="$(
        realpath "$service_file"
)"

if ! [[ -f "$service_path" ]]
then
    echo "File $service_path not found"
    exit 1
fi

if grep 'new-session' "$service_path"
then
    exit 1
fi

if [[ "${command:0:3}" != 'fg-' ]]
then
    ses="_${RANDOM}_${RANDOM}_${RANDOM}_${RANDOM}"
    tmux -Lindependent new -ds "$ses"
    tmux -Lindependent send-keys -t "$ses" -l "${0@Q} 'fg-'${command@Q} ${service_path@Q}; exit"$'\n'
    exit
fi

if [[ "$command" != 'fg-start' ]]
then
    while tmux -L service kill-pane -t "$service_name"
    do sleep 0.2
    done
fi

if [[ "$command" == 'fg-stop' ]]
then
    exit
fi

if [[ "$command" != 'fg-start' ]]
then
    tmux -L service new-session -d -s "$service_name" 2>/dev/null
fi

function send(){
    tmux -L service new-window   -t "$service_name"
    sleep 0.01
    tmux -L service send-keys    -t "$service_name" -l "$1"$'\n'
}

source "$service_path"
