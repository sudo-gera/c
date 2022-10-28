#include <unistd.h>
#include <fcntl.h>
// #include <stdio.h>
// #include <ctype.h>
// #include <inttypes.h>
// #include <iso646.h>
// #include <stdarg.h>
// #include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <tgmath.h>
// #include <stddef.h>
// #include <sys/mman.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <fcntl.h>


#define size 0
#if size==1
typedef uint8_t shu;
uint32_t C0[256];
uint32_t C1[256];
uint32_t C2[256];
uint32_t C3[256];
#else
typedef uint16_t shu;
uint32_t C0[65536];
uint32_t C1[65536];
#endif

void fast_sort(int A,int B,uint64_t n){
    uint32_t buffer[102400];
    uint64_t bb=0,be=0;
    lseek(A,0,SEEK_SET);
	for(uint64_t i=0;i!=n;++i){
        if (bb==be){
            bb=0;
            be=read(A,buffer,sizeof(buffer))/4;
        }
        uint32_t t=buffer[bb++];
		++C0[ ((shu*)&t)[0] ];
		++C1[ ((shu*)&t)[1] ];
		#if size==1
		++C2[ ((shu*)&t)[2] ];
		++C3[ ((shu*)&t)[3] ];
		#endif
	}
	for (unsigned j=1;j<sizeof(C0)/sizeof(C0[0]);++j){
		C0[j] += C0[j-1];
		C1[j] += C1[j-1];
		#if size==1
		C2[j] += C2[j-1];
		C3[j] += C3[j-1];
		#endif
	}
    lseek(A,0,SEEK_SET);
    bb=be=0;
	for (uint64_t i=0;i!=n;++i){
        if (bb==be){
            bb=0;
            be=read(A,buffer,sizeof(buffer))/4;
        }
        uint32_t t=buffer[bb++];
		uint64_t y=--C0[ ((shu*)&t)[0] ];
        lseek(B,(n-1-y)*4,SEEK_SET);
        write(B,&t,sizeof(t));
	}
    lseek(B,0,SEEK_SET);
    bb=be=0;
	for (uint64_t i=0;i!=n;++i){
        if (bb==be){
            bb=0;
            be=read(B,buffer,sizeof(buffer))/4;
        }
        uint32_t t=buffer[bb++];
		uint64_t y= --C1[ ((shu*)&t)[1] ];
	    #if size==1
        lseek(A,(n-1-y)*4,SEEK_SET);
        write(A,&t,sizeof(t));
        #else
        lseek(A,y*4,SEEK_SET);
        write(A,&t,sizeof(t));
        #endif
	}
	#if size==1
    lseek(A,0,SEEK_SET);
    bb=be=0;
	for (uint64_t i=0;i!=n;++i){
        if (bb==be){
            bb=0;
            be=read(A,buffer,sizeof(buffer))/4;
        }
        uint32_t t=buffer[bb++];
		uint64_t y = --C2[ ((shu*)&t)[2] ];
        lseek(B,(n-1-y)*4,SEEK_SET);
        write(B,&t,sizeof(t));
	}
    lseek(B,0,SEEK_SET);
    bb=be=0;
	for (uint64_t i=0;i!=n;++i){
        if (bb==be){
            bb=0;
            be=read(B,buffer,sizeof(buffer))/4;
        }
        uint32_t t=buffer[bb++];
		uint64_t y= --C3[ ((shu*)&t)[3] ];
        lseek(A,y*4,SEEK_SET);
        write(A,&t,sizeof(t));
	}
	#endif
	#undef size
}



int main(int argc,char**argv){
    if (argc==1){
        return 0;
    }
    int fd1=open(argv[1],O_RDWR);
    int fd2=open("tmp.txt",O_RDWR|O_CREAT);
    uint64_t filelen=0;
    while(1){
        char c[102400];
        int len=read(fd1,c,sizeof(c));
        if (len==0){
            break;
        }
        write(fd2,c,len);
        filelen+=len;
    }
    unsigned n=filelen/4;
    fast_sort(fd1,fd2,n);
    close(fd1);
    close(fd2);
    return 0;
}