tmppipe1="$(mktemp -u)"
tmppipe2="$(mktemp -u)"
mkfifo -m 600 "$tmppipe1"
mkfifo -m 600 "$tmppipe2"
function send1(){
    IFS=''
    while read -rn 1 text
    do
        echo "$text" | base64 | head -c 4 > "$tmppipe2"
    done
    echo "^^^^" > "$tmppipe2"
}
function send2(){
    IFS=''
    stop=0
    buff=''
    while [ $stop == 0 ]
    do
        send=1
        if read -t 2 -n 4 text
        then
            send=0
            if [ "$text" == $'^^^^' ]
            then
                stop=1
                send=1
            fi
            buff="$buff $text"
        fi
        if [ $send == 1 ]
        then
            if [ -n "$buff" ]
            then
                curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "$buff")"
                buff=''
            fi
            sleep 1
        fi
    done
}
function recv(){
    while :
    do
        curl -s --noproxy \* http://127.0.0.1:8008/
    done
}
send1 < "$tmppipe1" &
send2 < "$tmppipe2" &
recv &
script -F "$tmppipe1"


