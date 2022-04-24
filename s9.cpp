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
#include <iostream>
#include <algorithm>
using namespace std;

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

static inline int64_t getint() {
	long n;
	cin>>n;
	return n;
}

static inline void putint(uint64_t out) {
	long n=(long)(out);
	cout<<n;
}

static inline void print(uint64_t out) {
	putint(out);
	putchar('\n');
}

static inline void write(uint64_t out) {
	putint(out);
	putchar(' ');
}

typedef int (*cmp_f_t)(const void *, const void *);

#define bisect(b, e, ...)														\
	({																			\
		int64_t __begin = b;													\
		int64_t __end = e;														\
		assert(__begin <= __end);												\
		while (__begin + 1 < __end) {											\
			int64_t __center = (__begin + __end) / 2;							\
			if (__VA_ARGS__) {													\
				__end = __center;												\
			} else {															\
				__begin = __center;												\
			}																	\
		}																		\
		int64_t __center = __begin;												\
		if (__begin != __end and (__VA_ARGS__)) {								\
			__end = __center;													\
		}																		\
		__end;																	\
	})

///////////////////////////////////////////////////end of lib

long n=0;
long s=0;
long*a=0;
long*b=0;
long*c=0;

long*z=0;

auto get(long _c){
	for (long w=0;w<n;w++){
		if (c[w]>=_c){
			z[w]=a[w];
		}else{
			z[w]=b[w];
		}
	}
	sort(z,z+n);
	long _s=0;
	for (long w=0;w<n and w<_c;w++){
		_s+=z[w];
	}
	if (_s>s){
		return 1;
	}else{
		return 0;
	}
}

int main(){
	n=getint();
	s=getint();
	a=new long[n];
	b=new long[n];
	c=new long[n];
	z=new long[n];
	for (long w=0;w<n;w++){
		a[w]=getint();
		b[w]=getint();
		c[w]=getint();
	}
	print(bisect(0,n+1,get(__center))-1);
}
