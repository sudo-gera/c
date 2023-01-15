if [ "$TERM_PROGRAM" == "vscode" ]
then
    cd "/mnt/c/Users/..."
fi


function g(){
    clang++ -std=c++20 -O2 -g -fsanitize=address,undefined -Wfatal-errors "$@" && ./a.out
}


