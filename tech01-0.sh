#!/bin/bash
function readman(){
    if [ $0 == *.gz ]
    then
        echo $0 "has gz"
    else
        echo $0 "has no gz"
    fi
}


IFS=":"
for w in $MANPATH
{
    # w="$w/man3"
    for e in /**/*
    {
        if [ -f $e ]
        then
            echo "++$e++"
            # echo $e
        else
            echo "--$e--"
        fi
    }
    # find $w -exec readman "{}" \;
    IFS=":"
}