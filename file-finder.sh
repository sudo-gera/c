#!/usr/bin/env bash
if (( $# != 2 ))
then
    echo "usage: $0 /path/to/dir filetype"
    exit 1
fi

workpath=$1
worktype=$2


while read -r -d '' file
do
    types=$(file "$file" | tr "[:upper:]" "[:lower:]" | rev | sed -E "s/([^:]*)(:.*)?/\1/" | rev | sed -E "s/([^,]*)(,.*)?/\1/")
    IFS=' '
    for type in $types
    do
        if [ "$type" = "$worktype" ]
        then
            echo "$file"
            break
        fi
    done
done < <(find "$workpath" -print0) > "$worktype".txt
