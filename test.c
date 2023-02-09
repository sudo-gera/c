#include <stdio.h>

long long unsigned gcd(long long unsigned q,long long unsigned w){
    return q?gcd(w%q,q):w;
}

int main(){
    long long unsigned a=0,s=0;
    scanf("%llu%llu",&a,&s);
    if (gcd(a,s)==1){
        printf("nice\n");
    }else{
        printf("not nice\n");
    }
}









