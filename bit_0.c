#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int a,s;
    scanf("%x %x", &a, &s);
    return a^s;
}
