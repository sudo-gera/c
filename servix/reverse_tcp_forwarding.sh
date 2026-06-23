r=$RANDOM
echo ___ > ~/.reverse_tcp_forwarding_first_4_bytes_$r
mv ~/.reverse_tcp_forwarding_first_4_bytes_$r ~/.reverse_tcp_forwarding_first_4_bytes
this_file="${BASH_SOURCE[0]}"
this_file_abs="$(
    realpath -- "$this_file"
)"
this_dir="$(
    dirname -- "$this_file_abs"
)"
send '(set -x ; eval "$(tmux display-message -p "#{session_name}" | tr "^-" ".\n")" ; while sleep 1 ; do date ; '"${this_dir@Q}"'/../reverse_tcp_forwarding6 --mode $mode --connection_timeout 300 --max_accepted_sockets_per_server 200 --max_connected_sockets 200 --first_bytes_filename ~/.reverse_tcp_forwarding_first_4_bytes --internal_port $internal_port --internal_host $internal_host --external_port $external_port --external_host $external_host --clock_interval 1 ; done )'