#include "d"

void q(int64_t w){
    printf("int64_t");
}

void q(int w){
    printf("int64_t");
}

#ifdef LONG_
void q(long w){
    printf("long");
}
#endif

int main(){
    q(long(0));
    printf("\n");
}


