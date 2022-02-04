#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#include <functional>

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
	for (;put_ds;--put_ds){\
		putchar_unlocked(put_data[put_ds]);\
	}\
}

template<typename T,typename F>
struct heap{
	T*data=nullptr;
	T&top;
	size_t size=0;
	heap(T*d):data(d),top(*data){}
	void insert(T q){
		data[size++]=q;
		data--;
		size_t c=size;
		while (c>1 and F{}(data[c],data[c/2])){
			T t=data[c];
			data[c]=data[c/2];
			data[c/2]=t;
			c=c/2;
		}
		data++;
	}
	void erase(T* q=nullptr){
		assert(size);
		data[0]=data[size-1];
		data--;
		size_t c=1;
		while( 2*c+1<size and ( F{}(data[2*c],data[c]) or F{}(data[2*c+1],data[c]) ) ){
			if (F{}(data[2*c],data[2*c+1])){
				T t=data[c];
				data[c]=data[c*2];
				data[c*2]=t;
				c=c*2;
			}else{
				T t=data[c];
				data[c]=data[c*2+1];
				data[c*2+1]=t;
				c=c*2+1;
			}
		}
		if( 2*c<size and F{}(data[2*c],data[c]) ){
			T t=data[c];
			data[c]=data[c*2];
			data[c*2]=t;
			c=c*2;
		}
		data++;
		size--;
	}
};

int main(){
	size_t n;
	get_int(n);
	heap<ssize_t,std::greater<ssize_t>> a(new ssize_t[1000000]);
	heap<ssize_t,std::less<ssize_t>> s(new ssize_t[1000000]);
	for (size_t w=0;w<n;++w){
		size_t q;
		get_int(q);
		if (q){
			put_int(a.top);
			putchar_unlocked('\n');
		}else{
			ssize_t e;
			get_int(e);
			a.insert(e);
			while (a.size>s.size){
				s.insert(a.top);
				a.erase();
			}
			while (s.size>a.size){
				a.insert(s.top);
				s.erase();
			}
		}
	}
}
