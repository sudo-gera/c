#include <stdio.h>
#include <stdint.h>

template <class T>
class tree{
public:
	struct item{
		int64_t res=0;
		int64_t pro=0;
	};
	item *mdb;
	size_t ms;
	int64_t*a;
	int64_t s;
	T f;
	tree(T _f,int64_t*_a,size_t _s):f(_f){
		a=_a;
		s=_s;
		ms=2;
		size_t d=s;
		while (d){
			d>>=1;	
			ms<<=1;
		}
		mdb=new item[ms];
		init(0,ms);
	}
	item&acess(size_t b,size_t e){
		return mdb[(ms/2+b)/(e-b)];
	}
	int64_t init(size_t b,size_t e){
		if (e-b==1){
			auto&y=acess(b,e).res;
			return y=b<s?a[b]:0;
		}
		auto z=init(b,(b+e)/2);
		auto x=init((b+e)/2,e);
		acess(b,e).res=f(z,x);
		return acess(b,e).res;
	}
	int64_t get(size_t ub,size_t ue,size_t b=0,size_t e=-1){
		if (e==size_t(-1)){
			e=ms;
		}
		if (b==ub and ue==e){
			auto y=acess(b,e);
			return y.res+y.pro;
		}
		acess(b,(b+e)/2).pro+=acess(b,e).pro;
		acess((b+e)/2,e).pro+=acess(b,e).pro;
		acess(b,e).res+=acess(b,e).pro;
		acess(b,e).pro=0;
		size_t c=(b+e)/2;
		if (b<=ub and ue<=c){
			return get(ub,ue,b,c);
		}
		if (c<=ub and ue<=e){
			return get(ub,ue,c,e);
		}
		auto z=get(ub,c,b,c);
		auto x=get(c,ue,c,e);
		return f(z,x);
	}
	void add(size_t ub,size_t ue,int64_t d,size_t b=0,size_t e=-1){
		if (e==size_t(-1)){
			e=ms;
		}
		if (b==ub and ue==e){
			auto y=acess(b,e);
			y.pro+=d;
			return;
		}
		acess(b,(b+e)/2).pro+=acess(b,e).pro;
		acess((b+e)/2,e).pro+=acess(b,e).pro;
		acess(b,e).res+=acess(b,e).pro;
		acess(b,e).pro=0;
		size_t c=(b+e)/2;
		if (b<=ub and ue<=c){
			add(ub,c,d,b,c);
			return;
		}
		if (c<=ub and ue<=e){
			add(c,ue,d,c,e);
			return;
		}
		add(ub,c,d,b,c);
		add(c,ue,d,c,e);
	}
};


int main(){
	let a=vector<int64_t>({7,3,7,4,7,4,7,3,7});
	let y=[&](int64_t q,int64_t w){return q<w?q:w;};
	let s=tree<decltype(y)>(y,a.data(),a.size());
	while (1){
		let q=scan(str);
		if (q==""){
			break;
		}
		if (q=="get"){
			print(s.get(scan(int64_t),scan(int64_t)));
		}
		if (q=="add"){
			s.add(scan(int64_t),scan(int64_t),scan(int64_t));
		}
	}
}