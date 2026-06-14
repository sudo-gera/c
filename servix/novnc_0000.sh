export LISTEN_ON='0.0.0.0'

send '(set -x ; export USER="$(whoami)" ; while sleep 1 ; do date ; "$(find ~/noVNC*/ ~/novnc/ -name novnc_proxy | head -n 1)" --listen '"${LISTEN_ON@Q}"':6080 --vnc 127.0.0.1:5900 ; done )'
send '(set -x ; while sleep 1 ; do date ; x11vnc -display ":$(for i in $(seq 0 79) ; do xrandr -q -d :$i 2>/dev/null >/dev/null && echo $RANDOM $i ; done | sort | head -n 1 | awk '"'"'{print $2}'"'"' | tee /dev/stderr ~/vnc_display.txt)" -shared -dontdisconnect -many -listen '"${LISTEN_ON@Q}"' ; done )'
