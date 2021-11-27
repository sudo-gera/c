#include <iostream>
#include <string>

long long int offstep=100;
long long int offset=70;


#define offcheck (offset>0)?offset--:(offset--%offstep)?:
 
using std::cerr;
// #define cerr ss


// #define _1ic_t(...) offcheck(cerr<<"|"<<__LINE__<<" "<<*this<<" "<<__VA_ARGS__<<std::flush,0);
// #define _2ic_(...) offcheck(cerr<<"|"<<__LINE__<<" "<<__VA_ARGS__<<std::flush,0);
// #define _3i_t offcheck(cerr<<"|"<<__LINE__<<" "<<*this<<std::flush,0);
// #define _4i_ offcheck(cerr<<"|"<<__LINE__<<std::flush,0);
#define _1ac_t(...) offcheck(cerr<<"|"<<__LINE__<<" "<<*this<<" "<<__VA_ARGS__<<std::flush,0);
#define _2ac_(...) offcheck(cerr<<"|"<<__LINE__<<" "<<__VA_ARGS__<<std::flush,0);
#define _3a_t offcheck(cerr<<"|"<<__LINE__<<" "<<*this<<std::flush,0);
#define _4a_ offcheck(cerr<<"|"<<__LINE__<<std::flush,0);

#define _1ic_t(...)
#define _2ic_(...)
#define _3i_t
#define _4i_
// #define _1ac_t(...)
// #define _2ac_(...)
// #define _3a_t
// #define _4a_

class BigInteger{
private:
	int8_t sign=0;
	size_t size=0;
	uint32_t *vect=nullptr;
public:
	BigInteger(){
		// _4i_
	}
private:
	void resize(size_t q){
		if (size<q){
			auto t=new uint32_t[q]();
			for (size_t w=0;w<size;++w){
				t[w]=vect[w];
			}
			if (vect){
				delete[] vect;
			}
			vect=t;
			size=q;
		}
	}
public:
	BigInteger(const BigInteger& orig){
		// _2ic_(orig)
		resize(orig.size);
		size=orig.size;
		sign=orig.sign;
		for (size_t w=0;w<size;++w){
			vect[w]=orig.vect[w];
		}
	}
	BigInteger(const int&orig){
		_2ic_(orig)
		resize(1);
		sign=orig>0?1:orig<0?-1:0;
		vect[0]=sign*orig;
	}
	auto&operator=(const BigInteger&orig){
		// _1ic_t(orig)
		if (vect==orig.vect){
			return *this;
		}
		resize(orig.size);
		sign=orig.sign;
		size_t w=0;
		for (;w<orig.size;++w){
			vect[w]=orig.vect[w];
		}
		for (;w<size;++w){
			vect[w]=0;
		}
		return *this;
	}
	BigInteger(const char*orig,int t=10){
		*this=BigInteger(std::string(orig),t);
	}
	BigInteger(const std::string&orig,int64_t t=10){
		_2ic_(orig)
		size_t l=orig.size();
		resize(l/"\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"
			[t]+1);
		sign=0;
		BigInteger a,y=t;
		int g=0;
		if (l and orig[0]=='-'){
			g=1;
		}
		for (size_t w=g;w<l;++w){
			*this*=y;
			*this+="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"
				[(int)(orig[w])];
		}
		sign*=(-2)*g+1;
	}
	friend std::ostream&operator<<(std::ostream&q,const BigInteger&w){
		q<<w.toString();
		return q;
	}
	friend auto&operator>>(std::istream&q,BigInteger&w){
		std::string g;
		q>>g;
		_2ic_(g)
		w=g;
		return q;
	}
	std::string toString(int e=10)const{
		uint64_t _t=e;
		BigInteger r;
		r=*this;
		r.sign=bool(r.sign);
		// r.resize(size);
		// for (size_t w=0;w<size;++w){
		// 	r.vect[w]=vect[w];
		// }
		BigInteger t=0;
		std::string a((size+1)*"\x00\x00\x20\x15\x10\x0e\x0d\x0c\x0b\x0b\x0a\x0a\x09\x09\x09\x09\x08\x08\x08\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07"
			[e],0);
		size_t s=0;
		while (r.sign){
			uint64_t b=0;
			uint64_t t=0;
			for (size_t _w=r.size;_w>0;--_w){size_t w=_w-1;
				t=r.vect[w];
				t+=b<<32;
				b=t%_t;
				t/=_t;
				r.vect[w]=t;
			}
			r.sign=0;
			for (size_t _w=r.size;_w>0;--_w){size_t w=_w-1;
				if (r.vect[w]){
					r.sign=1;
					break;
				}
			}
			a[s++]=b;
		}
		for (size_t w=0;w<s;++w){
			a[w]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(int)(a[w])];
		}
		if (sign<0){
			a[s++]='-';
		}
		if (!s){
			a[s++]='0';
		}
		for (size_t w=0;w*2<s;++w){
			char t=a[w];
			a[w]=a[s-1-w];
			a[s-1-w]=t;
		}
		a=std::string(a.begin(),a.begin()+s);
		return a;
	}

	operator std::string()const{
		_3i_t
		return this->toString();
	}
