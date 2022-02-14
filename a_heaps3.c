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
// #define ALG
#ifdef ALG
#include <algorithm>
#endif

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
size_t*sumsl;
size_t*sumsr;


size_t sumss=0;

void run(size_t*a,size_t*sums,size_t*sumss,size_t as,size_t a_sum,size_t ss,size_t sum,size_t last_index){
	// ic_no_func(itervect(a,a+as),itervect(sums,sums+*sumss),a_sum,itervect(s,s+ss),sum,last_index)
	sums[(*sumss)++]=sum;
	// if (sum+sum-a_sum < min_sum){
	// 	min_sum=sum+sum-a_sum;
	// }
	// if (a_sum-sum-sum < min_sum){
	// 	min_sum=sum+sum-a_sum;
	// }
	if (ss==as){
		return;
	}
	for (size_t w=last_index;w<as;++w){
		s[ss]=a[w];
		run(a,sums,sumss,as,a_sum,ss+1,sum+a[w],w+1);
	}
}

int cmp(size_t*q,size_t*w){
	// ic(*(size_t*)(q),*(size_t*)(w),*(size_t*)(q)<*(size_t*)(w))
	// return (*(size_t*)(q))<(*(size_t*)(w));
	return *q-*w;
}

int main(){
	size_t n;
	get_int(n);
	a=array(size_t,n);
	s=array(size_t,n);
	sumsl=array(size_t,1LLU<<n);
	sumsr=array(size_t,1LLU<<n);
	size_t a_sum=0;
	for (size_t w=0;w<n;++w){
		get_int(a[w]);
		a_sum+=a[w];
	}
	size_t sumssl=0;
	size_t sumssr=0;
	run(a    ,sumsl,&sumssl,n/2  ,a_sum,0,0,0);
	run(a+n/2,sumsr,&sumssr,n-n/2,a_sum,0,0,0);
	// ic(itervect(sumsl,sumsl+sumssl))
	// ic(itervect(sumsr,sumsr+sumssr))
	cmp(sumsl,sumsl+1);
	#ifdef ALG
	std::sort(sumsl,sumsl+sumssl);
	std::sort(sumsr,sumsr+sumssr);
	#else
	qsort(sumsl,sumssl,sizeof(sumsl[0]),(int(*) (const void *, const void *)) cmp);
	qsort(sumsr,sumssr,sizeof(sumsr[0]),(int(*) (const void *, const void *)) cmp);
	#endif
	// ic(itervect(sumsl,sumsl+sumssl))
	// ic(itervect(sumsr,sumsr+sumssr))
	uint32_t min_sum=-1;
	long l=0;
	long r=sumssr-1;
	while (l<sumssl and r>=0){
		size_t d=(sumsl[l]+sumsr[r])*2;
		// ic(l,r,d)
		if (d-a_sum<min_sum){
			min_sum=(sumsl[l]+sumsr[r])*2-a_sum;
		}
		if (a_sum-d<min_sum){
			min_sum=a_sum-(sumsl[l]+sumsr[r])*2;
		}
		if (d>a_sum){
			r--;
		}else
		if (d<a_sum){
			l++;
		}else
		if (d==a_sum){
			break;
		}
	}
	put_int(min_sum);
	putchar_unlocked('\n');
}
