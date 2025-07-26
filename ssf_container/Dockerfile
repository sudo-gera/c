FROM --platform=linux/amd64 ubuntu:focal
RUN find /etc -name 'apt.conf' -exec bash -c 'echo '"'"'Acquire::http::Timeout "1";'"'"' >> {}' \;
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

RUN : && \
    apt install -y unzip && \
    :

RUN : && \
    curl -vvv -L -O https://github.com/securesocketfunneling/ssf/releases/download/3.0.0/ssf-linux-x86_64-3.0.0.zip && \
    # curl -vvv -L -O https://github.com/securesocketfunneling/ssf/releases/download/3.0.0/ssf-arm-linux-gnueabihf-3.0.0.zip && \
    mv ssf* zip_ssf.zip && \
    unzip zip_ssf.zip && \
    mv ssf* ssf && \
    :

RUN : && \
    apt install -y libc6-armhf-cross && \
    ln -s /usr/arm-linux-gnueabihf/lib/ld-linux-armhf.so.3 /usr/lib/ld-linux-armhf.so.3 && \
    apt install -y libc-bin && \
    apt install -y libc6-armhf-cross && \
    apt install -y file && \
    :

RUN : && \
    apt-get install -y openssl && \
    :

# RUN : && \
#     cd /ssf && \
#     openssl req -x509 -nodes -newkey rsa:4096 \
#         -keyout './certs/ca.key' \
#         -out './certs/trusted/ca.crt' \
#         -days 36500 \
#         -subj '/C=US/ST=State/L=Locality/O=SSF_CA/OU=Org/CN=SSF Root CA' && \
#     openssl req -newkey rsa:4096 -nodes \
#         -keyout './certs/private.key' \
#         -out './certs/server.csr' \
#         -subj '/C=US/ST=State/L=Locality/O=SSF_CA/OU=Org/CN=SSF Root CA' && \
#     printf 'basicConstraints=CA:FALSE\nkeyUsage=nonRepudiation, digitalSignature, keyEncipherment' > ./certs/extfile.txt && \
#     openssl x509 -req \
#         -in './certs/server.csr' \
#         -CA './certs/trusted/ca.crt' \
#         -CAkey './certs/ca.key' \
#         -CAcreateserial \
#         -out './certs/certificate.crt' \
#         -days 36500 \
#         -extfile './certs/extfile.txt' && \
#     openssl dhparam -out "./certs/dh4096.pem" 4096 && \
#     rm "./certs/extfile.txt" "./certs/server.csr" "./certs/ca.key" "./certs/ca.srl" && \
#     :

RUN cp -r /ssf /ssf_server
RUN cp -r /ssf /ssf_client
RUN rm -r /ssf

COPY ./fix.sh /
RUN chmod +x ./fix.sh && ./fix.sh

RUN rm -r /ssf_server/certs
RUN rm -r /ssf_client/certs
RUN cp -r /certs /ssf_client/certs
RUN cp -r /certs /ssf_server/certs

# RUN : && \
#     (cd /ssf_server && ./ssfd -g &) && \
#     cd /ssf_client && ./ssf 127.0.0.1 && \
#     :


RUN : && \
    mkdir new && cd new && \
    curl -vvv -L -O https://github.com/user-attachments/files/20523626/ssf-linux-x86_64-3.0.0.zip && \
    # curl -vvv -L -O https://github.com/securesocketfunneling/ssf/releases/download/3.0.0/ssf-arm-linux-gnueabihf-3.0.0.zip && \
    mv ssf* zip_ssf.zip && \
    unzip zip_ssf.zip && \
    mv ssf* /ssf && \
    :

RUN : && \
    (cd /ssf && ./ssfd -g &) && \
    cd /ssf && ./ssf 127.0.0.1 && \
    :


