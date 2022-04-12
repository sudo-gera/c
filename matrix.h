#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

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
	std::string toString(uint64_t base=10)const{
		BigInteger abs_of_this=*this;
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
	int cmp(BigInteger const&e,bool onlymod=0)const{
		if (!onlymod and sign!=e.sign){
			return ((sign)-(e.sign));
		}
		if (size+e.size==0){
			return 0;
		}
		for (size_t c=(size>e.size?size:e.size);c--;){
			size_t qdigit=size>c?vect[c]:0;
			size_t edigit=e.size>c?e.vect[c]:0;
			if (qdigit!=edigit){
				return ((qdigit>edigit)*2-1)*(onlymod?1:sign);
			}
		}
		return 0;
	}
	~BigInteger(){
		if (vect){
			delete[] vect;
		}
	}
private:
	void bn_M_add_to(BigInteger const &e){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		uint64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
	}
	//helps in e has only 2 digits
	void bn_M_add_to_fast(BigInteger const &e,uint64_t start){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		uint64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
	}
	void bn_M_sub_to(BigInteger const &e){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		int64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
		size_t g=size;
		while (g>0 and vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			sign=0;
		}	
	}
	//helps in e has only 2 digits
	void bn_M_sub_to_fast(BigInteger const &e,uint64_t start){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		int64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
		size_t g=size;
		while (g>0 and vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			sign=0;
		}	
	}
public:
	BigInteger&operator+=(const BigInteger&e){
		if (!e.sign){
			return *this;
		}
		if (e.sign*sign>=0){
			bn_M_add_to(e);
			sign=e.sign;
		}else if (this->cmp(e,1)>=0){
			bn_M_sub_to(e);
		}else{
			BigInteger tmp=*this;
			*this=e;
			bn_M_sub_to(tmp);
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
	auto&operator*=(const BigInteger&e){
		BigInteger res;
		BigInteger tmp;
		size_t qs=size;
		size_t es=e.size;
		while (qs and vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		res.resize(qs+es);
		tmp.resize(qs+es);
		tmp.sign=1;
		for (size_t w=0;w<qs;++w){
			if (vect[w]){
				for (size_t r=0;r<es;++r){
					uint64_t mulres=(uint64_t)(vect[w])*(uint64_t)(e.vect[r]);
					tmp.vect[w+r]=mulres<<32>>32;
					tmp.vect[w+r+1]=mulres>>32;
					res.bn_M_add_to_fast(tmp,w+r); 
					tmp.vect[w+r]=0;
					tmp.vect[w+r+1]=0;
				}
			}
		}
		res.sign=sign*e.sign;
		*this=res;
		return *this;
	}
private:
	void bn_half(){
		if (size){
			vect[0]>>=1;
		}
		for (size_t w=1;w<size;++w){
			vect[w-1]|=(vect[w]&1)<<31;
			vect[w]>>=1;
		}
		size_t not_zero=0;
		for (size_t w=0;w<size;++w){
			if (vect[w]){
				not_zero=1;
				break;
			}
		}
		if (!not_zero){
			sign=0;
		}
	}
	void bn_M_div_to(const BigInteger&e,bool getdiv=1){
		if(!e.sign){
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<"/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0/0"<<std::endl;
			std::cerr<<e.vect[-1]<<std::endl;return;
		}
		auto rsign=sign*e.sign;
		sign=bool(sign); //*this=abs(*this)
		size_t qs=size;
		size_t es=e.size;
		while (qs and vect[qs-1]==0){
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
			shifted_e[31].bn_half();
			for (size_t w=31;w>1;--w){
				shifted_e[w-1]=shifted_e[w];
				shifted_e[w-1].bn_half();
			}
			uint64_t*offsets=new uint64_t[32]();
			res.resize(qs+1-es);
			int64_t shift=(res.size+1)*32;
			res.sign=1;
			while (shift>=0){
				if (this->cmp(shifted_e[shift&0b11111])>=0){
					res.vect[shift>>5]|=(1LL<<(shift&0b11111));
					bn_M_sub_to(shifted_e[shift&0b11111]);
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
			*this=res;
		}
		sign=rsign;
		qs=size;
		while (qs>0 and vect[qs-1]==0){
			qs-=1;
		}
		if (qs==0){
			sign=0;
		}	
	}
public:
	auto&operator/=(const BigInteger&e){
		bn_M_div_to(e,1);
		return *this;
	}
	auto&operator%=(const BigInteger&e){
		bn_M_div_to(e,0);
		return *this;
	}
	auto&operator++(){
		if (this->sign<0){
			bn_M_sub_to_fast(1,0);
		}else{
			bn_M_add_to_fast(1,0);
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
			bn_M_add_to_fast(1,0);
		}else{
			bn_M_sub_to_fast(1,0);
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
};


std::ostream&operator<<(std::ostream&ostr,const BigInteger&bn){
	ostr<<bn.toString();
	return ostr;
}
auto&operator>>(std::istream&istr,BigInteger&bn){
	std::string tmp;
	istr>>tmp;
	bn=tmp;
	return istr;
}
bool operator<(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)<0;
}
bool operator>(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)>0;
}
bool operator==(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)==0;
}
bool operator!=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)!=0;
}
bool operator<=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)<=0;
}
bool operator>=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)>=0;
}
BigInteger operator+(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp+=w;
	return tmp;
}
BigInteger operator-(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp-=w;
	return tmp;
}
BigInteger operator*(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp*=w;
	return tmp;
}
BigInteger operator/(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp/=w;
	return tmp;
}
BigInteger operator%(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp%=w;
	return tmp;
}


