#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int run(int q=1){
    return q;
}

int main(){
    printf("%i",run());
    printf("%i",run(9));
}
