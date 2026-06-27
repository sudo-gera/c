#!/usr/bin/env bash
set -xEeuo pipefail

PREFLEN=30
LOCAL=10.240.128.2
PEER=10.240.128.1
SOCKS=127.0.0.1:1080
UDPGW=127.0.0.1:7300
LOGLEVEL=info

DEV=badvpntun${RANDOM}
while ip link show "${DEV}" >& /dev/null
do
    DEV=badvpntun${RANDOM}
done

usage() {
    cat <<EOF
Usage: $0 [options]

Options:
  -t DEV        TUN device name (default is some random non-existent interface)
  -n PREFLEN    peer-to-peer virtual network prefix len (default: $PREFLEN)
  -l a.b.c.d    IP for local tun (default: $LOCAL)
  -p e.f.g.h    IP for tun2socks virtual router (default: $PEER)
  -s IP:PORT    SOCKS5 server, required to be IP not hostname (default: $SOCKS)
  -u IP:PORT    UDPGW server relative to socks5 server (default: $UDPGW)
  -v LEVEL      Log level (0-5/none/error/warning/notice/info/debug) (default: $LOGLEVEL)
  -h            Show this help
EOF
}

while getopts ":t:n:l:p:s:u:v:h" opt; do
    case "$opt" in
        t) DEV=$OPTARG ;;
        n) PREFLEN=$OPTARG ;;
        l) LOCAL=$OPTARG ;;
        p) PEER=$OPTARG ;;
        s) SOCKS=$OPTARG ;;
        u) UDPGW=$OPTARG ;;
        v) LOGLEVEL=$OPTARG ;;
        h)
            usage
            exit 0
            ;;
        :)
            echo "Missing argument for -$OPTARG" >&2
            usage >&2
            exit 1
            ;;
        \?)
            echo "Unknown option: -$OPTARG" >&2
            usage >&2
            exit 1
            ;;
    esac
done

main() {
    local MASK="$(
        m=$(( 2**32 - 2**32 / 2**${PREFLEN} ))
        echo "$(( m >> 24 & 255 )).$(( m >> 16 & 255 )).$(( m >> 8 & 255 )).$(( m & 255 ))"
    )"

    socks_route="$(
        printf 'echo %s %s %s %s %s\n#' $(ip route get "${SOCKS%:*}") | bash -$-
    )"

    trap 'set +e ; ip link delete "$DEV" ; ip route del ${socks_route}' EXIT

    ip route add ${socks_route}

    ip tuntap add dev "${DEV}" mode tun
    ip addr add "${LOCAL}/${PREFLEN}" dev "${DEV}"
    ip link set "${DEV}" up
    ip route add 0.0.0.0/1 via "${PEER}" dev "${DEV}"
    ip route add 128.0.0.0/1 via "${PEER}" dev "${DEV}"

    # runs in foreground
    # expects TUN to be created and does not clear it on exit
    badvpn-tun2socks \
        --logger stdout \
        --loglevel "${LOGLEVEL}" \
        --tundev "${DEV}" \
        --netif-ipaddr "${PEER}" \
        --netif-netmask "${MASK}" \
        --socks-server-addr "${SOCKS}" \
        --udpgw-remote-server-addr "${UDPGW}"

    # tun2socks was stopped, cleaning ifaces by calling trapped cleanup
}

main