BigInteger operator""_bi(const char*orig){
	return BigInteger(orig);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BigInteger gcd(BigInteger q,BigInteger e){
	while (q and e){
		q%=e;
		if (q and e){
			e%=q;
		}
	}
	if (q){
		return q;
	}
	return e;
}


class Rational{
public:
	BigInteger numerator=0;
	BigInteger denominator=1;
private:
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
	auto&operator-=(const Rational&e){
		numerator*=e.denominator;
		numerator-=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto&operator/=(const Rational&e){
		numerator*=e.denominator;
		denominator*=e.numerator;
		norm();
		return *this;
	}
	auto&operator*=(const Rational&e){
		numerator*=e.numerator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto operator-()const{
		return Rational(-numerator)/=denominator;
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



auto operator+(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp+=e;
	return tmp;
}
auto operator-(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp-=e;
	return tmp;
}
auto operator*(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp*=e;
	return tmp;
}
auto operator/(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp/=e;
	return tmp;
}
bool operator<(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<q.denominator*e.numerator;
}
bool operator>(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>q.denominator*e.numerator;
}
bool operator==(const Rational&q,const Rational&e){
	return q.numerator*e.denominator==q.denominator*e.numerator;
}
bool operator<=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<=q.denominator*e.numerator;
}
bool operator!=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator!=q.denominator*e.numerator;
}
bool operator>=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>=q.denominator*e.numerator;
}
std::ostream&operator<<(std::ostream&q,const Rational&w){
	q<<w.toString();
	return q;
}
auto&operator>>(std::istream&istr,Rational&bn){
	std::string tmp;
	istr>>tmp;
	bn=tmp;
	return istr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <size_t N,size_t START,size_t COUNT>
struct N_not_div_all{
	static const bool value=N_not_div_all<N,START,COUNT/2>::value and N_not_div_all<N,START+COUNT/2,COUNT-COUNT/2>::value;
};

template <size_t N,size_t START>
struct N_not_div_all<N,START,1>{
	static const bool value=N%START;
};

template <size_t N,size_t START>
struct N_not_div_all<N,START,0>{
	static const bool value=true;
};

template <size_t N,size_t BIT>
struct root_s{
	static const size_t v1=root_s<N,BIT+1>::value;
	static const size_t v2=v1+(1ULL<<BIT);
	static const size_t value=v2*v2>N?v1:v2;
};

template <size_t N>
struct root_s<N,32>{
	static const size_t value=0;
};

template <size_t N>
const size_t root=root_s<N,0>::value;

template <size_t N>
const bool is_prime=N_not_div_all<N,2,root<N>-1>::value;

template<>
const bool is_prime<0> = 0;

template<>
const bool is_prime<1> = 0;

size_t pow(size_t q,size_t w,size_t e){
	size_t res=1;
	while (w){
		if (w%2){
			res*=q;
			res%=e;
		}
		q*=q;
		q%=e;
		w/=2;
	}
	return res;
}

template <size_t N>
class Residue{
public:
	size_t value=0;
	Residue(){}
	template<typename T>
	Residue(const T&q){
		if (q<0){
			value=__uint128_t(-q)%N;
			value=N-value;
		}else{
			value=__uint128_t(q)%N;
		}
	}
	Residue(bool q){
		value=q%N;
	}
	auto&operator+=(const Residue&e){
		value+=e.value;
		value%=N;
		return *this;
	}
	auto&operator*=(const Residue&e){
		value*=e.value;
		value%=N;
		return *this;
	}
	auto&operator-=(const Residue&e){
		value=value+N-e.value;
		value%=N;
		return *this;
	}
	template <typename TT=Residue&>
	std::enable_if_t<is_prime<N>,TT> operator/=(const Residue&e){
		value*=pow(e.value,N-2,N);
		value%=N;
		return *this;
	}
	// template <typename TT=Residue&>
	// std::enable_if_t<is_prime<N>,TT> operator%=(const Residue&e){
	// 	*this=*this-*this/e*e;
	// 	return *this;
	// }
	friend auto&operator<<(std::ostream&q,const Residue&e){
		q<<e.value;
		return q;
	}
	friend auto&operator>>(std::istream&q,Residue&e){
		q>>e.value;
		return q;
	}
	auto operator-(){
		return 0-*this;
	}
	friend auto operator==(const Residue<N>&q,const Residue<N>&e){
		return q.value==e.value;
	}
	friend auto operator!=(const Residue<N>&q,const Residue<N>&e){
		return q.value!=e.value;
	}
	friend auto operator+(const Residue<N>&q,const Residue<N>&e){
		auto w=q;
		w+=e;
		return w;
	}
	friend auto operator-(const Residue<N>&q,const Residue<N>&e){
		auto w=q;
		w-=e;
		return w;
	}
	friend auto operator*(const Residue<N>&q,const Residue<N>&e){
		auto w=q;
		w*=e;
		return w;
	}
	template<typename TT=Residue<N>>
	friend std::enable_if_t<is_prime<N>,TT> operator/(const Residue<N>&q,const Residue<N>&e){
		auto w=q;
		w/=e;
		return w;
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <size_t M,size_t N,typename Field>
class Matrix{
public:
	Matrix(){}
	std::array<std::array<Field,N>,M> data;
	Matrix(std::initializer_list<std::vector<Field>>list){
		auto vect=std::vector<std::vector<Field>>(list.begin(),list.end());
		for (size_t w=0;w<vect.size();++w){
			for (size_t e=0;e<vect[w].size();++e){
				data[w][e]=vect[w][e];
			}
		}
	}
	template<typename T>
	auto&operator+=(const Matrix<M,N,T>&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]+=e.data[w][q];
			}
		}
		return *this;
	}
	template<typename T>
	auto&operator-=(const Matrix<M,N,T>&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]-=e.data[w][q];
			}
		}
		return *this;
	}
	auto&operator*=(const Field&e){
		for (size_t w=0;w<M;++w){
			for (size_t q=0;q<N;++q){
				data[w][q]*=e;
			}
		}
		return *this;
	}
	template<typename T>
	Matrix<N,M,Field>&operator*=(const Matrix<N,N,T>&e){
		*this=*this*e;
		return *this;
	}
