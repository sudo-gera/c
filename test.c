#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

int8_t get_sign;
int get_c;

#define get_int(res)\
{\
    get_sign=1;\
    while (get_c=fgetc(fin),isspace(get_c)){\
    }\
    if (get_c=='-'){\
        get_sign*=-1;\
        res=0;\
    }else{\
        res=get_c-'0';\
    }\
    while (get_c=fgetc(fin),get_c!=EOF and !isspace(get_c)){\
        res*=10;\
        res+=get_c-'0';\
    }\
    res*=get_sign;\
}

char put_data[44];
unsigned long long put_t;
unsigned put_ds;

#define put_int(q)\
{\
    if (q<0){\
        fputc('-',fout);\
        put_t=-q;\
    }else{\
        put_t=q;\
    }\
    put_ds=0;\
    while(put_t){\
        put_data[++put_ds]=put_t%8+(unsigned)('0');\
        put_t/=8;\
    }\
    if (put_ds==0){\
        fputc('0',fout);\
    }\
    for (;put_ds;--put_ds){\
        fputc(put_data[put_ds],fout);\
    }\
}

int main(){
    long q=0;
    FILE * fin = fopen ( "stdin.txt" , "r" ) ;
    FILE * fout = fopen ( "stdout.txt" , "w" ) ;
    get_int ( q ) ; 
    put_int ( q ) ; 
}
