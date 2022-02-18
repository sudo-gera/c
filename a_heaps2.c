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


size_t min_sum=-1;

size_t*a;
size_t*s;


void run(size_t as,size_t a_sum,size_t ss,size_t sum,size_t last_index){
	// ic_no_func(itervect(a,a+as),a_sum,itervect(s,s+ss),sum,last_index)
	if (sum+sum-a_sum < min_sum){
		min_sum=sum+sum-a_sum;
	}
	if (a_sum-sum-sum < min_sum){
		min_sum=sum+sum-a_sum;
	}
	if (ss==as){
		return;
	}
	for (size_t w=last_index;w<as;++w){
		s[ss]=a[w];
		run(as,a_sum,ss+1,sum+a[w],w+1);
	}
}

int cmp(const void*q,const void*w){
	return *(int*)(q)<*(int*)(w);
}

int main(){
	size_t n;
	get_int(n);
	a=array(size_t,n);
	s=array(size_t,n);
	size_t a_sum=0;
	for (size_t w=0;w<n;++w){
		get_int(a[w]);
		a_sum+=a[w];
	}
	qsort(a,n,sizeof(a[0]),cmp);
	// size_t c_sum;
	run(n,a_sum,0,0,0);
	put_int(min_sum);
	putchar_unlocked('\n');
}
