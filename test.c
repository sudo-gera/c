#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

void gen(int*a,size_t n,int sum){
    if (n==0){
        printf("%i\n",sum);
        return;
    }
    // for (int i=start;i<8;++i){
    //     p[i]='1';
    //     gen(p,ed-1,i+1);
    //     p[i]='0';
    // }
    gen(a+1,n-1,sum);
    gen(a+1,n-1,sum+a[0]);
}

int main(){
    // char a[9];
    // for (size_t w=0;w<8;++w){
    //     a[w]='0';
    // }
    // a[8]=0;
    // gen(a,3,0);
    int a[4];
    a[0]=1;
    a[1]=7;
    a[2]=3;
    a[3]=14;
    gen(a,4,0);
}
