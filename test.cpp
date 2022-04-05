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


int main(){
	while (1){
		int q=int(rand()%4)*"\x01\xff"[rand()%2];
		int w=int(rand()%4)*"\x01\xff"[rand()%2];
		print(q,w,bin_repr(q),bin_repr(w),bin_repr(q/w),bin_repr((unsigned&)(q)/(unsigned&)(w)))
	}
}
