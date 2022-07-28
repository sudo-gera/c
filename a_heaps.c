#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

#define array(t,n) ((t*)malloc(sizeof(t)*(n)))
#define c_array(t,a,n) t*a=array(t,(n));

#define get_int(res)\
{\
	get_sign=1;\
	while (get_c=getchar_unlocked(),isspace(get_c)){\
	}\
	if (get_c=='-'){\
		get_sign*=-1;\
		res=0;\
	}else{\
		res=get_c-'0';\
	}\
	while (get_c=getchar_unlocked(),get_c!=EOF and !isspace(get_c)){\
		res*=10;\
		res+=get_c-'0';\
	}\
	res*=get_sign;\
}

int8_t get_sign;
int get_c;

char put_data[44];
unsigned long long put_t;
unsigned put_ds;

#define put_int(q)\
{\
	if (q<0){\
		putchar_unlocked('-');\
		put_t=-q;\
	}else{\
		put_t=q;\
	}\
	put_ds=0;\
	while(put_t){\
		put_data[++put_ds]=put_t%10+(unsigned)('0');\
		put_t/=10;\
	}\
	if (put_ds==0){\
		putchar_unlocked('0');\
	}\
	for (;put_ds;--put_ds){\
		putchar_unlocked(put_data[put_ds]);\
	}\
}

int main(){
	uint32_t n;
	get_int(n);
	c_array(size_t,a,n);
	uint32_t a_sum=0;
	for (size_t w=0;w<n;++w){
		get_int(a[w]);
		a_sum+=a[w];
	}
	const uint32_t end=1LLU<<(n);
	uint32_t c_sum;
	uint32_t min_sum=-1;
	uint32_t cw;
	size_t w;
	size_t*ap;
	for (w=0;w<end;++w){
		c_sum=0;
		cw=w;
		ap=a;

		while (cw){
			c_sum+=(*ap)  *  ((cw)&1);
			cw>>=1,++ap;
		}

		c_sum=(c_sum*2)-a_sum;
		if (c_sum<min_sum){
			min_sum=c_sum;
		}
	}
	put_int(min_sum);
	putchar_unlocked('\n');
}
