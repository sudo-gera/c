// #include "h"
#include <stdio.h>
<<<<<<< HEAD
#include <stdint.h>
=======
>>>>>>> 46dfc180cdf64f10001a635345392471cd765bfb


void run(int q){
	printf("%li",sizeof(q));
}

void run(int64_t q){
	printf("%li",sizeof(q));
}

#ifdef L
void run(long q){
	printf("%li",sizeof(q));
}
#endif

int main(){
	run((long)0);

}
