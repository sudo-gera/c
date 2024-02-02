#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
#include <netdb.h>
#include <sys/socket.h>
 
#include <netinet/in.h>
#include <arpa/inet.h>

#include <assert.h>
 
char *addrtype(int addrtype) {
    switch(addrtype) {
        case AF_INET:
            return "AF_INET";
        case AF_INET6:
            return "AF_INET6";
    }
    return "Unknown";
}
 
int main(int argc, char **argv) {
    struct hostent *tmp = 0;
    int i = 0;
 
    if (argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
 
    const char*host_ip = NULL;
    int q,w,e,r;
    if (sscanf(argv[1], "%d.%d.%d.%d", &q, &w, &e, &r)){
        host_ip = argv[1];
    }
    tmp = gethostbyname(argv[1]);
    // printf("%p\n", tmp);
    // printf("%p\n", &tmp->h_aliases);
    // printf("%p\n", tmp->h_aliases);
    // printf("%p\n", &tmp->h_aliases[0]);
    // printf("%p\n", &tmp->h_aliases[1]);

    if (!tmp) {
        printf("Lookup Failed: %s\n", hstrerror(h_errno));
        return 0;
    }
 
    printf("Lookup: %s\n", argv[0]);
    printf("h_name: %s\n", tmp->h_name);
 
    i = 0;
    while(tmp->h_aliases[i] != NULL) {
        printf("h_aliases[i]: %s\n", tmp->h_aliases[i]);
        i++;
    }
 
    printf("h_addrtype: %d - %s\n", tmp->h_addrtype, addrtype(tmp->h_addrtype));
    printf("h_length: %d\n", tmp->h_length);
     

    assert(tmp->h_addr_list[0]);
    host_ip = inet_ntoa( (struct in_addr) *((struct in_addr *) tmp->h_addr_list[i]));
//     i = 0;
//     while(tmp->h_addr_list[i] != NULL) {
//         printf("h_addr_list[i]: %s\n", inet_ntoa( (struct in_addr) *((struct in_addr *) tmp->h_addr_list[i])));
//         i++;
//     }
 
//     return 0;
// }


// int main(int argc, char *argv[])
// {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001); 

    if(inet_pton(AF_INET, host_ip, &serv_addr.sin_addr)<=0)
    // if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}


