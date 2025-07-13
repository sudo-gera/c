#!/usr/bin/env bash

set -e

session_name=acc

while tmux -L service kill-pane -t "$session_name" 2>/dev/null
do sleep 0.01
done

function send(){
    if tmux -L service capture-pane -pet "$session_name" >/dev/null 2>/dev/null
    then
        tmux -L service new-window   -t "$session_name"
    else
        tmux -L service new-session -ds "$session_name"
    fi
    sleep 0.01
    tmux -L service send-keys    -t "$session_name" -l "$1"$'\n'
}

conf_dir="$(realpath ~/rem_acc/)"

rm -rf "${conf_dir}"
mkdir -p "${conf_dir}"

temp_file="${conf_dir}/${RANDOM}"

echo 'Host *' >> "$temp_file"
echo '    StrictHostKeyChecking no' >> "$temp_file"
echo '    UserKnownHostsFile /dev/null' >> "$temp_file"
echo '    ServerAliveInterval 15' >> "$temp_file"
echo '    ExitOnForwardFailure yes' >> "$temp_file"
echo '    ConnectTimeout 8' >> "$temp_file"
echo '    ConnectionAttempts 1' >> "$temp_file"
echo '    PasswordAuthentication no' >> "$temp_file"

[[ -f ~/.ssh/id_ed25519 ]] || ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N '' -q
cat ~/.ssh/id_ed25519.pub

send 'while sleep 1 ; do date ; ssh -vvv -F '"${temp_file@Q}"' -J gera@cs.mipt.ru:55748                     gera@s1145.vdi.mipt.ru -N -R 127.0.0.1:$(( $RANDOM % 1000 + 42000 )):127.0.0.1:22 ; done'
send 'while sleep 1 ; do date ; ssh -vvv -F '"${temp_file@Q}"' -J gera@mipt-client.atp-fivt.org:22          gera@s1145.vdi.mipt.ru -N -R 127.0.0.1:$(( $RANDOM % 1000 + 42000 )):127.0.0.1:22 ; done'
send 'while sleep 1 ; do date ; ssh -vvv -F '"${temp_file@Q}"' -J gera.tatarinov.999@lorien.atp-fivt.org:22 gera@s1145.vdi.mipt.ru -N -R 127.0.0.1:$(( $RANDOM % 1000 + 42000 )):127.0.0.1:22 ; done'
