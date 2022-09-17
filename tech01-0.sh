

while read cf
do
    for w in $(echo $MANPATH | sed "s/:/\n/g")
    {
        w="$w/man3"
        if [ -d $w ]
        then
            for e in $(find $w | grep $cf)
            {
                if [ -f $e ]
                then
                    if [[ $e == *".gz" ]]
                    then
                        rf=$(cat $e | gunzip)
                    else
                        rf=$(cat $e)
                    fi
                    echo $rf
                    echo ""
                    echo ""
                    echo ""
                    echo ""
                fi
            }
        fi
    }
done