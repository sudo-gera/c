if script --version >/dev/null 2>/dev/null
then
    gnu_head=head
    gnu_cut=cut
    gnu_sed=sed
    gnu_wc=wc
else
    gnu_head=ghead
    gnu_cut=gcut
    gnu_sed=gsed
    gnu_wc=gwc
fi

function free_iface(){
    local port="$1"
    local data="$(`#ssh root@127.0.0.1#` lsof -Pni "$port")"
    if [ -z "$data" ]
    then
        return
    fi
    printf '%s\n' "$data"
    local to_cut="$(printf '%s\n' "$data" | $gnu_head -n 1 | $gnu_sed -E 's?\bPID\b.*?PID?' | $gnu_head -c -1 | $gnu_wc -c)"
    local pids="$(printf '%s\n' "$data" | $gnu_cut -c 1-"$to_cut" | tail -n +2 | $gnu_sed -E 's?.*\b([0-9]+)$?\1?')"
    echo $pids
    `#ssh root@127.0.0.1#` kill $pids
}

port="$1"
if echo "$port" | grep -E 'tcp:|udp:' >/dev/null
then
    free_iface "$port"
else
    free_iface "tcp:$port"
    free_iface "udp:$port"
fi
