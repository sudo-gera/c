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

dirs_escaped_lf_joined="$(find . -mindepth 1 -maxdepth 1 -type d -exec bash -c 'echo "${0@Q}"' {} \;)"

echo "$dirs_escaped_lf_joined" | \
while read -r path_1_escaped
do
    path_1="$(bash -c "printf '%s\n' $path_1_escaped")"
    name_1="$(basename "$path_1" | $gnu_sed -E 's?_based_on_.*??g')"
    echo "$dirs_escaped_lf_joined" | \
    while read -r path_2_escaped
    do
        path_2="$(bash -c "printf '%s' $path_2_escaped")"
        if [ "$path_1" != "$path_2" ]
        then
            if printf '%s' "$path_2" | grep -- "$name_1" >/dev/null
            then
                echo
                echo
                echo
                echo
                echo "Comparing ${path_1@Q} and ${path_2@Q}"
                echo
                diff --recursive -q "$path_1" "$path_2" || :
            fi
        fi
    done
done


