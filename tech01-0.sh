

while read cf
do
    for w in $(echo $MANPATH | sed "s/:/\n/g")
    {
        w="$w/man3"
        if [ -d $w ]
        then
            for e in $(find $w | grep "$cf")
            {
                echo "$e"


                # if [ "$e" == "$w/$cf"* ]
                # then
                #     if [ -f $e ]
                #     then
                #         if [[ $e == *".gz" ]]
                #         then
                #             echo "1 $e"
                #             rf=$(cat $e | gunzip)
                #         else
                #             echo "2 $e"
                #             rf=$(cat $e)
                #         fi
                #         echo "$rf"
                #         echo ""
                #         echo ""
                #         echo ""
                #         echo ""
                #     fi
                # fi
            }
        fi
    }
done