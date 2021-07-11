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


const int end=10000000;
int primes[end];

int main(int argc, char const *argv[])
{
	primes[0]=2;
	primes[1]=3;
	primes[2]=5;
	int primes_len=3;
	int e,b,p;
	int q=primes[primes_len-1]+2;
	int o=-1;
	long double g;
	long long int i=sqrt(end)*end*end;
	printf("%011i\n",end);
	for (int w=0;primes_len<end;++w){
		if (w%1000000==0){
			printf("%011i\r",primes_len);
			fflush(stdout);
		}
		b=0;
		for(e=0;primes[e]*primes[e]<=q;++e){
			if (q%primes[e]==0){
				b=1;
				break;
			}
		}
		if (!b){
			primes[primes_len++]=q;
		}
		q+=2;
	}
	// unsigned char* primes_char=(unsigned char*)(primes);
	FILE*v=fopen("/Users/gera/primes.txt","w");
	// for (int w=0;w<primes_len*4;w+=4){
	// 	fprintf(v,"'");
	// 	fprintf(v,"%02x",(unsigned int)(primes_char[w+3]));
	// 	fprintf(v,"%02x",(unsigned int)(primes_char[w+2]));
	// 	fprintf(v,"%02x",(unsigned int)(primes_char[w+1]));
	// 	fprintf(v,"%02x",(unsigned int)(primes_char[w+0]));
	// 	fprintf(v,"'\n");
	// }
	fprintf(v,"[");
	for (int w=0;w<primes_len;++w){
		fprintf(v,"%i%s",primes[w],w+1==primes_len?"":",");
	}
	fprintf(v,"]\n");
}