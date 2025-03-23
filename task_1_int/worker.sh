#!/bin/bash

set -x

node_id="$1"
if [ "$node_id" -eq '0' ]
then
    is_master=1
else
    is_master=0
fi

system_hash="$(sum /a.out)" # to identify nodes of this system
echo "system_hash=${system_hash@Q}"

network_prefix=172.17.0
min_last_ip_num=0
max_last_ip_num=8

this_ip="$(ifconfig | grep 'inet ' | grep "$network_prefix" | tr ' ' '\n' | grep "$network_prefix")"

##############################################################################################################################
# setup `worker_nodes` list

if [ "$is_master" -eq 0 ]
then
    (
        (
            while :
            do
                echo "$system_hash" | nc -l 2001 |:
            done
        )&
    )
    (
        (
            while :
            do
                echo "$this_ip" | nc -l 2002 |:
            done
        )&
    )
else
    sleep 4
    for last_ip_num in $(seq $min_last_ip_num $max_last_ip_num)
    do
        if  :|
            nc "${network_prefix}.${last_ip_num}" 2001 2>/dev/null|
            grep "$system_hash" 2>/dev/null >/dev/null
        then
            :|nc "${network_prefix}.${last_ip_num}" 2002 2>/dev/null >> worker_nodes
        fi
    done
    worker_nodes="$(cat worker_nodes)"
fi

##############################################################################################################################
# setup `nc -l 9999 | bash`

mkfifo fifo
(
    (
        script -q -f fifo -c 'nc -kl 9999'
    )&
)
(
    (
        (
            echo Iw== | base64 -d
            cat fifo
        ) | bash -x
    )&
)

##############################################################################################################################
# setup `network disabler`

if [ $is_master -eq 1 ]
then
    (
        (
            set +x
            while sleep 0.2
            do
                worker_ip="$(echo "$worker_nodes" | head -n "$(( 1 + $RANDOM % "$(echo "$worker_nodes" | wc -l)" ))" | tail -n 1)"
                filename="${worker_ip}_has_net"
                if [ $(( $RANDOM % 4 )) -eq 0 ]
                then
                    command=' : ; /enable_net.sh ; : '
                    if ! [ -f "$filename" ]
                    then
                        echo ">>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> sending ${command@Q} to ${worker_ip@Q}"
                    fi
                    touch "$filename"
                else
                    command=' : ; /disable_net.sh ; : '
                    if [ -f "$filename" ]
                    then
                        echo ">>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> sending ${command@Q} to ${worker_ip@Q}"
                    fi
                    rm -f "$filename"
                fi
                echo "$command" | nc $worker_ip 9999 | :
            done
        )&
    )
else
    /disable_net.sh
fi

##############################################################################################################################
# main code

if [ $is_master -eq 1 ]
then
    # /a.out 0 172.17.0.2 4444 172.17.0.3 4444 172.17.0.4 4444 172.17.0.5 4444
    /a.out "$is_master" $(echo "$worker_nodes" | sed -E 's?(.*)?\1 4444 ?' | tr -d '\n')
else
    # /a.out 1 0.0.0.0 4444
    /a.out "$is_master" 0.0.0.0 4444
fi
