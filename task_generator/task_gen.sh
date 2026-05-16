#!/usr/bin/env bash

set -xeuo pipefail

cd "$(
    dirname -- "$(
        realpath -- "${0}"
    )"
)"


for q in $(seq 0 99)
do
    mkdir -p "__task__/${q}"
    python3 task_gen.py > "__task__/${q}/test.c"
    gcc -o "__task__/${q}/original_task.exe" "__task__/${q}/test.c"
    python3 solution.py --always-accept < "__task__/${q}/original_task.exe" > "__task__/${q}/reversed_task.exe"
    python3 solution.py --invert < "__task__/${q}/original_task.exe" > "__task__/${q}/reversed_task.exe"
    gcc -o "__task__/${q}/reversed_task.exe"
done


