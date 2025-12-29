#!/usr/bin/env bash

set -e -x -u -o pipefail

session=_${RANDOM}_${RANDOM}_${RANDOM}_${RANDOM}_

tmux new -ds "$session"
sleep 1
tmux resize-window -t "$session" -x 200 -y 9999
sleep 1


tmux send -t "$session" -l $'ssh -i ~/home-network-node/base/.ssh/id_ed25519 -J mrr.nya.pub:55748 runner@127.0.0.1 -p 32827\n'
sleep 4

tmux send -t "$session" -l $'bash -x -l\n'
sleep 1
tmux send -t "$session" -l $'echo "export PS1=${PS1@Q}"\n'
sleep 1
tmux send -t "$session" -l $'echo "export TERM=${TERM@Q}"\n'
sleep 1
tmux send -t "$session" -l $'echo "export SHELL=${SHELL@Q}"\n'
sleep 1
tmux send -t "$session" -l $'exit\n'
sleep 1

tmux send -t "$session" -l $'bash -x\n'
sleep 1
tmux send -t "$session" -l $'echo "export PS1=${PS1@Q}"\n'
sleep 1
tmux send -t "$session" -l $'echo "export TERM=${TERM@Q}"\n'
sleep 1
tmux send -t "$session" -l $'echo "export SHELL=${SHELL@Q}"\n'
sleep 1
tmux send -t "$session" -l $'exit\n'
sleep 1

tmux capture -S- -pet "$session"

tmux send -t "$session" -l $'exit\n'
sleep 1

tmux send -t "$session" -l $'exit\n'
sleep 1

tmux send -t "$session" -l $'exit\n'
sleep 1

tmux send -t "$session" -l $'exit\n'
sleep 1

tmux send -t "$session" -l $'exit\n'
sleep 1

