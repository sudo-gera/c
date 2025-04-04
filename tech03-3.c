#if defined(_WIN32)
#define open _open
#define read _read
#define write _write
#define lseek _lseek
#endif

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
#include <unistd.h>
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
    uint64_t c=0;
    while (1){
        struct Item t;
        int64_t readlen=0;
        while (1){
            int64_t len=read(fd1,readlen+(char*)(&t),sizeof(t)-readlen);
            if (len==0){
                break;
            }
            if (len<=0){
                goto end;
            }
            readlen+=len;            
        }
        if (c++ < 64 and readlen==0){
            break;
        }
        printf("%i\n",t.value);
        if (t.next_pointer){
            lseek(fd1,t.next_pointer,SEEK_SET);
        }else{
            break;
        }
    }
    end:
    close(fd1);
    return 0;

}