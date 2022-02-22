export PATH=$PATH:~/Library/Python/3.7/bin
autoload -U colors && colors
PS1="%{$fg[red]%}%D{%T}%{$reset_color%}:%{$fg[yellow]%}$(arch)%{$reset_color%}:%{$fg[green]%}%~%{$reset_color%}$ "
PATH="$PATH:/Users/gera/Library/Python/3.9/bin:/Users/gera/:.:"
alias port="arch -x86_64 sudo port"
export PYTHONSTARTUP="/Users/gera/.pythonrc"
alias "g++"="/opt/homebrew/Cellar/gcc/11.2.0_3/bin/g++-11 -std=c++23"
# alias "g++"="g++ -std=c++17"
alias "gcc"="/opt/homebrew/Cellar/gcc/11.2.0_3/bin/gcc-11"
function b(){
	clang++ -std=c++11 -g -fsanitize=address,undefined -Wfatal-errors $@ && ./a.out
}
function g(){
	clang++ -std=c++17 -g -fsanitize=address,undefined -Wfatal-errors $@ && ./a.out
}
function d(){
	clang++ -std=c++17 --include /Users/gera/c/d -g -fsanitize=address,undefined -Wfatal-errors $@ && ./a.out
}
function c(){
	gcc -Wfatal-errors $@ && ./a.out
}
function pas(){
	cp $1 a.pas
	/Library/Frameworks/Mono.framework/Versions/6.12.0/bin/mono /Users/gera/Downloads/PABCNETC/pabcnetcclear.exe a.pas && /Library/Frameworks/Mono.framework/Versions/6.12.0/bin/mono a.exe
}
alias "scrcpy"="(adb connect 192.168.49.1:53142 ; scrcpy --power-off-on-close --turn-screen-off --shortcut-mod \"lalt+lctrl\" --window-title scrcpy &) && (python ~/scrcpy-input.py/scrcpy-input.py scrcpy &)"
alias "scrcpyb"="scrcpy -b 400000 --max-fps 8"

if [ $(arch) = "i386" ]
then
	echo "auto switching from x86 to arm, type \x1b[32mexit\x1b[0m to get x86"
	arch -arm64 zsh
fi
alias "killself"="kill \$(ps -t \$(tty) -o pid)"
export PATH=$PATH:~/Library/Python/3.7/bin
alias ls='ls -GFC'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias ll='lt -ltr'
function valgrind(){
	scp -P 2222 $@ 192.168.64.20:~/c/  && ssh -p 2222 -t 192.168.64.20 "cd c && g++ -g -std=c++17 -DREALITY $@ && valgrind -s --track-origins=yes --leak-check=full ./a.out"

}
function cu(){
	scp -P 2222 $@ 192.168.64.20:~/c/;

}
function lp(){
	ls $@ | sed 's,\(.*\),"\1",';
}
export PATH="/opt/homebrew/opt/python@3.10/bin:/opt/homebrew/opt/python@3.10/Frameworks/Python.framework/Versions/3.10/bin:$PATH"

alias "sudo"="sudo /Users/gera/c/sudo.sh;sudo"

if [ "$(tty)" = "/dev/ttys000" ]
then
	python3 -i ~/c/h.py
fi


precmd(){
	# echo "starting precmd"
	if ((precmd_lock))
	then
		# echo "already locked"
	else
		# echo "locking"
		((precmd_lock=1))
		((precmd_locked=1))
	fi
	fc -W
	export ftp_proxy="";
	export FTP_PROXY="";
	export http_proxy="";
	export HTTP_PROXY="";
	export https_proxy="";
	export HTTPS_PROXY="";
	export socks_PROXY="";
	export SOCKS_PROXY="";
	export socks4_PROXY="";
	export SOCKS4_PROXY="";
	export socks5_PROXY="";
	export SOCKS5_PROXY="";
	if [ $(scselect | awk '{if ($1=="*") print $3}') = "(netshare)" ]
	then
		hp="8080"
		sp="1080"
		export ftp_proxy="http://192.168.49.1:$hp";
		export FTP_PROXY="http://192.168.49.1:$hp";
		export http_proxy="http://192.168.49.1:$hp";
		export HTTP_PROXY="http://192.168.49.1:$hp";
		export https_proxy="http://192.168.49.1:$hp";
		export HTTPS_PROXY="http://192.168.49.1:$hp";
		export socks_PROXY="http://192.168.49.1:$sp";
		export SOCKS_PROXY="http://192.168.49.1:$sp";
		export socks4_PROXY="http://192.168.49.1:$sp";
		export SOCKS4_PROXY="http://192.168.49.1:$sp";
		export socks5_PROXY="http://192.168.49.1:$sp";
		export SOCKS5_PROXY="http://192.168.49.1:$sp";
	fi
	# echo "stopping precmd"
	if ((precmd_locked))
	then
		# echo "disabling lock"
		((precmd_lock=0))
		((precmd_locked=0))
	fi
}
alias mou="sshfs -p 2222 192.168.64.20:. ~/ubuntu"
alias umou="umount ~/ubuntu"
alias ssu="ssh -p 2222 192.168.64.20"


function ucon(){
	if (ssh -q -o ConnectTimeout=1 -p 2222 gera@192.168.64.20 exit) 
	then
	trap umou EXIT
		umou 2>/dev/null
		mou
		python3 ~/c/subl_open.py &
		ssu
		umou
	fi
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
	nohup gitpush 2>/dev/null >/dev/null &
}

if [ $TERMINUS_SUBLIME ]
then
	precmd
	cd ~/c
	trap at_exit EXIT
fi
# export CEVERYTHING="-Weverything -Werror -Wfatal-errors -Wno-poison-system-directories"
export EVERYTHING="-Weverything -Werror -Wfatal-errors -Wno-poison-system-directories"

# export LDFLAGS="-L/usr/local/opt/tcl-tk/lib"
# export CPPFLAGS="-I/usr/local/opt/tcl-tk/include"
# export PATH=$PATH:/usr/local/opt/tcl-tk/bin
