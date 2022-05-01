#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>


int main(){
	int*a=(int*)calloc(1024,sizeof(int));
	#define left --a;
	#define right ++a;
	#define inc ++*a;
	#define dec --*a;
	#define get getchar(*a);
	#define put putchar(*a);
	#define begin while(*a){
	#define end }

	inc
	inc
	inc
	begin
		right
		inc
		inc
		inc
		inc
		left
		dec
	end
	right
	begin
		right
		inc
		inc
		inc
		inc
		left
		dec
	end
	right
	put

}
