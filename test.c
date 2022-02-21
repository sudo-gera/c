#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(){
	uint64_t* q=(uint64_t*)malloc(sizeof(uint64_t));
	printf("%llx\n",*q);
}
