#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5001); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
<<<<<<< HEAD

    listen(listenfd, 10); 
=======
    if (errno){
        perror("");
        fflush(stderr);
        fflush(stdout);
    }

    listen(listenfd, 10); 
    if (errno){
        perror("");
        printf("%li\n",__LINE__);
        fflush(stderr);
        fflush(stdout);
    }
>>>>>>> 95fb96e1154f703ab88a92a647e59415b646e6fe

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
<<<<<<< HEAD
	printf("got client\n");
=======
    if (errno){
        perror("");
        printf("%li\n",__LINE__);
        fflush(stderr);
        fflush(stdout);
    }
>>>>>>> 95fb96e1154f703ab88a92a647e59415b646e6fe

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 
<<<<<<< HEAD

        close(connfd);
=======
    if (errno){
        perror("");
        printf("%li\n",__LINE__);
        fflush(stderr);
        fflush(stdout);
    }

        close(connfd);
    if (errno){
        perror("");
        printf("%li\n",__LINE__);
        fflush(stderr);
        fflush(stdout);
    }
>>>>>>> 95fb96e1154f703ab88a92a647e59415b646e6fe
        sleep(1);
     }
}
