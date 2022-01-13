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

// template <class T>
class tree{
public:
	// struct item{
	// 	ssize_t pro=0;
	// };
	using item=ssize_t;
	item *mdb;
	ssize_t ms;
	item&acess(ssize_t b,ssize_t e){
		// if (e==b){
		// 	e=mdb[-1];
		// }
		// ic(b,e,ms)
		return mdb[(ms/2+b)/(e-b)];
	}
	tree(ssize_t s){
		ms=2;
		ssize_t d=s;
		while (d){
			d>>=1;	
			ms<<=1;
		}
		mdb=new item[ms];
		memset(mdb,0,sizeof(item)*ms);		
	}
	void add(ssize_t v,ssize_t ub,ssize_t ue,ssize_t b=0,ssize_t e=-1){
		if (e==ssize_t(-1)){
			e=ms/2;
		}
		ssize_t c=(b+e)/2;
		// ic(v,ub,ue,b,e,c)
		if (b==ub and ue==e){
			acess(b,e)+=v;
			return;
		}
		if ((b<=ub and ue<=c)){
			add(v,ub,ue,b,c);
			return;
		}
		if (c<=ub and ue<=e){
			add(v,ub,ue,c,e);
			return;
		}
		add(v,ub,c,b,c);
		add(v,c,ue,c,e);
	}
	ssize_t* res(ssize_t b=0,ssize_t e=-1){
		if (e==ssize_t(-1)){
			e=ms/2;
		}
		if (e-b>1){
			ssize_t c=(b+e)/2;
			acess(b,c)+=acess(b,e);
			acess(c,e)+=acess(b,e);
			res(b,c);
			res(c,e);
		}
		return ms/2+mdb;
	}
	~tree(){
		delete[] mdb;
	}
};

int main(){
	ssize_t a=new ssize_t[1'000'000];
	tree t;
	
	
}
