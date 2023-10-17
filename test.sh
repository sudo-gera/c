reader(){
    while :
    do
        IFS=''
        read -rt 1 -n 8 text
        code=$?
        # echo "===$code"
        echo "text is _$text""_"
        if [ $code -eq 0 ]
        then
            echo "got text $text"
        elif [ $code -le 128 ]
        then
            echo "break"
            break
        else
            echo "waiting"
        fi
    done
}

writer(){
    echo "1" | head -c 1
    # sleep 4
    # echo "2" | head -c 1
    # sleep 4
    # echo "3" | head -c 1
    # sleep 4
    # echo "4" | head -c 1
    # sleep 4
    # echo "5" | head -c 1
    # sleep 4
    # echo "6" | head -c 1
    # sleep 4
    echo "7" | head -c 1
    sleep 4
    echo "8++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" | head -c 97
    sleep 4
    echo "9" | head -c 1
    sleep 4
    echo "0" | head -c 1
    sleep 0.5
}

writer > ./fifo &
sleep 1
reader < ./fifo

