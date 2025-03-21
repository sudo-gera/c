FROM ubuntu:focal
RUN bash -e -c 'apt update ; apt install -y nano'
RUN apt install -y wget curl
RUN apt install -y software-properties-common 
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get install -y gcc-13 g++-13
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 60 --slave /usr/bin/g++ g++ /usr/bin/g++-13
RUN apt-get install -y tmux
RUN apt-get install -y netcat
RUN apt-get install -y iptables
RUN apt-get install -y traceroute
RUN apt-get install -y net-tools
RUN bash -c "echo $'*filter\n:INPUT ACCEPT [7:488]\n:FORWARD ACCEPT [0:0]\n:OUTPUT ACCEPT [4:424]\nCOMMIT' >> enable_net.sh"
RUN bash -c "echo $'*filter\n:INPUT ACCEPT [7:488]\n:FORWARD ACCEPT [0:0]\n:OUTPUT ACCEPT [4:424]\n-A INPUT -p tcp -m tcp --dport 7777 -j DROP\nCOMMIT' >> disable_net.sh"
# RUN bash -c 'iptables-save > enable'
# RUN bash -c 'iptables -P INPUT DROP ; iptables-save > disable'
# these commands would be cached and would not run again for each source change


# all commands below would run again for each source change
COPY . .
# RUN g++ -std=c++20 -g -fsanitize=address,undefined -Ofast -Wall -Wextra -Werror -Wfatal-errors *.cpp
# RUN bash -c 'tmux new ; tmux send -l 'mkfifo fifo ; ((script -qf fifo -c "nc -kl 9999" )&) ; ((bash -s < fifo)&)'
# CMD bash -c 'mkfifo fifo ; ((script -qf fifo -c "nc -kl 9999" )&) ; ((bash -s < fifo)&) ; bash'
# CMD [ "bash" , "-c" , "\' mkfifo fifo ; (( script -q -f fifo -c \'\\"\'\\"\'nc -kl 9999\'\\"\'\\"\' )&) ; (( bash -s < fifo )&) ; bash\'" ]
CMD [ "bash" , "-c" , "mkfifo fifo ; (( script -q -f fifo -c 'nc -kl 9999' )&) ; (( (echo Iw== | base64 -d ; cat fifo) | bash -x )&) ; bash" ]
# CMD [ "bash" , "-c" , "mkfifo fifo ; (( script -q -f fifo -c ':|nc -kl 9999' )&) ; (( (echo Iw== | base64 -d ; tee < fifo) | base64 > log )&) ; bash" ]
