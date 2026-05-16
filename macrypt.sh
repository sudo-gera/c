#!/usr/bin/env bash

set -x

for q in $(seq 0 99)
do
    mkdir -p "__task__/${q}"
    python3 macrypt.py > "__task__/${q}/test.c"
done


