tmppipe1="$(mktemp -u)"
tmppipe2="$(mktemp -u)"
mkfifo -m 600 "$tmppipe1"
mkfifo -m 600 "$tmppipe2"
# base64 < "$tmppipe1" > "$tmppipe2" &
function send(){
    while read -rn 1 text
    do
        echo "$text" | base64
    done
}
send < "$tmppipe1" &
script -F "$tmppipe1"


