#include <sys/syscall.h>
char* syscall(long number, ...);
void _start(){
    long tmp_1=0,tmp_2=0,data_len=0,data_size=0,data_read=0;
    char*data_begin=0,*data_end=0,*tmp=0;
    char*data=syscall(SYS_brk,0);
    do{
        if (data_len == data_size){
            data_size*=2;
            data_size+=123;
            syscall(SYS_brk,data+data_size);
        }
        data_read=(long)syscall(SYS_read,0,data+data_len,data_size-data_len);
        data_len+=data_read;
    }while(data_read);
    if (data_len){
        if (data[data_len-1] != 10){
            data[data_len]=10;
            data_len+=1;
        }
        data_begin=data;
        data_end=data+data_len-1;
        while(data_begin < data_end){
            tmp_1=data_begin[0];
            tmp_2=data_end[0];
            data_begin[0]=tmp_2;
            data_end[0]=tmp_1;
            data_begin+=1;
            data_end-=1;
        }
        data_end=data+data_len-1;
        data_begin=data_end;
        while(data_begin != data){
            if (*(char*)(data_begin) == 10){
                tmp=data_begin;
                while(data_begin < data_end){
                    tmp_1=*(char*)(data_begin);
                    tmp_2=*(char*)(data_end);
                    *(char*)(data_begin)=tmp_2;
                    *(char*)(data_end)=tmp_1;
                    data_begin+=1;
                    data_end-=1;
                }
                data_end=tmp;
                data_begin=data_end;
                data_end-=1;
            }
            data_begin-=1;
        }
        tmp=data_begin;
        while(data_begin < data_end){
            tmp_1=*(char*)(data_begin);
            tmp_2=*(char*)(data_end);
            *(char*)(data_begin)=tmp_2;
            *(char*)(data_end)=tmp_1;
            data_begin+=1;
            data_end-=1;
        }
        loop_last_word_rev_end:
        data_begin=tmp;
        data_end=data_begin;
        syscall(SYS_write,1,data,data_len);
    }
    syscall(SYS_exit,0);
}