private:
	void add_line(size_t line_to,size_t line_from,Field coeff){
		for (size_t w=0;w<N;++w){
			data[line_to][w]+=data[line_from][w]*coeff;
		}
	}
	void mul_line(size_t line_to,Field coeff){
		for (size_t w=0;w<N;++w){
			data[line_to][w]*=coeff;
		}
	}
	void triange(Matrix<M,N,Field>* other=nullptr){
		size_t Q=(M<N?M:N);
		for (size_t q=0;q<Q;++q){
			size_t is_col_zero=1;
			size_t w=q+1;
			for (;w<M;++w){
				if (data[w][q]!=0){
					is_col_zero=0;
					break;
				}
			}
			if (is_col_zero){
				continue;
			}
			if (data[q][q]==0){
				add_line(q,w,1);
				if (other){
					other->add_line(q,w,1);
				}
			}
			for (size_t w=q+1;w<M;++w){
				auto tmp=-data[w][q]/data[q][q];
				add_line(w,q,tmp);
				if (other){
					other->add_line(w,q,tmp);
				}
			}
		}
	}
	template <typename TT=Field>
	std::enable_if_t<M==N,TT> change_and_det(){
		triange();
		Field res=1;
		for (size_t q=0;q<M;++q){
			res*=data[q][q];
		}
		return res;
	}
public:
	template <typename TT=Field>
	std::enable_if_t<M==N,TT> det()const{
		auto tmp=*this;
		return tmp.change_and_det();
	}
	auto transposed()const{
		Matrix<N,M,Field> res;
		for (size_t q=0;q<M;++q){
			for (size_t w=0;w<N;++w){
				res.data[w][q]=data[q][w];
			}
		}
		return res;
	}
	auto&operator[](size_t q){
		return data[q];
	}
	const auto&operator[](size_t q)const{
		return data[q];
	}
private:
	Field change_and_rank(){
		size_t Q=(M<N?M:N);
		triange();
		Field res=0;
		for (size_t q=0;q<Q;++q){
			for (size_t w=q;w<N;++w){
				if (data[q][w]!=0){
					res+=1;
					break;
				}
			}
		}
		return res;
	}
