#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <string.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>

void print_f(char*a,char*s,int q,...){
	va_list args;
	va_start (args,q);
	for (int w=0;w<q;++w){
		printf("%i%s",va_arg(args,int),a);
	}
	printf("%s",s);
	va_end(args);
}

void newline(){
	printf("\n");
}

#define print(...) print_f(" ","\n",sizeof((int[]){__VA_ARGS__})/sizeof(int),__VA_ARGS__);
#define print_nn(...) print_f(" ","",sizeof((int[]){__VA_ARGS__})/sizeof(int),__VA_ARGS__);

int input(){
	int q;
	scanf("%i",&q);
	return q;
}

#define list() ((int*)(calloc(4,1))+1)
#define len(n) (*((n)-1))
#define push(n,q) (n)=(int*)(realloc(&len(n),len(n)*4+8))+1;(n)[len(n)++]=q;
#define del(n) free(&len(n));



int main(int argc, char const *argv[])
{
}