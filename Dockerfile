<<<<<<< HEAD

FROM ubuntu:latest

# RUN apt update && \
#     apt upgrade -y && \
#     apt install -y python3 python3-pip clang cmake gcc git && \
#     pip3 install flask && \
#     rm -rf /var/lib/apt/lists/*

RUN echo "123"

CMD echo "456"
=======
FROM ubuntu:latest

RUN apt update &&\
    apt upgrade -y &&\
    apt install -y python3 python3-pip clang cmake gcc git &&\
    pip3 install flask && \
    rm -rf /var/lib/apt/lists/*



>>>>>>> 13bc93bc3633e4c71d443c4647ebed0ce0ca3ecf


