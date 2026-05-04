send '( set -x ; while sleep 1 ; do date ; for pver in 13 12 11 10 ; do python3.$pver ~/c/line_proxy.py --listen-host 127.0.0.1 --listen-port 20124 ; done ; done )'
