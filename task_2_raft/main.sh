docker_name='raft'

min_id=0
worker_count=2
max_id=$((
    $worker_count
        +
    1 `# client #`
        +
    1 `# network_manager #`
        -
    1
))

function clean(){
    echo
    echo
    echo '                 ' cleaning containers and images
    echo
    echo
    for q in $(seq 1 80)
    do
        printf $'\x1b[s\x1b[999B\x1b['"$q"$'C#\x1b[u'
        sleep 0.1
    done &
    curl 127.0.0.1:2101 --max-time 1 >/dev/null 2>/dev/null &
    curl 127.0.0.1:2102 --max-time 1 >/dev/null 2>/dev/null &
    for id in $(seq $min_id $max_id)
    do
        (
            (
                docker container stop -t 1 "${docker_name}_${id}" ||:
                docker container rm "${docker_name}_${id}"   ||:
            )&
        )
    done | tee

    docker image rm "$docker_name" ||:
}

function main(){
    set -e

    cd "$(
        printf '%s' "$0" |
        realpath "`cat`" |
        dirname  "`cat`" # find dir of this file
    )"

    docker build --progress plain -t "$docker_name" .

    python3 log_server.py &
    local log_server_pid="$!"

    for id in $(seq $max_id $min_id)
    do
        # if [ $id -eq $min_id ]
        # then
        #     docker container run --rm -i -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script -f >(nc 172.30.216.80 9999) -c '/worker.sh $id'"
        # else
        #     docker container run --rm -d    --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script -f >(nc 172.30.216.80 9999) -c '/worker.sh $id'"
        # fi
        # if [ $id -eq $min_id ]
        # then
        #     docker container run --rm -i -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id"
        # else
        #     docker container run --rm -d    --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id"
        # fi
        # docker container run --rm -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script -f >(nc 172.30.216.80 9999) -c '/worker.sh $id'" &
        docker container run --rm -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script -f >(nc 172.30.216.80 9999) -c '/worker.sh $id $(stty size) $worker_count'" | python3 log_client.py &
        # docker container run --rm -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id" | python3 log_client.py &
    done
    nc -l 2102
    # tail -f /dev/null
}

clean
trap clean EXIT
main