private:
	friend int8_t cmp(BigInteger const&q,BigInteger const&e,bool onlymod=0){
		if (!onlymod and q.sign!=e.sign){
			return ((q.sign)-(e.sign));
		}
		if (q.size+e.size==0){
			return 0;
		}
		for (size_t c=(q.size>e.size?q.size:e.size)-1;;--c){
			size_t a=q.size>c?q.vect[c]:0;
			size_t s=e.size>c?e.vect[c]:0;
			if (a!=s){
				return (((a>s)*2-1)*(onlymod?1:q.sign));
			}
			if (!c){break;}
		}
		return 0;
	}
public:
	friend bool operator<(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)<0;
	}
	friend bool operator>(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)>0;
	}
	friend bool operator==(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)==0;
	}
	friend bool operator!=(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)!=0;
	}
	friend bool operator<=(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)<=0;
	}
	friend bool operator>=(BigInteger const&q,BigInteger const&e){
		_2ic_(q)
		_2ic_(e)
		return cmp(q,e)>=0;
	}
	~BigInteger(){
		if (vect){
			delete[] vect;
		}
	}
private:
	friend void bn_M_add_to(BigInteger &q, BigInteger const &e){
		size_t qs=q.size;
		if (qs and q.vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		q.resize(qs);
		uint64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=q.vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			q.vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
	}
	friend void bn_M_add_to_fast(BigInteger &q, BigInteger const &e,uint64_t start){
		size_t qs=q.size;
		if (qs and q.vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		q.resize(qs);
		uint64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=q.vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			q.vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
	}
	friend void bn_M_sub_to(BigInteger &q, BigInteger const &e){
		size_t qs=q.size;
		if (qs and q.vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		q.resize(qs);
		int64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=q.vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			q.vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
		size_t g=q.size;
		while (g>0 and q.vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			q.sign=0;
		}	
	}
	friend void bn_M_sub_to_fast(BigInteger &q, BigInteger const &e,uint64_t start){
		size_t qs=q.size;
		if (qs and q.vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		q.resize(qs);
		int64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=q.vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			q.vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
		size_t g=q.size;
		while (g>0 and q.vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			q.sign=0;
		}	
	}
public:
	BigInteger&operator+=(const BigInteger&e){
		_1ic_t(e)

		int l=cmp(*this,e,1);
		if (!e.sign){
			return *this;
		}
		if (e.sign*sign>=0){
			bn_M_add_to(*this,e);
			sign=e.sign;
		}else if (l>=0){
			bn_M_sub_to(*this,e);
		}else{
			BigInteger h=*this;
			*this=e;
			bn_M_sub_to(*this,h);
		}
		size_t g=size;
		while (g>0 and vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			sign=0;
		}
		return *this;
	}
	BigInteger&operator-=(const BigInteger&e){
		_1ic_t(e)
		sign*=-1;
		*this+=e;
		sign*=-1;
		return *this;
	}
	friend BigInteger operator+(const BigInteger&q,const BigInteger&w){
		_2ic_(q)
		_2ic_(w)
		auto h=q;
		h+=w;
		return h;
	}
	friend BigInteger operator-(const BigInteger&q,const BigInteger&w){
		_2ic_(q)
		_2ic_(w)
		auto h=q;
		h-=w;
		return h;
	}
	friend BigInteger operator*(BigInteger const&q,const BigInteger&e){
		_2ic_(q)
		_2ic_(e)
		BigInteger res;
		BigInteger tmp;
		size_t qs=q.size;
		size_t es=e.size;
		while (qs and q.vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		res.resize(qs+es);
		tmp.resize(qs+es);
		tmp.sign=1;
		for (size_t w=0;w<qs;++w){
			if (q.vect[w]){
				for (size_t r=0;r<es;++r){
					*(uint64_t*)(tmp.vect+w+r)=(uint64_t)(q.vect[w])*(uint64_t)(e.vect[r]);
					bn_M_add_to_fast(res,tmp,w+r); 
					*(uint64_t*)(tmp.vect+w+r)=0;
				}
			}
		}
		res.sign=q.sign*e.sign;
		return res;
	}
	BigInteger&operator*=(BigInteger const&w){
		return *this=*this*w;
	}
private:
	friend void bn_half(BigInteger&q){
		if (q.size){
			q.vect[0]>>=1;
		}
		for (size_t w=1;w<q.size;++w){
			q.vect[w-1]|=(q.vect[w]&1)<<31;
			q.vect[w]>>=1;
		}
		size_t r=0;
		for (size_t w=0;w<q.size;++w){
			if (q.vect[w]){
				r=1;
				break;
			}
		}
		if (!r){
			q.sign=0;
		}
	}
	friend void bn_M_div_to(BigInteger&q,const BigInteger&e,bool getdiv=1){
		if(!e.sign){std::cerr<<"zero"<<std::flush;return;}
		auto rsign=q.sign*e.sign;
		q.sign=bool(q.sign);
		size_t qs=q.size;
		size_t es=e.size;
		while (qs and q.vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		BigInteger r;
		if (qs>=es){
			BigInteger t;
			t.resize(qs+2);
			t.sign=1;
			for(size_t w=0;w<es;++w){
				t.vect[qs-es+2+w]=e.vect[w];
			}
			BigInteger*a=new BigInteger[32];
			a[31]=t;
			bn_half(a[31]);
			for (size_t w=31;w>1;--w){
				a[w-1]=a[w];
				bn_half(a[w-1]);
			}
			a[0]=t;
			uint64_t*o=new uint64_t[32]();
			r.resize(qs+1-es);
			ssize_t f=(r.size+1)*32;
			r.sign=1;
			while (f>=0){
				// print(q,a[f&0b11111],r,f)
				if (q>=a[f&0b11111]){
					r.vect[f>>5]|=(1LL<<(f&0b11111));
					bn_M_sub_to(q,a[f&0b11111]);
				}
				a[f&0b11111].size-=1;
				a[f&0b11111].vect+=1;
				o[f&0b11111]+=1;
				f-=1;
			}
			size_t rs=r.size;
			while (rs and r.vect[rs-1]==0){
				--rs;
			}
			if (!rs){
				r.sign=0;
			}
			for (size_t w=0;w<32;++w){
				a[w].vect-=o[w];
			}
			delete[] o;
			delete[] a;
		}
		if (getdiv){
			q=r;
		}
		q.sign=rsign;
		size_t g=q.size;
		while (g>0 and q.vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			q.sign=0;
		}	
	}
public:
	auto&operator/=(const BigInteger&e){
		_1ic_t(e)
		bn_M_div_to(*this,e,1);
		return *this;
	}
	auto&operator%=(const BigInteger&e){
		_1ic_t(e)
		bn_M_div_to(*this,e,0);
		return *this;
	}

	friend BigInteger operator/(const BigInteger&q,const BigInteger&w){
		_2ic_(q)
		_2ic_(w)
		auto h=q;
		h/=w;
		return h;
	}
	friend BigInteger operator%(const BigInteger&q,const BigInteger&w){
		_2ic_(q)
		_2ic_(w)
		auto h=q;
		h%=w;
		return h;
	}

	auto&operator++(){
		_3i_t
		if (this->sign<0){
			bn_M_sub_to_fast(*this,1,0);
		}else{
			bn_M_add_to_fast(*this,1,0);
		}
		return *this;
	}
	auto operator++(int){
		_3i_t
		auto h=*this;
		++*this;
		return h;
	}
	auto&operator--(){
		_3i_t
		if (this->sign<0){
			bn_M_add_to_fast(*this,1,0);
		}else{
			bn_M_sub_to_fast(*this,1,0);
		}
		return *this;
	}
	auto operator--(int){
		_3i_t
		auto h=*this;
		--*this;
		return h;
	}
	auto operator-()const{
		_3i_t
		BigInteger g=*this;
		g.sign*=-1;
		return g;
	}
	explicit operator bool(){
		_3i_t
		return this->sign;
	}
#ifdef CPP_R
	friend std::string print_one(const BigInteger&q);
	friend std::string print_one(BigInteger&q);
#endif
	friend BigInteger gcd(BigInteger q,BigInteger w);
};


BigInteger gcd(BigInteger q,BigInteger w){
	while (q.sign and w.sign){
		q%=w;
		if (q.sign and w.sign){
			w%=q;
		}
	}
	if (q.sign){
		return q;
	}
	return w;
}


class Rational{
#if __has_include("h")
public:
#endif
	BigInteger n=0;
	BigInteger d=1;
	void norm(){
		auto g=gcd(n,d);
		n/=g;
		d/=g;
		if (d<BigInteger(0)){
			n*=-1;
			d*=-1;
		}
	}
public:
	Rational(const int&q=0){
		_2ac_(q)
		n=q;
	}
	Rational(const BigInteger&q){
		_2ac_(q)
		n=q;
	}
	Rational(const std::string&orig,int t=10){
		auto h=orig.find('/');
		if (h==orig.npos){
			n=BigInteger(orig,t);
		}else{
			n=BigInteger(std::string(orig.begin(),orig.begin()+h),t);
			d=BigInteger(std::string(orig.begin()+h+1,orig.end()),t);
			norm();
		}
	}
	Rational(const char*a){
		*this=Rational(std::string(a));
	}
	auto&operator+=(const Rational&e){
		_1ac_t(e)
		n*=e.d;
		n+=e.n*d;
		d*=e.d;
		norm();
		return *this;
	}
	friend auto operator+(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		auto t=q;
		t+=e;
		return t;
	}
	auto&operator-=(const Rational&e){
		_1ac_t(e)
		n*=e.d;
		n-=e.n*d;
		d*=e.d;
		norm();
		return *this;
	}
	friend auto operator-(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		auto t=q;
		t-=e;
		return t;
	}
	auto&operator*=(const Rational&e){
		_1ac_t(e)
		n*=e.n;
		d*=e.d;
		norm();
		return *this;
	}
	friend auto operator*(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		auto t=q;
		t*=e;
		return t;
	}
	auto&operator/=(const Rational&e){
		_1ac_t(e)
		n*=e.d;
		d*=e.n;
		norm();
		return *this;
	}
	friend auto operator/(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		auto t=q;
		t/=e;
		return t;
	}
	auto operator-()const{
		_3a_t
		return Rational(-n)/d;
	}
	friend bool operator<(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d<q.d*e.n;
	}
	friend bool operator>(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d>q.d*e.n;
	}
	friend bool operator==(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d==q.d*e.n;
	}
	friend bool operator<=(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d<=q.d*e.n;
	}
	friend bool operator!=(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d!=q.d*e.n;
	}
	friend bool operator>=(const Rational&q,const Rational&e){
		_2ac_(q)
		_2ac_(e)
		return q.n*e.d>=q.d*e.n;
	}
	auto toString()const{
		// _3a_t
		auto h=n.toString();
		if (d!=BigInteger(1)){
			h+="/"+d.toString();
		}
		return h;
	}
	operator std::string()const{
		return this->toString();
	}
	friend std::ostream&operator<<(std::ostream&q,const Rational&w){
		q<<w.toString();
		return q;
	}
	auto asDecimal(const size_t&p){
		_1ac_t(p)
		auto t=n;
		auto ts=t<0?-1:1;
		t*=ts;
		for (size_t w=0;w<p;++w){
			t*=10;
		}
		t/=d;
		auto h=t.toString();
		while (h.size()<p+1){
			h="0"+h;
		}
		h=std::string(h.begin(),h.end()-p)+"."+std::string(h.end()-p,h.end());
		if (ts==-1){
			h="-"+h;
		}
		return h;
	}
	#if __has_include("h")
	auto operator%(const Rational&_p){
		return this->asDecimal(stol(str(_p)));
	}
	#endif
	explicit operator double(){
		_3a_t
		return stold(n.toString())/stold(d.toString());
	}
};


#ifdef CPP_R
std::string print_one(BigInteger&q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"\x1b[92m%s\x1b[0m",1==q.sign?"+":-1==q.sign?"-":1<q.sign?"++":-1>q.sign?"--":"0");
	int c=0;
	for (int t=q.size-1;t>-1;--t){
		if (c%2){
			sprintf(b+strlen(b),"\x1b[92m");
		}
		sprintf(b+strlen(b),"%0*x",8,q.vect[t]);
		if (c%2){
			sprintf(b+strlen(b),"\x1b[0m");
		}
		++c;
	}
	return std::string(b);
}

std::string print_one(const BigInteger&q){
	return print_one(const_cast<BigInteger&>(q));
}
#endif