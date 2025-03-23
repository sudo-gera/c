set -e
docker_name='integral'

min_id=0
max_id=4

function clean(){
    echo
    echo
    echo '                 ' cleaning containers and images
    echo
    echo
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

clean

printf '%s' "$0" |
realpath "`cat`" |
dirname  "`cat`" | # find dir of this file
docker build --progress plain -t "$docker_name" "`cat`"

for id in $(seq $max_id $min_id)
do
    # if [ $id -eq $min_id ]
    # then
    #     docker container run --rm -i -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script >(nc 172.30.216.80 900$id) -c '/worker.sh $id'"
    # else
    #     docker container run --rm -d    --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "script >(nc 172.30.216.80 900$id) -c '/worker.sh $id'"
    # fi
    if [ $id -eq $min_id ]
    then
        docker container run --rm -i -t --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id"
    else
        docker container run --rm -d    --cap-add=NET_ADMIN --name "${docker_name}_${id}" "$docker_name" bash -c "/worker.sh $id"
    fi
done

clean
