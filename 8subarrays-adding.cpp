#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


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
	ssize_t n,q;
	scanf("%zi%zi",&n,&q);
	auto a=new ssize_t[n];
	for (ssize_t w=0;w<n;++w){
		scanf("%zi",a+w);
	}
	tree p(n);
	for (ssize_t w=0;w<q;++w){
		ssize_t l,r,x;
		scanf("%zi%zi%zi",&l,&r,&x);
		// ic(l,r+1,x)
		p.add(x,l,r+1);
		// ic(itervect(p.mdb,p.mdb+p.ms))
	}
	auto s=p.res();
	for (ssize_t w=0;w<n;++w){
		a[w]+=s[w];
		printf("%zi ",a[w]);
	}
	printf("\n");
	delete[] a;
}
