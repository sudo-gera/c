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

this_ip="$(ifconfig | grep 'inet ' | grep "$network_prefix" | tr ' ' '\n' | grep "$network_prefix")"

##############################################################################################################################
# setup `worker_nodes` list

if [ "$is_master" -eq 0 ]
then
    (
        (
            while :
            do
                echo '@@@@@@@@@@@@@@'
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
    for last_ip_num in $(seq 0 10)
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

if [ $is_master -eq 1 ]
then
    (
        (
            while :
            do
                worker_ip="$(echo "$worker_nodes" | head -n "$(( 1 + $RANDOM % "$(echo "$worker_nodes" | wc -l)" ))" | tail -n 1)"
                if [ $(( $RANDOM % 4 )) -eq 0 ]
                then
                    command=': ; /disable_net.sh ; ifconfig | grep inet ; :'
                else
                    command=': ; /disable_net.sh ; ifconfig | grep inet ; :'
                fi
                echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> sending ${command@Q} to ${worker_ip@Q}"
                echo "$command" | nc $worker_ip 9999 | :
            done
        )&
    )
fi

if [ $is_master -eq 1 ]
then
    /a.out "$is_master" $(echo "$worker_nodes" | sed -E 's?(.*)?\1 4444 ?' | tr -d '\n')
else
    /a.out "$is_master" 0.0.0.0 4444
fi
