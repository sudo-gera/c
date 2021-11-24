// #include "h"
#include <stdio.h>


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
