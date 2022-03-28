#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

int run(uint32_t q,uint32_t w,uint32_t e,uint32_t r){
	printf("%x\n",q);
	printf("%x\n",w);
	printf("%x\n",e);
	printf("%x\n",r);
}


int main(){
	int (*p)();
	p=run;
	p((uint64_t)(0x1234567887654321));
}
