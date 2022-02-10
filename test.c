#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

void gen(char*p,int ed,int start){
    if (ed==0){
        printf("%s\n",p);
        return;
    }
    for (int i=start;i<8;++i){
        p[i]='1';
        gen(p,ed-1,i+1);
        p[i]='0';
    }
}

int main(){
    char a[9];
    for (size_t w=0;w<8;++w){
        a[w]='0';
    }
    a[8]=0;
    gen(a,3,0);
}
