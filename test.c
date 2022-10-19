#include <stdio.h>
#include <limits.h>

int main(){
    int e=INT_MIN;
    int r=-1;
    r=e%r;
    printf("%i\n",r);
}