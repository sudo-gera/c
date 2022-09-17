#!/bin/bash

IFS=":"
while read -r func
do
    for mpath in $MANPATH
    do
        fpath=$(find $mpath -name "$func.3*" | head -1)
        if [ -n "$fpath" ]
        then
            break
        fi
    done

    if [ -n "$fpath" ]
    then
        if [ $(echo $fpath | tail -c -3) = "gz" ]
        then
            include_string=$(gunzip -c $fpath | grep '\#include' | head -1)
        else
            include_string=$(cat $fpath | grep '\#include' | head -1)
        fi
        include_file=$(echo $include_string | sed -r 's/.*include <(.*)>. */\1/g')
        echo $include_file
        echo "---"
    fi
done

