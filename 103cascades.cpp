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
	size_t n,k;
	get_int(n);
	get_int(k);
	auto a=new unsigned*[n];
	auto l=new unsigned[n];
	for (size_t q=0;q<n;++q){
		get_int(l[q]);
		a[q]=new unsigned[l[q]+2];
		a[q][0]=0;
		for (size_t w=1;w<l[q]+1;++w){
			get_int(a[q][w]);
		}
		a[q][l[q]+1]=-1;
	}
	for (size_t q=0;q<k;++q){
		long t;
		get_int(t);
		for (size_t w=0;w<n;++w){
			size_t b=0;
			size_t e=l[w]+1;
			while(e-b>1){
				size_t c=(b+e)/2;
				if (a[w][c]<t){
					b=c;
				}else{
					e=c;
				}
			}
			// size_t e=0;
			// while(a[w][e]<t){
			// 	e++;
			// }
			put_int(int(a[w][e]));
			putchar_unlocked(' ');
		}
		putchar_unlocked('\n');
	}
}
