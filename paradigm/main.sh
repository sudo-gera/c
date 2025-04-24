#!/bin/bash
set -e

docker_name='paradigm_task'

function clean(){
    echo
    echo
    echo '                  cleaning containers and images'
    echo
    echo

    docker container stop -t 1 "${docker_name}" ||:
    docker container rm "${docker_name}"   ||:

    docker image rm "${docker_name}" ||:
}

clean

cd "$(
    dirname "$(
        realpath "${0}"
    )"
)"

docker build --progress plain -t "${docker_name}" .
docker run -i -t --name "${docker_name}" --mount type=bind,src=.,dst=/host "${docker_name}" "$@"

clean

