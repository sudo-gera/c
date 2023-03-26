function installation(){
    echo -e "\x1b[95mnote:\x1b[93m if asked override or not, type n and hit <enter>\x1b[0m"
    echo -e "\x1b[95mnote:\x1b[93m if asked for passphrase, hit <enter> for empty passphrase\x1b[0m"
    ssh-keygen -qf ~/.ssh/id_rsa_for_nasm
    echo -e "\x1b[95mnote: in next commands password is password (if asked)\x1b[0m"
    ssh-copy-id -i ~/.ssh/id_rsa_for_nasm user@192.168.64.21
    ssh-copy-id -i ~/.ssh/id_rsa_for_nasm exec@192.168.64.21
    scp user@192.168.64.21:./nasm.sh ~/
    echo -e "\x1b[92mnice! now you can run \x1b[94m~/nasm.sh\x1b[92m command!\x1b[0m"
}
installation

