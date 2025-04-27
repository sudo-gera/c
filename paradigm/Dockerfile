FROM ubuntu:jammy
RUN apt update && \
    apt install -y curl nano tmux tree && \
    mkfifo fifo && \
    tmux new -d && \
    tmux send -l 'script -f fifo' && \
    tmux send C-m && \
    sleep 0.1 && \
    tmux send -l 'curl https://sh.rustup.rs -sSf | sh ; exit' && \
    tmux send C-m && \
    sleep 0.1 && \
    (while sleep 0.3 ; do tmux send C-m ; done & ) && \
    cat fifo
RUN apt-get install -y gcc
CMD ln -sf /host/bash_history /root/.bash_history && bash
