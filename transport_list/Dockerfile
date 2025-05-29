FROM ubuntu:focal
RUN apt update && apt install -y nano curl tmux wget gcc && \
    (mkfifo fifo||:) && \
    tmux new -d && \
    tmux send -l 'script -f fifo' && \
    tmux send C-m && \
    sleep 0.1 && \
    tmux send -l 'rm -f /ok ; ( curl https://sh.rustup.rs -sSf | sh ) && touch /ok ; exit' && \
    tmux send C-m && \
    sleep 0.1 && \
    (while sleep 0.3 ; do tmux send C-m ; done & ) && \
    cat fifo && \
    [ -f /ok ]
COPY . /