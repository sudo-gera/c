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

size_t fib(size_t*ff0_102400,size_t*ff1_102400,size_t m,size_t n){
	size_t f0=ff0_102400[n/102400];
	size_t f1=ff1_102400[n/102400];
	n%=102400;
	while (n){
		size_t f2=(f0+f1)%m;
		f0=f1;
		f1=f2;
		n-=1;
	}
	return f0;
}

int main(){
	size_t a0,a1,n,m;
	// get_int(a0);
	// get_int(a1);
	// get_int(n);
	// get_int(m);
	m=1000000;
	c_array(size_t,f,102400+4);
	c_array(size_t,ff0_102400,102400+1);
	c_array(size_t,ff1_102400,102400+1);
	f[0]=1;
	f[1]=1;
	for (size_t w=2;w<102400+4;++w){
		f[w]=(f[w-1]+f[w-2])%m;
	}
	ff0_102400[0]=1;
	ff1_102400[0]=1;
	for (size_t k=0;k<102400;++k){
		ff0_102400[k+1]=(f[102400-2]*ff0_102400[k]+f[102400-1]*ff1_102400[k])%m;
		ff1_102400[k+1]=(f[102400-1]*ff0_102400[k]+f[102400]*ff1_102400[k])%m;
	}
	
}
