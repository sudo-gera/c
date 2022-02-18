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

int main(){
	size_t M1, N1, M2, N2;
	get_int(M1);
	get_int(N1);
	get_int(M2);
	get_int(N2);
	auto a=new long*[M1];
	for (size_t w=0;w<M1;++w){
		a[w]=new long [N1];
		for (size_t e=0;e<N1;++e){
			get_int(a[w][e]);
		}
	}
	auto s=new long*[M2];
	for (size_t w=0;w<M2;++w){
		s[w]=new long [N2];
		for (size_t e=0;e<N2;++e){
			get_int(s[w][e]);
		}
	}
	if (N1!=M2){
		put_int(-1);
		putchar_unlocked('\n');
	}else{
		auto d=new long*[M1];
		for (size_t q=0;q<M1;++q){
			d[q]=new long[N2];
			for (size_t w=0;w<N2;++w){
				long res=0;
				for (size_t e=0;e<M2;++e){
					res+=a[q][e]*s[e][w];
				}
				d[q][w]=res;
				put_int(res);
				putchar_unlocked(' ');
			}
			putchar_unlocked('\n');
		}
	}
}
