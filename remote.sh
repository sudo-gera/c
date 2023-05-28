tmppipe1="$(mktemp -u)"
tmppipe2="$(mktemp -u)"
mkfifo -m 600 "$tmppipe1"
mkfifo -m 600 "$tmppipe2"
# base64 < "$tmppipe1" > "$tmppipe2" &
function send1(){
    IFS=''
    while read -rn 1 text
    do
        echo "$text" | base64 > "$tmppipe2"
        # tmp="$(echo "$text" | base64)"
        # buff="$buff$tmp"
        # echo "$buff" | wc -m 
        # curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "$text" | base64)"
    done
    echo "----" > "$tmppipe2"
}
function send2(){
    IFS=''
    stop=0
    buff=''
    while [ $stop == 0 ]
    do
        if read -t 0.01 -n 5 text
        then
            if [ "$text" == $'----\n' ]
            then
                stop=1
            else
                buff="$buff$text"
            fi
            curl --noproxy \* http://127.0.0.1:8008/ -d "$(echo "$buff")"
        fi
    done
}
send1 < "$tmppipe1" &
send2 < "$tmppipe2" &
script -F "$tmppipe1"


