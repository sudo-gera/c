#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
template <typename T>
class bits{
public:
	T val=0;
	bool get_bit(size_t bit)const{
		return (val>>bit)&1;
	}
	void set_bit(size_t bit,bool vb){
		size_t v=vb;
		val|=1LLU<<bit;
		val-=1LLU<<bit;
		val+=(1LLU<<bit)*v;
	}
	void set_one(size_t bit){
		val|=1LLU<<bit;
	}
	void set_zer(size_t bit){
		val&=~(1LLU<<bit);
	}
	void inv_bit(size_t bit){
		val^=1LLU<<bit;
	}
	bool chk_bit(size_t bit,bool vb)const{
		return vb==get_bit(bit);
	}
	size_t cnt_one()const{
		size_t r=0;
		for (size_t w=0;w<sizeof(val)*8;++w){
			r+=get_bit(w);
		}
		return r;
	}
	size_t cnt_zer()const{
		return sizeof(val)*8-cnt_one();
	}
	size_t cnt_bit(bool vb)const{
		if (vb){
			return cnt_one();
		}else{
			return cnt_zer();
		}
	}
	operator std::string()const{
		std::string r="";
		for (size_t w=0;w<sizeof(val)*8;++w){
			r+=(char)('0'+get_bit(w));
		}
		return r;
	}
	size_t size(){
		return sizeof(val)*8;
	}
};

template<typename T>
auto&operator<<(std::ostream& out,const bits<T>&d){
	out<<std::string(d);
	return out;
}

template<typename T>
void check(){
	bits<T> a;
	assert(a.cnt_one()==0);
	assert(a.cnt_bit(1)==0);
	for (size_t w=0;w*w<a.size();++w){
		a.inv_bit(w*w);
	}
	for (size_t w=0;w<a.size();++w){
		assert(a.chk_bit(w,T(std::sqrt(w))*T(std::sqrt(w))==w));
	}
	for (size_t w=0;w*w<a.size();w+=2){
		a.set_zer(w*w);
	}
	for (size_t w=0;w<a.size();++w){
		assert(a.chk_bit(w,w%2 and T(std::sqrt(w))*T(std::sqrt(w))==w));
	}
	for (size_t w=0;w*w<a.size();w+=2){
		a.set_one(w*w);
	}
	for (size_t w=0;w<a.size();++w){
		if (a.get_bit(w)){
			size_t e=w+1;
			for (;e<a.size() and a.get_bit(e)==0;++e){}
			if (e<a.size()){
				e=(e-w)/2;
				e*=e;
				assert(w==e);
			}
		}
	}
	assert(a.cnt_one()+a.cnt_zer()==a.size());
	for (size_t w=0;w*w<a.size();w+=2){
		a.set_bit(w*w,0);
	}
	for (size_t w=0;w<a.size();++w){
		assert(a.chk_bit(w,w%2 and T(std::sqrt(w))*T(std::sqrt(w))==w));
	}
	for (size_t w=1;w*w<a.size();w+=2){
		a.set_bit(w*w,0);
	}
	assert(a.cnt_one()==0);
	assert(a.cnt_bit(1)==0);
	auto s=std::string(a);
	assert(s.find('1')==s.npos);
	std::stringstream ss;
	ss<<a;
	assert(ss.str()==s); 
}

int main(){
	check<int>();
	check<long>();
	check<signed char>();
	check<unsigned>();
}
