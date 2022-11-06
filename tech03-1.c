#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc,char**argv){
    int fd1=open(argv[1],O_RDONLY);
    if (fd1<0){
        return 1;
    }
    while (1){
        struct Item t;
        uint64_t readlen=0;
        while (readlen<t){
            int len=read(fd1,readlen+(char*)(&t),sizeof(t)-readlen);
            if (len<=0){
                break;
            }
            readlen+=len;            
        }
        printf("%i\n",t.value);
        if (t.next_pointer){
            lseek(fd1,t.next_pointer,SEEK_SET);
        }else{
            break;
        }
    }
    close(fd1);
    return 0;

}