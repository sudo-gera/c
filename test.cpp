#include "d"

void q(int64_t w){
    printf("int64_t%i",w);
}

// void q(int w){
//     printf("int64_t");
// }

// #ifdef L
// void q(long w){
//     printf("long");
// }
// #endif



int main(){
    auto g=q;
    auto h=(void*)(g);
    auto j=decltype(g)(h);
}


