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
	if ((q)<0){\
		putchar_unlocked('-');\
		put_t=-(q);\
	}else{\
		put_t=(q);\
	}\
	put_ds=0;\
	while(put_t){\
		put_data[++put_ds]=put_t%10+(unsigned)('0');\
		put_t/=10;\
	}\
	for (;put_ds;--put_ds){\
		putchar_unlocked(put_data[put_ds]);\
	}\
}

typedef long T;

typedef struct heap{
	T*data;
	size_t size;
	bool (*F)();
}heap;

heap heap_c(bool (*f)(),T*d){
	heap t;
	t.data=d;
	t.size=0;
	t.F=f;
	return t;
}


void insert(heap*t,T q){
	t->data[t->size++]=q;
	t->data--;
	size_t c=t->size;
	while (c>1 and t->F(t->data[c],t->data[c/2])){
		T _t=t->data[c];
		t->data[c]=t->data[c/2];
		t->data[c/2]=_t;
		c=c/2;
	}
	t->data++;
}
void erase(heap*t){
	assert(t->size);
	t->data[0]=t->data[t->size-1];
	t->data--;
	size_t c=1;
	while( 2*c+1<t->size and ( t->F(t->data[2*c],t->data[c]) or t->F(t->data[2*c+1],t->data[c]) ) ){
		if (t->F(t->data[2*c],t->data[2*c+1])){
			T _t=t->data[c];
			t->data[c]=t->data[c*2];
			t->data[c*2]=_t;
			c=c*2;
		}else{
			T _t=t->data[c];
			t->data[c]=t->data[c*2+1];
			t->data[c*2+1]=_t;
			c=c*2+1;
		}
	}
	if( 2*c<t->size and t->F(t->data[2*c],t->data[c]) ){
		T _t=t->data[c];
		t->data[c]=t->data[c*2];
		t->data[c*2]=_t;
		c=c*2;
	}
	t->data++;
	t->size--;
}

bool is_greater(long q,long w){
	return q>w;
}

bool is_less(long q,long w){
	return q<w;
}

int main(){
	size_t n;
	get_int(n);
	heap a=heap_c(is_greater,malloc(sizeof(long)*1000000));
	heap s=heap_c(is_less,malloc(sizeof(long)*1000000));
	for (size_t w=0;w<n;++w){
		size_t q;
		get_int(q);
		if (q){
			put_int(*a.data);
			putchar_unlocked('\n');
		}else{
			ssize_t e;
			get_int(e);
			insert(&a,e);
			while (a.size>s.size){
				insert(&s,*a.data);
				erase(&a);
			}
			while (s.size>a.size){
				insert(&a,*s.data);
				erase(&s);
			}
		}
	}
}
