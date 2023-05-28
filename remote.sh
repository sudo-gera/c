tmppipe1="$(mktemp -u)"
tmppipe2="$(mktemp -u)"
mkfifo -m 600 "$tmppipe1"
mkfifo -m 600 "$tmppipe2"
# base64 < "$tmppipe1" > "$tmppipe2" &
function send1(){
    IFS=''
    while read -rn 1 text
    do
        echo "$text" | base64 | head -c 4 > "$tmppipe2"
        # tmp="$(echo "$text" | base64)"
        # buff="$buff$tmp"
        # echo "$buff" | wc -m 
        # curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "$text" | base64)"
    done
    echo "1234" > "$tmppipe2"
}
function send2(){
    IFS=''
    stop=0
    buff=''
    while [ $stop == 0 ]
    do
        read -t 1 -n 4 text
        # curl --noproxy \* http://127.0.0.1:8008/ -d "$text"
        if read -t 1 -n 4 text
        then
            if [ "$text" == $'1234' ]
            then
                stop=1
            else
                buff="$buff$text"
            fi
            if [ "$(echo "$buff" | wc -c)" -ge 4096 ]
            then
                curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "2222$buff")"
                buff=''
            fi
        else
            if [ -n "$buff" ]
            then
                curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "1111$buff")"
                buff=''
            fi
        fi
    done
}
send1 < "$tmppipe1" &
send2 < "$tmppipe2" &
script -F "$tmppipe1"


