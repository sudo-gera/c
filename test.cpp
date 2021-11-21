#include "d"

<<<<<<< HEAD
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


=======
auto run(int q){
    if (q){
        return run(q-1)+1;
    }
    return 0;
}

ima{
    auto h=run(9);
    print(h);
}
>>>>>>> f551edf2377d4482a52dead0c522256c48ed4aeb
