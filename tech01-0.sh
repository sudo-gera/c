#!/bin/bash
# function readman(){
#     if [ $0 == *.gz ]
#     then
#         echo $0 "has gz"
#     else
#         echo $0 "has no gz"
#     fi
# }


for w in $(echo $MANPATH | sed "s/:/\n/g")
{
    w="$w/man3"
    if [ -d $w ]
    then
        for e in $(find $w | grep memcmp)
        {
            if [ -f $e ]
            then
                echo $e
            fi
        }
    fi
}