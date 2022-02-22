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

size_t fibonacci(size_t n,long m){
	size_t t=1;
	while (t<n){
		t<<=1;
	}
	long f0=0;
	long f1=1;
	long t0,t1;
	while (t>1){
		if (n&t){
			f1+=f0;
			f0=f1-f0;
		}
		t0=f1*f0*2-f0*f0;
		t1=f0*f0+f1*f1;
		f0=(t0%m+m)%m;
		f1=(t1%m+m)%m;
		t>>=1;
	}
	if (n%2){
		return f1;
	}
	return f0;
}

int main(int argc,char**argv){
	long a0,a1,n,m;
	get_int(a0);
	get_int(a1);
	get_int(n);
	get_int(m);
	if (n==0){
		put_int(a0);
	}else{
		put_int((a0*fibonacci(n-1,m)+a1*fibonacci(n,m))%m);
	}
	putchar_unlocked('\n');
}
