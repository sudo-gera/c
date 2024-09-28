function a(){
    start="$(date +%s)"
    ssh -o=ConnectionAttempts=1 -o=ServerAliveCountMax=1 -oServerAliveInterval=1 -p 2255 localhost -N
    stop="$(date +%s)"
    echo "data[$start]=$stop"
}

echo 'data={}'
pids=''
while sleep 6
do
    a &
    pids="$pids $!"
done
kill $pids

