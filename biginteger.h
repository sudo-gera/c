#include <iostream>
#include <string>


class BigInteger{
	int8_t sign=0;
	size_t size=0;
	uint32_t *vect=nullptr;
public:
	BigInteger(){
	}
private:
	void resize(size_t q){
		if (size<q){
			auto tmp=new uint32_t[q]();
			for (size_t w=0;w<size;++w){
				tmp[w]=vect[w];
			}
			if (vect){
				delete[] vect;
			}
			vect=tmp;
			size=q;
		}
	}
public:
	BigInteger(const BigInteger& orig){
		resize(orig.size);
		size=orig.size;
		sign=orig.sign;
		for (size_t w=0;w<size;++w){
			vect[w]=orig.vect[w];
		}
	}
	BigInteger(const int&orig){
		resize(1);
		sign=orig>0?1:orig<0?-1:0;
		vect[0]=sign*orig;
	}
	auto&operator=(const BigInteger&orig){
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
	BigInteger(const char*orig,int base=10){
		*this=BigInteger(static_cast<std::string>(orig),base);
	}
	BigInteger(const std::string&orig,int64_t base=10){
		resize(orig.size()/"\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"
			[base]+1); //optimal digit count, int(ln(2^32)/ln(base))
		sign=0;
		bool starts_with_minus_sign=0;
		if (orig.size() and orig[0]=='-'){
			starts_with_minus_sign=1;
		}
		auto symbol_to_code="------------------------------------------------\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09-------\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23------\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23-----";
		//string has \x00\x01... at positions '0','1',... and \x0a\x0b... at positions 'a','b',... and 'A','B',... symbol_to_code['0'] is 0, symbol_to_code['a'] is 10
		for (size_t w=starts_with_minus_sign;w<orig.size();++w){
			*this*=base;
			*this+=symbol_to_code[static_cast<int>(orig[w])];  
		}
		if (starts_with_minus_sign){
			sign*=-1;
		}
	}
	friend std::ostream&operator<<(std::ostream&ostr,const BigInteger&bn){
		ostr<<bn.toString();
		return ostr;
	}
	friend auto&operator>>(std::istream&istr,BigInteger&bn){
		std::string tmp;
		istr>>tmp;
		bn=tmp;
		return istr;
	}
	std::string toString(uint64_t base=10)const{
		BigInteger abs_of_this;
		abs_of_this=*this;
		abs_of_this.sign=bool(abs_of_this.sign);
		std::string res;
		while (abs_of_this.sign){
			uint64_t buff=0;
			uint64_t tmp=0;
			for (size_t w=abs_of_this.size;w>0;--w){
				tmp=abs_of_this.vect[w-1];
				tmp+=buff<<32;
				buff=tmp%base;
				tmp/=base;
				abs_of_this.vect[w-1]=tmp;
			}
			abs_of_this.sign=0;
			for (size_t _w=abs_of_this.size;_w>0;--_w){size_t w=_w-1;
				if (abs_of_this.vect[w]){
					abs_of_this.sign=1;
					break;
				}
			}
			res.push_back(buff);
		}
		auto code_to_symbol="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		//code_to_symbol[0] is '0', code_to_symbol[10] is 'A'
		for (size_t w=0;w<res.size();++w){
			res[w]=code_to_symbol[static_cast<int>(res[w])];
		}
		if (sign<0){
			res.push_back('-');
		}
		if (!res.size()){
			res.push_back('0');
		}
		for (size_t w=0;w*2<res.size();++w){
			char tmp=res[w];
			res[w]=res[res.size()-1-w];
			res[res.size()-1-w]=tmp;
		}
		return res;
	}
	operator std::string()const{
		return this->toString();
	}
private:
	friend int cmp(BigInteger const&q,BigInteger const&e,bool onlymod=0){
		if (!onlymod and q.sign!=e.sign){
			return ((q.sign)-(e.sign));
		}
		if (q.size+e.size==0){
			return 0;
		}
		for (size_t c=(q.size>e.size?q.size:e.size);c--;){
			size_t qdigit=q.size>c?q.vect[c]:0;
			size_t edigit=e.size>c?e.vect[c]:0;
			if (qdigit!=edigit){
				return ((qdigit>edigit)*2-1)*(onlymod?1:q.sign);
			}
		}
		return 0;
	}
public:
	friend bool operator<(BigInteger const&q,BigInteger const&e){
		return cmp(q,e)<0;
	}
	friend bool operator>(BigInteger const&q,BigInteger const&e){
		return cmp(q,e)>0;
	}
	friend bool operator==(BigInteger const&q,BigInteger const&e){
		return cmp(q,e)==0;
	}
	friend bool operator!=(BigInteger const&q,BigInteger const&e){
		return cmp(q,e)!=0;
	}
	friend bool operator<=(BigInteger const&q,BigInteger const&e){
		return cmp(q,e)<=0;
	}
	friend bool operator>=(BigInteger const&q,BigInteger const&e){
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
	//helps in e has only 2 digits
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
	//helps in e has only 2 digits
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
		if (!e.sign){
			return *this;
		}
		if (e.sign*sign>=0){
			bn_M_add_to(*this,e);
			sign=e.sign;
		}else if (cmp(*this,e,1)>=0){
			bn_M_sub_to(*this,e);
		}else{
			BigInteger tmp=*this;
			*this=e;
			bn_M_sub_to(*this,tmp);
		}
		size_t ts=size;
		while (ts>0 and vect[ts-1]==0){
			ts-=1;
		}
		if (ts==0){
			sign=0;
		}
		return *this;
	}
	BigInteger&operator-=(const BigInteger&e){
		sign*=-1;
		*this+=e;
		sign*=-1;
		return *this;
	}
	friend BigInteger operator+(const BigInteger&q,const BigInteger&w){
		auto tmp=q;
		tmp+=w;
		return tmp;
	}
	friend BigInteger operator-(const BigInteger&q,const BigInteger&w){
		auto tmp=q;
		tmp-=w;
		return tmp;
	}
	friend BigInteger operator*(BigInteger const&q,const BigInteger&e){
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
		size_t not_zero=0;
		for (size_t w=0;w<q.size;++w){
			if (q.vect[w]){
				not_zero=1;
				break;
			}
		}
		if (!not_zero){
			q.sign=0;
		}
	}
	friend std::string print_one(BigInteger&q);
	friend std::string print_one(const BigInteger&q);
	friend void bn_M_div_to(BigInteger&q,const BigInteger&e,bool getdiv=1){
		if(!e.sign){std::cerr<<"zero"<<std::flush;return;}
		auto rsign=q.sign*e.sign;
		q.sign=bool(q.sign); //q=abs(q)
		size_t qs=q.size;
		size_t es=e.size;
		while (qs and q.vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		BigInteger res;
		if (qs>=es){
			BigInteger*shifted_e=new BigInteger[32];
			shifted_e[0].resize(qs+2);
			shifted_e[0].sign=1;
			for(size_t w=0;w<es;++w){
				shifted_e[0].vect[qs-es+2+w]=e.vect[w];
			}
			shifted_e[31]=shifted_e[0];
			bn_half(shifted_e[31]);
			for (size_t w=31;w>1;--w){
				shifted_e[w-1]=shifted_e[w];
				bn_half(shifted_e[w-1]);
			}
			uint64_t*offsets=new uint64_t[32]();
			res.resize(qs+1-es);
			int64_t shift=(res.size+1)*32;
			res.sign=1;
			while (shift>=0){
				if (q>=shifted_e[shift&0b11111]){
					res.vect[shift>>5]|=(1LL<<(shift&0b11111));
					bn_M_sub_to(q,shifted_e[shift&0b11111]);
				}
				shifted_e[shift&0b11111].size-=1;
				shifted_e[shift&0b11111].vect+=1;
				offsets[shift&0b11111]+=1;
				shift-=1;
			}
			size_t rs=res.size;
			while (rs and res.vect[rs-1]==0){
				--rs;
			}
			if (!rs){
				res.sign=0;
			}
			for (size_t w=0;w<32;++w){
				shifted_e[w].vect-=offsets[w];
			}
			delete[] offsets;
			delete[] shifted_e;
		}
		if (getdiv){
			q=res;
		}
		q.sign=rsign;
		qs=q.size;
		while (qs>0 and q.vect[qs-1]==0){
			qs-=1;
		}
		if (qs==0){
			q.sign=0;
		}	
	}
public:
	auto&operator/=(const BigInteger&e){
		bn_M_div_to(*this,e,1);
		return *this;
	}
	auto&operator%=(const BigInteger&e){
		bn_M_div_to(*this,e,0);
		return *this;
	}

	friend BigInteger operator/(const BigInteger&q,const BigInteger&w){
		auto tmp=q;
		tmp/=w;
		return tmp;
	}
	friend BigInteger operator%(const BigInteger&q,const BigInteger&w){
		auto tmp=q;
		tmp%=w;
		return tmp;
	}

	auto&operator++(){
		if (this->sign<0){
			bn_M_sub_to_fast(*this,1,0);
		}else{
			bn_M_add_to_fast(*this,1,0);
		}
		return *this;
	}
	auto operator++(int){
		auto tmp=*this;
		++*this;
		return tmp;
	}
	auto&operator--(){
		if (this->sign<0){
			bn_M_add_to_fast(*this,1,0);
		}else{
			bn_M_sub_to_fast(*this,1,0);
		}
		return *this;
	}
	auto operator--(int){
		auto tmp=*this;
		--*this;
		return tmp;
	}
	auto operator-()const{
		BigInteger g=*this;
		g.sign*=-1;
		return g;
	}
	explicit operator bool(){
		return this->sign;
	}
	friend BigInteger gcd(BigInteger q,BigInteger w);
};


BigInteger operator""_bi(const char*orig){
	return BigInteger(orig);
}


BigInteger gcd(BigInteger q,BigInteger e){
	while (q.sign and e.sign){
		q%=e;
		if (q.sign and e.sign){
			e%=q;
		}
	}
	if (q.sign){
		return q;
	}
	return e;
}


class Rational{
	BigInteger numerator=0;
	BigInteger denominator=1;
	void norm(){
		auto g=gcd(numerator,denominator);
		numerator/=g;
		denominator/=g;
		if (denominator<BigInteger(0)){
			numerator*=-1;
			denominator*=-1;
		}
	}
public:
	Rational(const int&q=0){
		numerator=q;
	}
	Rational(const BigInteger&q){
		numerator=q;
	}
	Rational(const std::string&orig,int base=10){
		auto slash_index=orig.find('/');
		if (slash_index==orig.npos){
			numerator=BigInteger(orig,base);
		}else{
			numerator=BigInteger(std::string(orig.begin(),orig.begin()+slash_index),base);
			denominator=BigInteger(std::string(orig.begin()+slash_index+1,orig.end()),base);
			norm();
		}
	}
	Rational(const char*a){
		*this=Rational(std::string(a));
	}
	auto&operator+=(const Rational&e){
		numerator*=e.denominator;
		numerator+=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	friend auto operator+(const Rational&q,const Rational&e){
		auto tmp=q;
		tmp+=e;
		return tmp;
	}
	auto&operator-=(const Rational&e){
		numerator*=e.denominator;
		numerator-=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	friend auto operator-(const Rational&q,const Rational&e){
		auto tmp=q;
		tmp-=e;
		return tmp;
	}
	auto&operator*=(const Rational&e){
		numerator*=e.numerator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	friend auto operator*(const Rational&q,const Rational&e){
		auto tmp=q;
		tmp*=e;
		return tmp;
	}
	auto&operator/=(const Rational&e){
		numerator*=e.denominator;
		denominator*=e.numerator;
		norm();
		return *this;
	}
	friend auto operator/(const Rational&q,const Rational&e){
		auto tmp=q;
		tmp/=e;
		return tmp;
	}
	auto operator-()const{
		return Rational(-numerator)/denominator;
	}
	friend bool operator<(const Rational&q,const Rational&e){
		return q.numerator*e.denominator<q.denominator*e.numerator;
	}
	friend bool operator>(const Rational&q,const Rational&e){
		return q.numerator*e.denominator>q.denominator*e.numerator;
	}
	friend bool operator==(const Rational&q,const Rational&e){
		return q.numerator*e.denominator==q.denominator*e.numerator;
	}
	friend bool operator<=(const Rational&q,const Rational&e){
		return q.numerator*e.denominator<=q.denominator*e.numerator;
	}
	friend bool operator!=(const Rational&q,const Rational&e){
		return q.numerator*e.denominator!=q.denominator*e.numerator;
	}
	friend bool operator>=(const Rational&q,const Rational&e){
		return q.numerator*e.denominator>=q.denominator*e.numerator;
	}
	auto toString()const{
		auto res=numerator.toString();
		if (denominator!=BigInteger(1)){
			res+="/"+denominator.toString();
		}
		return res;
	}
	operator std::string()const{
		return this->toString();
	}
	friend std::ostream&operator<<(std::ostream&q,const Rational&w){
		q<<w.toString();
		return q;
	}
	auto asDecimal(const size_t&p){
		auto tmp=numerator;
		auto tsign=tmp<0?-1:1;
		tmp*=tsign;
		for (size_t w=0;w<p;++w){
			tmp*=10;
		}
		tmp/=denominator;
		auto res=tmp.toString();
		while (res.size()<p+1){
			res="0"+res;
		}
		res=std::string(res.begin(),res.end()-p)+"."+std::string(res.end()-p,res.end());
		if (tsign==-1){
			res="-"+res;
		}
		return res;
	}
	explicit operator double(){
		return stold(numerator.toString())/stold(denominator.toString());
	}
};
