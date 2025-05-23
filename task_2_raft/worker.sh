#!/bin/bash

# set -x

node_id="$1"
height="$2"
width="$3"
worker_count="$4"

network=172.17.0.0/24

if [ "$node_id" -eq 0 ]
then
    sleep 8
    python3.11 network_manager.py "$height" "$width" $(python3.11 print_hosts.py "$network" 2100 "$worker_count") &
else
    if [ "$node_id" -eq 1 ]
    then
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>'
        python3.11 print_hosts.py "$network" 2100 "$worker_count" > hosts.txt
        echo "$(python3.11 print_colored_ip.py $(cat hosts.txt))" $'\x02'
        python3.11 solution.py $(cat hosts.txt) &
    else
        python3.11 command_executor.py &
        python3.11 print_hosts.py "$network" 2100 "$worker_count" > hosts.txt
        echo "$(python3.11 print_colored_ip.py $(cat hosts.txt))" $'\x02'
        while sleep 0.1
        do
            if [ -f /work ]
            then
                python3.11 log_prefix.py '+++++++++++++++++++++ started working +++++++++++++++++++++' $(cat hosts.txt)
                python3.11 solution.py $(cat hosts.txt)
                python3.11 log_prefix.py '--------------------- stopped working ---------------------' $(cat hosts.txt)
            else
                tail -f //dev/null
            fi
        done &

        # python3.11 log.py $(cat hosts.txt) &
        # tmux new -d
        # tmux resize-pane -x 200
        # tmux send -l $'script -f >(while sleep 0.3 ; do nc 127.0.0.1 2102 ; done)\n'
        # sleep 0.1
        # tmux send -l $'python3.11 print_hosts.py "127.0.0.1" 2102 1\n'
        # tmux send -l $'date\n'
        # tmux send -l $'python3.11 solution.py $(cat hosts.txt)\n'
    fi
fi
tail -f /dev/null