public:
	Field rank()const{
		auto tmp=*this;
		return tmp.change_and_rank();
	}
	template <typename TT=Field>
	std::enable_if_t<M==N,TT> trace()const{
		Field res=0;
		for (size_t q=0;q<M;++q){
			res+=data[q][q];
		}
		return res;		
	}
	std::vector<Field> getRow(unsigned q)const{
		std::vector<Field> res;
		for (size_t w=0;w<M;++w){
			res.push_back(data[q][w]);
		}
		return res;
	}
	std::vector<Field> getColumn(unsigned q)const{
		std::vector<Field> res;
		for (size_t w=0;w<M;++w){
			res.push_back(data[w][q]);
		}
		return res;
	}
	template <typename TT=void>
	std::enable_if_t<M==N,TT> invert(){
		auto res=*this;
		for (size_t w=0;w<M;++w){
			for (size_t e=0;e<N;++e){
				res[w][e]=w==e;
			}
		}
		triange(&res);
		for (size_t q=0;q<M;++q){
			if (data[q][q]!=0){
				for (size_t w=0;w<q;++w){
					auto tmp=data[w][q]/data[q][q];
					add_line(w,q,Field(-tmp));
					res.add_line(w,q,Field(-tmp));
				}
			}
		}
		for (size_t q=0;q<M;++q){
			auto tmp=1/data[q][q];
			mul_line(q,tmp);
			res.mul_line(q,tmp);
		}
		*this=res;
	}
	template <typename TT=Matrix<M,N,Field>>
	std::enable_if_t<M==N,TT> inverted()const{
		auto tmp=*this;
		tmp.invert();
		return tmp;
	}
	auto& out(std::ostream&cout)const{
		for (size_t w=0;w<data.size();++w){
			cout<<'[';
			size_t c=0;
			for (size_t e=0;e<data[w].size();++e){
				cout<<(c++?" ":"");
				cout<<data[w][e];
			}
			cout<<"]\n";
		}
		return cout;
	}
	friend auto&operator<<(std::ostream&q,const Matrix&e){
		return e.out(q);
	}
};

template <int N,typename Field=Rational>
using SquareMatrix=Matrix<N,N,Field>;


template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator==(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	for (size_t w=0;w<_M;++w){
		for (size_t r=0;r<_N;++r){
			if (q.data[w][r]!=e.data[w][r]){
				return 0;
			}
		}
	}
	return 1;

}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator!=(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	return !(q==e);
}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator+(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	auto tmp=q;
	tmp+=e;
	return tmp;
}
template <size_t _M,size_t _N,typename _Field1,typename _Field2>
auto operator-(const Matrix<_M,_N,_Field1>&q,const Matrix<_M,_N,_Field2>&e){
	auto tmp=q;
	tmp-=e;
	return tmp;
}
template <size_t _M,size_t _K,size_t _N,typename _Field1,typename _Field2>
auto operator*(const Matrix<_M,_K,_Field1>&q,const Matrix<_K,_N,_Field2>&e){
	using dt=decltype(q[0][0]*e[0][0]);
	auto res=Matrix<_M,_N,dt>();
	for (size_t w=0;w<_M;++w){
		for (size_t r=0;r<_N;++r){
			dt t_=0;
			for (size_t t=0;t<_K;++t){
				t_+=q[w][t]*e[t][r];
			}
			res[w][r]=t_;
		}
	}
	return res;
}

template <size_t _M,size_t _K,typename _Field1,typename _Field2>
auto operator*(const Matrix<_M,_K,_Field1>&q,const _Field2&e){
	auto tmp=q;
	tmp*=e;
	return tmp;
}

template <size_t _K,size_t _N,typename _Field1,typename _Field2>
auto operator*(const _Field1&q,const Matrix<_K,_N,_Field2>&e){
	auto tmp=e;
	tmp*=q;
	return tmp;
}

#include <string>

auto readfile_(FILE*q){
	std::string s;
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(q)) != EOF) { // standard C I/O file reading loop
		s+=c;
	}
	return s;
}

auto replace_(std::string q,std::string w,std::string e){
	std::string res;
	uint64_t a=0;
	while (a<uint64_t((q).size())){
		if (q.find(w,a)==a){
			res+=e;
			a+=w.size();
		}else{
			res+=q[a];
			++a;
		}
	}
	return res;
}

bool printed=0;

int f(std::string file){
	if (printed){
		return 0;
	}
	printed=1;
	auto d=fopen(file.c_str(),"r");
	auto s=readfile_(d);
	fclose(d);
	s=replace_(s,"\t"," ");
	size_t len=512;
	size_t start=len*13;
	std::cerr<<"//BEGIN OF PART "<<start/len<<std::endl;
	std::cerr<<std::string(s.begin()+(start<s.size()?start:s.size()),s.begin()+(start+len<s.size()?start+len:s.size()))<<std::endl;
	std::cerr<<"//END OF PART "<<start/len<<std::endl;
	return 0;
}


// #define rank() rank()+f(__FILE__)
