export HISTSIZE=1234567890
export HISTFILESIZE=1234567890
source ~/.zprofile
export PATH=$PATH:~/Library/Python/3.7/bin
if [ $(arch) == arm64 ]
then
    eval "$(/opt/homebrew/bin/brew shellenv)"
else
    eval "$(/usr/local/bin/brew shellenv)"
fi
PATH="$PATH:/Users/gera/Library/Python/3.9/bin:/Users/gera/:.:/opt/homebrew/bin/:/opt/homebrew/Cellar/llvm/*/bin/"
PATH="$PATH:/Users/gera/.local/bin:/Users/gera/Library/Python/3.11/bin:~:."
# alias python=python3
alias port="arch -x86_64 sudo -E port"
export PYTHONSTARTUP="/Users/gera/.pythonrc"
# alias "g++"="/opt/homebrew/bin/g++-13 -std=c++20"
# alias "g++"="/opt/homebrew/Cellar/gcc/12.2.0/bin/g++-13 -std=c++20"
# alias "gcc"="/opt/homebrew/Cellar/gcc/12.2.0/bin/gcc-13"
alias 'gcc'="$(compgen -c | grep -E '^gcc-[0-9]+$' | sort -h | tail -n 1) -std=c2x"
alias 'g++'="$(compgen -c | grep -E '^gcc-[0-9]+$' | sort -h | tail -n 1) -std=c++20"
alias "clang++"="clang++ -std=c++20"
export UBSAN_OPTIONS=print_stacktrace=1
function g(){
    # clang++ -lgmpxx -lgmp -std=c++20 -Ofast -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
    clang++ -std=c++20 -Ofast -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
}
function gg(){
    clang++ -std=c++20 -g -Wfatal-errors -Ofast "$@" && ./a.out "$a_arg_1"
}
function d(){
    clang++ -lgmpxx -lgmp -std=c++20 -Ofast --include /Users/gera/c/d -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
}
function b(){
    clang++ -lgmpxx -lgmp -std=c++20 -Ofast -Dneed_boost --include /Users/gera/c/d -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
}
function c(){
    # clang -lgmp -lgmp -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
    clang -g -fsanitize=address,undefined -fno-sanitize-recover=all -Wfatal-errors "$@" && ./a.out "$a_arg_1"
}
function pas(){
    cp "$1" a.pas
    /Library/Frameworks/Mono.framework/Versions/6.12.0/bin/mono /Users/gera/Downloads/PABCNETC/pabcnetcclear.exe a.pas && /Library/Frameworks/Mono.framework/Versions/6.12.0/bin/mono a.exe "$a_arg_1"
}
alias "scrcpy"="scrcpy --power-off-on-close --turn-screen-off --shortcut-mod \"lalt+lctrl\" --window-title scrcpy"
alias "scrcpyb"="scrcpy -b 400000 --max-fps 8"

# if [ $(arch) = "i386" ]
# then
#   echo "auto switching from x86 to arm, type \x1b[32mexit\x1b[0m to get x86"
#   arch -arm64 zsh
# fi
alias "killself"="kill \$(ps -t \$(tty) -o pid)"
export PATH=$PATH:~/Library/Python/3.7/bin
alias ls='ls -GFC'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias ll='lt -ltr'
function valgrind(){
    scp -P 2222 "$@" 192.168.64.20:~/c/  && ssh -p 2222 -t 192.168.64.20 "cd c && g++ -g -std=c++20 -DREALITY "$@" && valgrind -s --track-origins=yes --leak-check=full ./a.out"

}
function cu(){
    scp -P 2222 "$@" 192.168.64.20:~/c/;

}
function lp(){
    ls "$@" | sed 's,\(.*\),"\1",';
}
export PATH="/opt/homebrew/opt/python@3.10/bin:/opt/homebrew/opt/python@3.10/Frameworks/Python.framework/Versions/3.10/bin:$PATH"

alias "sudo"="sudo /Users/gera/c/sudo.sh ; sudo"

if [[ $ITERM_SESSION_ID =~ w([0-9]+)t([0-9]+)p([0-9]+):* ]];
then
    if [ ${BASH_REMATCH[2]} = 0 ]
    then
        python3.10 -i ~/c/h.py
    fi
fi

export auto_set_proxy=1

[[ -f ~/.bash-preexec.sh ]] && source ~/.bash-preexec.sh
precmd(){
    _last="$?"
    history -a
    if [ "$auto_set_proxy" = "1" ]
    then
        source ~/c/proxy.sh
        if [ $(scselect | awk '{if ($1=="*") print $3}') = "(netshare)" ]
        then
            source ~/c/proxy.sh http://127.0.0.1:8082 socks5h://127.0.0.1:1080
        fi
    fi
    if [ "$_last" == "0" ]
    then
        if [ "$(whoami)" == "root" ]
        then
            PS1="\[\e[34m\]\t\[\e[0m\]:\[\e[33m\]$(arch)\[\e[0m\]:\[\e[32m\]\w\[\e[0m\]# "
        else
            PS1="\[\e[34m\]\t\[\e[0m\]:\[\e[33m\]$(arch)\[\e[0m\]:\[\e[32m\]\w\[\e[0m\]$ "
        fi
    else
        if [ "$(whoami)" == "root" ]
        then
            PS1="\[\e[31m\]\t\[\e[0m\]:\[\e[33m\]$(arch)\[\e[0m\]:\[\e[32m\]\w\[\e[0m\]# "
        else
            PS1="\[\e[31m\]\t\[\e[0m\]:\[\e[33m\]$(arch)\[\e[0m\]:\[\e[32m\]\w\[\e[0m\]$ "
        fi
    fi
}
alias mou="sshfs 192.168.64.20:. ~/ubuntu"
alias umou="umount ~/ubuntu"
alias ssu="ssh 192.168.64.20"
alias moux="sshfs 192.168.64.16:. ~/ubuntux"
alias umoux="umount ~/ubuntux"
alias ssux="ssh 192.168.64.16"


