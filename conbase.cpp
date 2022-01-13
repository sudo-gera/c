#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#define get_int(res)\
{\
	int8_t sign=1;\
	int c;\
	while (c=getchar_unlocked(),isspace(c)){\
	}\
	if (c=='-'){\
		sign*=-1;\
	}else{\
		res=c-'0';\
	}\
	while (c=getchar_unlocked(),c!=EOF and !isspace(c)){\
		res*=10;\
		res+=c-'0';\
	}\
	res*=sign;\
}

char put_data[44];

#define put_int(q)\
{\
	unsigned long long t;\
	if (std::is_signed<decltype(q)>::value and q<0){\
		putchar_unlocked('-');\
		t=-q;\
	}else{\
		t=q;\
	}\
	unsigned ds=1;\
	while (t){\
		put_data[ds++]=t%10+'0';\
		t/=10;\
	}\
	for (--ds;ds;--ds){\
		putchar_unlocked(put_data[ds]);\
	}\
}
