#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <algorithm>

// #define get_int(res)\
// {\
// 	int8_t sign=1;\
// 	int c;\
// 	while (c=getchar_unlocked(),isspace(c)){\
// 	}\
// 	if (c=='-'){\
// 		sign*=-1;\
// 		res=0;\
// 	}else{\
// 		res=c-'0';\
// 	}\
// 	while (c=getchar_unlocked(),c!=EOF and !isspace(c)){\
// 		res*=10;\
// 		res+=c-'0';\
// 	}\
// 	res*=sign;\
// }

// char put_data[44];

// #define put_int(q)\
// {\
// 	unsigned long long t;\
// 	if (std::is_signed<decltype(q)>::value and q<0){\
// 		putchar_unlocked('-');\
// 		t=-q;\
// 	}else{\
// 		t=q;\
// 	}\
// 	unsigned ds=1;\
// 	while (t){\
// 		put_data[++ds]=t%10+'0';\
// 		t/=10;\
// 	}\
// 	for (;ds;--ds){\
// 		putchar_unlocked(put_data[ds]);\
// 	}\
// }

#define get_int(q) scanf("%zi",&(q));
#define put_int(q) printf("%zi",(q));

long run(long*a,long b,long e){
	assert(b<e);
	if (e-b==1){
		return 0;
	}
	long res=size_t(-1)/2;
	long sum=0;
	for (long w=b;w<e;++w){
		sum+=a[w];
	}
	long psum=0;
	long md=size_t(-1)/2;
	long mdw=-1;
	for (long w=b;w<e;++w){
		if (md>abs(sum-psum-psum)){
			md=abs(sum-psum-psum);
			mdw=w;
		}
		psum+=a[w];
	}
	// for (long w=(b+1>mdw-1?b+1:mdw-1);w<(e<mdw+1?e:mdw+1);++w){
		long tmp=run(a,b,w)+run(a,w,e);
		res=res<tmp?res:tmp;
	// }
	return res+sum;
}

int main(){
	long n;
	get_int(n);
	auto a=new long[n];
	for (long w=0;w<n;++w){
		get_int(a[w]);
	}
	std::sort(a,a+n);
	printf("%.02lf\n",(run(a,0,n)/100.));
}