# function ucon(){
#   if (ssh -q -o ConnectTimeout=1 -p 2222 gera@192.168.64.20 exit) 
#   then
#   trap umou EXIT
#       umou 2>/dev/null
#       mou
#       # python3 ~/c/subl_open.py &
#       ssu
#       umou
#   fi
# }

# function uxcon(){
#   if (ssh -q -o ConnectTimeout=1 -p 2222 gera@192.168.64.16 exit) 
#   then
#   trap umoux EXIT
#       umoux 2>/dev/null
#       moux
#       python3 ~/c/subl_open.py &
#       ssux
#       umoux
#   fi
# }

function uxsubl(){
    ssh -R 52698:localhost:52698 -p 2222 192.168.64.16 -t "cd ~/c; bash --login"
}

function alert(){
    if [ $# -lt 1 ]
    then
        osascript -e 'display notification "alert!"'
    else
        osascript -e 'display notification "'$1'"'
    fi
}


function at_exit(){
    if [ $(pwd) == "/Users/gera/c" ]
    then
        nohup gitpush 2>/dev/null >/dev/null &
    fi
}

if ( [ "$TERM_PROGRAM" == "vscode" ] || [ "$TERM_PROGRAM" == "Terminus-Sublime" ] ) && (( code_started==0 ))
then
    code_started=1
    xkbswitch -se US
    precmd
    if [ "$(pwd)" == $'/Users/gera' ]
    then
        cd ~/c
    fi
    trap at_exit EXIT
    PATH="$(echo "$PATH" | sed -e 's/:\/Users\/gera\/.cargo\/bin//')"
    . "$HOME/.cargo/env"
fi
export CEVERYTHING="-Weverything -Werror -Wfatal-errors -Wno-poison-system-directories"
export WEVERYTHING="-Weverything -Werror -Wfatal-errors -Wno-poison-system-directories"

# export LDFLAGS="-L/usr/local/opt/tcl-tk/lib"
# export CPPFLAGS="-I/usr/local/opt/tcl-tk/include"
# export PATH=$PATH:/usr/local/opt/tcl-tk/bin

export BASH_SILENCE_DEPRECATION_WARNING=1
export HISTCONTROL=ignoreboth:erasedups

function n(){
    scp -P 2222 "$@" 192.168.64.16:~/  && ssh -p 2222 -t 192.168.64.16 "nasm -felf "$@" -o a.o && ld -m elf_i386 a.o && ./a.out"
}

function m(){
    scp -P 2222 "$@" 192.168.64.16:~/  && ssh -p 2222 -t 192.168.64.16 "nasm -felf64 "$@" -o a.o && gcc -no-pie a.o && ./a.out"
}

[[ -r "/opt/homebrew/etc/profile.d/bash_completion.sh" ]] && . "/opt/homebrew/etc/profile.d/bash_completion.sh"

transfer(){ if [ $# -eq 0 ];then echo "No arguments specified.\nUsage:\n transfer <file|directory>\n ... | transfer <file_name>">&2;return 1;fi;if tty -s;then file="$1";file_name=$(basename "$file");if [ ! -e "$file" ];then echo "$file: No such file or directory">&2;return 1;fi;if [ -d "$file" ];then file_name="$file_name.zip" ,;(cd "$file"&&zip -r -q - .)|curl --progress-bar --upload-file "-" "https://transfer.sh/$file_name"|tee /dev/null,;else cat "$file"|curl --progress-bar --upload-file "-" "https://transfer.sh/$file_name"|tee /dev/null;fi;else file_name=$1;curl --progress-bar --upload-file "-" "https://transfer.sh/$file_name"|tee /dev/null;fi;echo "";}
export PATH="/opt/homebrew/opt/ruby/bin:$PATH"
function cpp-2022(){
    cd ~/c ; (cmake ~/cpp-2022-sudo-gera && make && ( make test ; $(/bin/ls -1tr ~/c/test_* | tail -n 1 | tee /dev/stderr ) ) ) ; cd -
}

. "$HOME/.cargo/env"
export RUST_BACKTRACE=1

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

export MKL_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1
export OMP_NUM_THREADS=1
function scan_range() { for ip in $(seq 1 255) ; do ( ( ping -ot 1 "$1.$ip" 2>/dev/null >/dev/null && sleep 1 && echo && echo "$1.$ip" ) & ); done; }


function ussh(){
    local port
    port="3"
    port="$port$(head -c 99 /dev/urandom | sum | head -c 1)"
    port="$port$(head -c 99 /dev/urandom | sum | head -c 1)"
    port="$port$(head -c 99 /dev/urandom | sum | head -c 1)"
    port="$port$(head -c 99 /dev/urandom | sum | head -c 1)"
    echo "$port"
    local client_pid
    python ~/udp_over_tcp/client.py --connections 16 --listen 0.0.0.0:"$port" --connect 127.0.0.1:64001 --forward 127.0.0.1:"$port" 2>&1 >/dev/null &
    client_pid="$!"
    mosh -p "$port" --ssh 'ssh -p 2244' localhost -- ssh "$@"
#    kill $(lsof -Plni udp:"$port" | tail -n 1 | sed -E 's/[^0-9]*([0-9]+).*/\1/')
    kill "${client_pid}"
}

