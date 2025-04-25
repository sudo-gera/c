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
RUN add-apt-repository -y ppa:deadsnakes/ppa
RUN apt update
RUN apt install -y python3.11-full
RUN mkfifo fifo && \
    tmux new -d && \
    tmux send -l 'script -f fifo' && \
    tmux send C-m && \
    sleep 0.1 && \
    tmux send -l 'python3.11 -m ensurepip && python3.11 -m pip install psutil && exit' && \
    tmux send C-m && \
    sleep 0.1 && \
    (while sleep 0.3 ; do tmux send C-m ; done & ) && \
    cat fifo
RUN apt install -y ncat
# these commands would be cached and would not run again for each source change


# all commands below would run again for each source change
COPY . .
# RUN g++ -std=c++20 -g -fsanitize=address,undefined -Ofast -Wall -Wextra -Werror -Wfatal-errors *.cpp
