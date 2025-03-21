docker_name='integral'

docker container stop "$docker_name"
docker container rm "$docker_name"
docker image rm "$docker_name"

printf '%s' "$0" |
realpath "`cat`" |
dirname  "`cat`" | # find dir of this file
docker build --progress plain -t "$docker_name" "`cat`"
docker container run --rm -i -t --cap-add=NET_ADMIN --name "$docker_name" "$docker_name"

docker container stop "$docker_name"
docker container rm "$docker_name"
docker image rm "$docker_name"
