FROM ubuntu:latest

RUN apt update &&\
    apt upgrade -y &&\
    apt install -y python3 python3-pip flask clang cmake gcc git &&\
    rm -rf /var/lib/apt/lists/*





