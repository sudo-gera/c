#include <unistd.h>
#include <fcntl.h>

int main(int argc,char**argv){
    if (argc!=4){
        return 3;
    }
    int fd1=open(argv[1],O_RDONLY);
    if (fd1==-1){
        return 1;
    }
    int fd2=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
    if (fd2==-1){
        return 2;
    }
    int fd3=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
    if (fd3==-1){
        return 2;
    }
    while (1){
        char data1[1024];
        char data2[1024];
        char data3[1024];
        int data1l=0;
        int data2l=0;
        int data3l=0;
        data1l=read(fd1,data1,1024);
        if (data1l<0){
            return 3;
        }
        if (data1l==0){
            close(fd1);
            close(fd2);
            close(fd3);
            return 0;
        }
        for (int w=0;w<data1l;++w){
            if ('0' <= data1[w] && data1[w] <= '9'){
                data2[data2l++]=data1[w];
            }else{
                data3[data3l++]=data1[w];
            }
        }
        if (data2l){
            if (write(fd2,data2,data2l)<0){
                return 3;
            }
        }
        if (data3l){
            if (write(fd3,data3,data3l)<0){
                return 3;
            }
        }
    }
}