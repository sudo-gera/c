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

int8_t get_sign;
int get_c;

#define get_int(res)\
{\
	get_sign=1;\
	get_c;\
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
		put_data[++put_ds]=put_t%10+unsigned('0');\
		put_t/=10;\
	}\
	if (put_ds==0){\
		putchar_unlocked('0');\
	}\
	for (;put_ds;--put_ds){\
		putchar_unlocked(put_data[put_ds]);\
	}\
}


long&acess(long*s,long k,long b,long e){
	return s[(k+b)/(e-b)];
}

long init(size_t k,long*a,long*s,size_t b,size_t e){
	if (e-b==1){
		return a[b];
	}
	size_t c=(b+e)/2;
	long t1=init(k,a,s,b,c);
	long t2=init(k,a,s,c,e);
	t1=t1>t2?t1:t2;
	acess(s,k,b,e)=t1;
	return t1;
}

long max(size_t k,long*a,long*s,size_t ub,size_t ue,size_t b,size_t e){
	if (ub==b and ue==e){
		return acess(s,k,b,e);
	}
	size_t c=(b+e)/2;
	if (b<=ub and ue<=c){
		return max(k,a,s,ub,ue,b,c);
	}
	if (c<=ub and ue<=e){
		return max(k,a,s,ub,ue,c,e);
	}
	long t1=max(k,a,s,ub,c,b,c);
	long t2=max(k,a,s,c,ue,c,e);
	return t1>t2?t1:t2;
}


int main(){
	size_t kk=2097152;
	// auto kk=16;
	size_t k=kk/2;
	auto s=new long[kk];
	// auto a=new long[k];
	auto a=s+k;
	size_t n,m;
	get_int(n);
	get_int(m);
	for (size_t w=0;w<n;++w){
		get_int(a[w]);
	}
	init(k,a,s,0,k);
	for (size_t w=0;w<m;++w){
		size_t l,r;
		get_int(l);
		get_int(r);
		put_int(max(k,a,s,l,r+1,0,k));
		putchar_unlocked('\n');
	}
	delete[] s;
}






