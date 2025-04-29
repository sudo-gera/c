docker_name='raft'

min_id=0
max_id=9

function clean(){
    echo
    echo
    echo '                 ' cleaning containers and images
    echo
    echo
    curl 127.0.0.1:2101 --max-time 1 >/dev/null 2>/dev/null &
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

    printf '%s' "$0" |
    realpath "`cat`" |
    dirname  "`cat`" | # find dir of this file
    docker build --progress plain -t "$docker_name" "`cat`"

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
        docker container run --rm -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script -f >(nc 172.30.216.80 9999) -c '/worker.sh $id $(stty size)'" | python3 log_client.py &
        # docker container run --rm -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id" | python3 log_client.py &
    done
    tail -f /dev/null
}

clean
trap clean EXIT
main
