#!/usr/bin/env bash

set -xeuo pipefail

cd "$(
    dirname -- "$(
        realpath -- "${0}"
    )"
)"


for q in $(seq 0 99)
do
    while true
    do
        mkdir -p "__task__/${q}"
        python3 task_gen.py > "__task__/${q}/test.c"
        gcc -o "__task__/${q}/original_task.exe" "__task__/${q}/test.c"

        # check that both lines occur in binary.
        if ! grep -q 'ACCESS GRANTED' "__task__/${q}/original_task.exe"
        then
            continue
        fi

        if ! grep -q 'WRONG PASSWORD' "__task__/${q}/original_task.exe"
        then
            continue
        fi
        
        python3 solution.py < "__task__/${q}/original_task.exe" > "__task__/${q}/reversed_task.exe"
        chmod +x "__task__/${q}/reversed_task.exe"

        # check that original task reject password and modified accepts it.
        if ! [ "$( "__task__/${q}/original_task.exe" <<< 'password' )" = 'WRONG PASSWORD' ]
        then
            continue
        fi

        if ! [ "$( "__task__/${q}/reversed_task.exe" <<< 'password' )" = 'ACCESS GRANTED' ]
        then
            continue
        fi

        break # task is done and solvable

    done

done


