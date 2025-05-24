#!/usr/bin/env bash

set -e

cd "$(
    dirname "$(
        realpath "${0}"
    )"
)"

if script --version >/dev/null 2>/dev/null
then
    gnu_sed='sed'
else
    gnu_sed='gsed'
fi

test_paths_escaped_lf_joined="$(find . -mindepth 2 -maxdepth 2 -name 'test_all.sh' -exec bash -c 'echo "${0@Q}"' {} \;)"

printf '%s\n' "$test_paths_escaped_lf_joined" | \
while read -r test_path_escaped
do
    test_path="$(bash -c "printf '%s\n' $test_path_escaped")"
    "$test_path" || exit 1
done


