export LISTEN_ON='127.0.0.1'

send 'export USER="$(whoami)" ; while sleep 1 ; do date ; "$(printf %s\\n%s\\n ~/noVNC* | head -n 1)"/utils/novnc_proxy --listen '"${LISTEN_ON@Q}"':6080 --vnc 127.0.0.1:5900 ; done'
send 'while sleep 1 ; do date ; x11vnc -display ":$(for i in $(seq 0 79) ; do xrandr -q -d :$i 2>/dev/null >/dev/null && echo $RANDOM $i ; done | sort | head -n 1 | awk '"'"'{print $2}'"'"' | tee /dev/stderr ~/vnc_display.txt)" -shared -dontdisconnect -many -listen '"${LISTEN_ON@Q}"' ; done'
