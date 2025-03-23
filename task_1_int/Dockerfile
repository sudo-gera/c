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
# these commands would be cached and would not run again for each source change


# all commands below would run again for each source change
COPY . .
RUN g++ -std=c++20 -g -fsanitize=address,undefined -Ofast -Wall -Wextra -Werror -Wfatal-errors *.cpp
