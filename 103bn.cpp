#ifndef C_R
#define CPP_R
#endif


#define NORMAL_SIZE 0

#define ERRORS 0


#define COLORS 1


#ifdef CPP_R
// #include "bn.h"
// #include "d"
#endif

#ifdef C_R
// #include "bn.h"
// #include "d"
#endif




#ifdef CPP_R
#include "bn.c"
#endif

#ifdef C_R
#include "bn.c"
#endif


#include <string>
using std::string;
#ifdef CPP_R
void bn_init_str(bn *q,string e){
	if (q->vect){
		free(q->vect);
	}
	q->vect=(uint32_t*)calloc(sizeof(uint32_t)*(e.size()/8+bool(e.size()%8)),1);
	q->size=e.size()/8+bool(e.size()%8);
	if (e.size()==0){
		q->sign=0;
	}else{
		q->sign=1;
		if (e[0]=='-'){
			q->sign=-1;
			e=string(e.begin()+1,e.end());
		}
		for (auto&w:e){
			w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[int(w)];
		}
		for (size_t w=0;w<e.size();++w){
			q->vect[w/8]|=uint32_t(uint8_t(e.end()[-1-w]))<<(w%8)*4;
		}
	}
	size_t g=q->size;
	while (g>0 and q->vect[g-1]==0){
		g-=1;
	}
	if (g==0){
		q->sign=0;
	}else{
	}
}
#endif


#define PERF 0


#ifdef CPP_R

class bn_class{
public:
	bn *q;
	bn_class(){

		q=bn_new();
#if PERF
		ic(v);
#endif
	}
	bn_class(bn*q){
		this->q=q;
	}
	bn_class(const bn_class& orig){

		q=bn_init(orig.q);
#if PERF
		ic(v);
#endif
	}
// 	bn_class(const long orig){
// 
// 		q=bn_new();
// 		bn_init_int(q,int64_t(orig));
// #if PERF
// 		ic(v);
// #endif
// 	}
	bn_class(const int orig){

		q=bn_new();
		bn_init_int(q,int64_t(orig));
#if PERF
		ic(v);
#endif
	}
	bn_class(const string&orig){

		q=bn_new();
		bn_init_str(q,orig.c_str());
#if PERF
		ic(v);
#endif
	}
	bn_class(const string&orig,int64_t r){
		q=bn_new();
		bn_init_string_radix(q,orig.c_str(),r);
#if PERF
		ic(v);
#endif
	}
	auto&operator=(int64_t orig){

		bn_init_int(q,orig);
#if PERF
		ic(v);
#endif
		return *this;
	}
	auto&operator=(const bn_class&orig){

		bn_delete(q);
		q=bn_init(orig.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	template <typename T>
	// friend auto &operator<<(T& q,bn_class f){
	// 	q<<print_one(f.q);
	// 	return q;
	// }
	bool operator<(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)<0;
#if PERF
		ic(v);
#endif
		return h;
	}
	bool operator==(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)==0;
#if PERF
		ic(v);
#endif
		return h;
	}
	bool operator>(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)>0;
#if PERF
		ic(v);
#endif
		return h;
	}
	bool operator<=(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)<=0;
#if PERF
		ic(v);
#endif
		return h;
	}
	bool operator!=(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)!=0;
#if PERF
		ic(v);
#endif
		return h;
	}
	bool operator>=(bn_class const&q){

		auto h=bn_cmp(this->q,q.q)>=0;
#if PERF
		ic(v);
#endif
		return h;
	}
	~bn_class(){
		bn_delete(q);
	}
	auto&operator+=(const bn_class&q){

		bn_add_to(this->q,q.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	auto&operator-=(const bn_class&q){

		bn_sub_to(this->q,q.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	auto&operator*=(const bn_class&q){

		bn_mul_to(this->q,q.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	auto&operator/=(const bn_class&q){

		bn_div_to(this->q,q.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	auto&operator%=(const bn_class&q){

		bn_mod_to(this->q,q.q);
#if PERF
		ic(v);
#endif
		return *this;
	}
	struct pow{
		const bn_class&q;
		pow(const bn_class&w):q(w){}
		friend bn_class operator*(const bn_class&q,const pow&w){
	
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=(uint64_t)(e->vect);
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			auto h=bn_pow(q.q,r);
	#if PERF
		ic(v);
#endif
			return h;
		}
		friend bn_class operator/(const bn_class&q,const pow&w){
	
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=(uint64_t)(e->vect);
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			auto h=bn_root(q.q,r);
	#if PERF
		ic(v);
#endif
			return h;
		}
		friend auto operator<<(const bn_class&q,const pow&w){
	
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=(uint64_t)(e->vect);
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			auto h=bn_to_string(q.q,r);
			auto g=std::string(h);
			char *u=(char*)h;
			free(u);
	#if PERF
		ic(v);
#endif
			return g;
		}
		friend auto operator^(const bn_class&q,const pow&w){
	
			// bn*e=w.q.q;
			// uint64_t r;
			// if (e->size==0){
			// 	r=0;
			// }else if (e->size==1){
			// 	r=e->vect[0];
			// }else{
			// 	r=e->vect[0]|uint64_t(e->vect[1])<<32;
			// }
			// bn**a=new bn*[stol(bn_to_string(q.q,10))*stol(bn_to_string(w.q.q,10))];
			// for (size_t w:range( stol(bn_to_string(q.q,10))*stol(bn_to_string(w.q.q,10))   )){
			// 	a[w]=bn_new();
			// }
			// for (size_t w:range( stol(bn_to_string(q.q,10))*stol(bn_to_string(w.q.q,10))   )){
			// 	bn_delete(a[w]);
			// }
			// delete[] a;
	#if PERF
		ic(v);
#endif
			return "0";
		}
	};
	pow operator*(){
		return pow(*this);
	}
	friend bn_class operator+(const bn_class&q,const bn_class&w){

		auto h=bn_add(q.q,w.q);
#if PERF
		ic(v);
#endif
		return h;
	}
	friend bn_class operator-(const bn_class&q,const bn_class&w){

		auto h=bn_sub(q.q,w.q);
#if PERF
		ic(v);
#endif
		return h;
	}
	friend bn_class operator*(const bn_class&q,const bn_class&w){

		auto h=bn_mul(q.q,w.q);
#if PERF
		ic(v);
#endif
		return h;
	}
	friend bn_class operator/(const bn_class&q,const bn_class&w){

		auto h=bn_div(q.q,w.q);
#if PERF
		ic(v);
#endif
		return h;
	}
	friend bn_class operator%(const bn_class&q,const bn_class&w){

		auto h=bn_mod(q.q,w.q);
#if PERF
		ic(v);
#endif
		return h;
	}
	std::string toString(int64_t w=10)const{

		auto h=bn_to_string(q,w);
		auto g=std::string(h);
		char *u=(char*)h;
		free(u);
#if PERF
		ic(v);
#endif
		return g;
	}
	// std::string str1(int64_t w)const{
	// 	auto h=bn_to_string_low(q,w);
	// 	auto g=std::string(h);
	// 	char *u=(char*)h;
	// 	free(u);
	// 	return g;
	// }
	operator std::string()const{

		auto h=bn_to_string(q,10);
		auto g=std::string(h);
		char *u=(char*)h;
		free(u);
#if PERF
		ic(v);
#endif
		return g;
	}
};

template <typename T>
std::string output_time(T q){
	if (q>20){
		return "\x1b[91m"+to_string(q)+"\x1b[0m";
	}
	if (q>1){
		return "\x1b[93m"+to_string(q)+"\x1b[0m";
	}
	return "\x1b[92m"+to_string(q)+"\x1b[0m";
}
#include <iostream>
using std::cout, std::endl;

// #include "biginteger.h"
// #include "/Users/gera/Downloads/e89224ba7328171c34ad1a08431b97d375dbca1a/075e97c3387e456692f480d67a27365f-e89224ba7328171c34ad1a08431b97d375dbca1a/biginteger.cpp"
// #define bn_class BigInteger
void check_output(auto&&q, auto&&w){
	cout << q.toString() << endl;
	cout << w << endl;
	assert (q.toString() == w);
}

signed main(){
	// test(bn_class("1"),"\x1b[92m+\x1b[0m00000001");
	// test(bn_class("-1"),"\x1b[92m-\x1b[0m00000001");
	// test(bn_class("1234"),"\x1b[92m+\x1b[0m00001234");
	// test(bn_class("-1234"),"\x1b[92m-\x1b[0m00001234");
	// test(bn_class("12345678"),"\x1b[92m+\x1b[0m12345678");
	// test(bn_class("-12345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	// test(bn_class("012345678"),"\x1b[92m+\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	// test(bn_class("-012345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	// test(bn_class("876543210"),"\x1b[92m+\x1b[0m00000008\x1b[92m76543210\x1b[0m");
	// test(bn_class("-876543210"),"\x1b[92m-\x1b[0m00000008\x1b[92m76543210\x1b[0m");
	// test(bn_class("fedcba9876543210"),"\x1b[92m+\x1b[0mfedcba98\x1b[92m76543210\x1b[0m");
	// test(bn_class("-fedcba9876543210"),"\x1b[92m-\x1b[0m00000000\x1b[92mfedcba98\x1b[0m76543210");
	// test(bn_class("1234567898765432123456789876543212345678987654321234567"),"\x1b[92m+\x1b[0m01234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567");
	// test(bn_class("0"),"\x1b[92m0\x1b[0m00000000");
	// test(bn_class(4294967296),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(bn_class(4294967295),"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(bn_class(-2147483648),"\x1b[92m-\x1b[0m00000000\x1b[92m80000000\x1b[0m");
	// test(bn_class(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(bn_class(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(bn_class()==bn_class(),"True");
	// test(bn_class(0)==bn_class(0),"True");
	// test(bn_class(0)==bn_class("0"),"True");
	// test(bn_class(1)==bn_class(0),"False");
	// test(bn_class(1)==bn_class(-1),"False");
	// test(bn_class(1)==bn_class("1"),"True");
	// test(bn_class(-1)==bn_class("-1"),"True");
	// test(bn_class(2)>bn_class(1),"True");
	// test(bn_class(-2)<bn_class(-1),"True");
	// test(bn_class("ffffffffffffffffffffffffffffffff")<bn_class(2),"False");
	// test(bn_class(),"\x1b[92m0\x1b[0m")
	// auto q=bn_class(1);
	// test(q+=1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(q+=-1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q-=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(q+=-1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=-1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(q-=-3,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=0,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000003\x1b[0m");
	// test(q-=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(q+=1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q+=0,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// auto h=bn_class("ffffffffffffffffffffffff");
	// test(q+=h,"\x1b[92m+\x1b[0m00000001\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	// test(q-=h,"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// test(q-=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	// test(q-=0,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	// test(q-=1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// test(q-=0,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// test(q-=h,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	// test(q+=2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0mffffffff\x1b[92mffffffff\x1b[0mfffffffe");
	// test(q+=h,"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// q=1;
	// test(q*1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(q*2,"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// q=-4;
	// test(q*-4,"\x1b[92m+\x1b[0m00000000\x1b[92m00000010\x1b[0m");
	// q=-2147483648;
	// test(q*2147483648,"\x1b[92m+\x1b[0m00000000\x1b[92m40000000\x1b[0m00000000");
	// // test(q/2147483648,"\x1b[92m+\x1b[0m00000001");
	// // test(bn_class(17)/10,"\x1b[92m+\x1b[0m00000001");
	// // test(bn_class(-17)/10,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// // test(bn_class(17)/(-10),"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// // test(bn_class(-17)/(-10),"\x1b[92m+\x1b[0m00000001");
	// // test(bn_class(0)/(-10),"\x1b[92m0\x1b[0m");
	// // test(bn_class(0)/(+10),"\x1b[92m0\x1b[0m");
	// h=bn_class("ffffffffffffffffffffffffffffffff");
	// test(h/15,"\x1b[92m+\x1b[0m11111111\x1b[92m11111111\x1b[0m11111111\x1b[92m11111111\x1b[0m")
	// test(h/bn_class("ffffffff"),"\x1b[92m+\x1b[0m00000001\x1b[92m00000001\x1b[0m00000001\x1b[92m00000001\x1b[0m")
	// test(h%bn_class("ffffffff"),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000")
	// test(q/2147483648,"\x1b[92m+\x1b[0m00000001");
	// test(bn_class(17)/10,"\x1b[92m+\x1b[0m00000001");
	// test(bn_class(-17)/10,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(bn_class(17)/(-10),"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(bn_class(-17)/(-10),"\x1b[92m+\x1b[0m00000001");
	// test(bn_class(0)/(-10),"\x1b[92m0\x1b[0m");
	// test(bn_class(0)/(+10),"\x1b[92m0\x1b[0m");
	// h=bn_class("ffffffffffffffffffffffffffffffff");
	// test(h/15,"\x1b[92m+\x1b[0m11111111\x1b[92m11111111\x1b[0m11111111\x1b[92m11111111\x1b[0m")
	// test(h/bn_class("ffffffff"),"\x1b[92m+\x1b[0m00000001\x1b[92m00000001\x1b[0m00000001\x1b[92m00000001\x1b[0m")
	// test(h%bn_class("ffffffff"),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000")
	// test(bn_class(2) ** bn_class(2),"\x1b[92m+\x1b[0m00000000\x1b[92m00000004\x1b[0m");
	// test(bn_class(2) ** bn_class(10),"\x1b[92m+\x1b[0m00000000\x1b[92m00000400\x1b[0m");
	// test(bn_class(7) ** bn_class(7),"\x1b[92m+\x1b[0m00000000\x1b[92m000c90f7\x1b[0m");
	// test(bn_class(23) ** bn_class(23),"\x1b[92m+\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	// test(bn_class(-23) ** bn_class(23),"\x1b[92m-\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	// test(bn_class(23) ** bn_class(24),"\x1b[92m+\x1b[0m00000000\x1b[92m000017ad\x1b[0m9de92445\x1b[92m8933ffd9\x1b[0m2a3d9ac1");
	// test(bn_class(-23) ** bn_class(24),"\x1b[92m+\x1b[0m00000000\x1b[92m000017ad\x1b[0m9de92445\x1b[92m8933ffd9\x1b[0m2a3d9ac1");
	// test(bn_class(16)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000002");
	// test(bn_class(15)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// test(bn_class(16)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000002");
	// test(bn_class(15)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// // test(bn_class(16)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// // test(bn_class(15)/ *bn_class(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(bn_class("123456",7),"\x1b[92m+\x1b[0m00000000\x1b[92m0000595b\x1b[0m");
	// // ic()
	// test(bn_class("zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m+\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	// // ic()
	// test(bn_class("-zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m-\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	// test(1**bn_class(1000000000),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	// test(bn_class("-0",10),"\x1b[92m0\x1b[0m00000000")
	// test(str(bn_class(1)),"1")
	// test(str(bn_class()),"0")
	// test(str(bn_class("-12345678901",10)),"-12345678901")
	// test(str(bn_class("-12345678901",11).str(11)),"-12345678901")
	// test(str(bn_class("-1234567890123456789",16).str(16)),"-1234567890123456789")
	// test(str(bn_class("-1234567890123456789",22).str(22)),"-1234567890123456789")
	// test(str(bn_class("-1234567890123456789",32).str(32)),"-1234567890123456789")
	// test(bn_class("-zyxwvutsrqponmlkjihgfedcba9876543210",36).str(36),"-ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210");
	// test(bn_class(10).str(10),"10");
	// test(bn_class(10).str(2),"1010");
	// test(bn_class(65536).str(2),"10000000000000000");
	// // // // // // // _rand
	// // // // // // // vector<int> a(40);
	// // // // // // // for (auto q:range(9)){
	// // // // // // // 	auto f=bn_class(rand());
	// // // // // // // 	f=f**bn_class(rand()%9);
	// // // // // // // 	for (auto w:range(2,37)){
	// // // // // // // 		if (f.str(w)!=f.str1(w)){
	// // // // // // // 			a[w]+=1;
	// // // // // // // 		}
	// // // // // // // 	}
	// // // // // // // }
	// // // // // // // print(a);
	// // _rand
	// // vector<int> a(40);
	// // for (auto q:range(9)){
	// // 	auto f=bn_class(rand());
	// // 	f=f**bn_class(rand()%9);
	// // 	for (auto w:range(2,37)){
	// // 		if (f.str(w)!=f.str1(w)){
	// // 			a[w]+=1;
	// // 		}
	// // 	}
	// // }
	// // print(a);
	// test(bn_class(0).str(36),"0");
	// test(str(bn_class("100000000000000000000000000000000000000000000000000000000",10)/bn_class("100000000000000000000000000000000000000000000000000000001",10)),"0")
	// test(str(bn_class("0",10)%bn_class("10",10)),"0")
	// test(bn_class("0",10)<bn_class("2",10),"True")
	// test(str(bn_class("-0",10)+bn_class("0",10)),"0")
	// // // // // // std::string _t="9675014747112608736850773242048361690409865981458363630705894373979202914072624810773537954622842049373398993797832873339776860075727147259888580079459161264328932129729221929178213767648394882406658458661139787843222912562544351554813090922783715438420126";
	// // // // // // auto l=monotonic();
	// // // // // // auto y=bn_class(_t,10);
	// // // // // // print(monotonic()-l)	
	// // // // // // l=monotonic();
	// // // // // // test(str(y),_t)
	// // // // // // print(monotonic()-l)

// #define HIDE_118
// #define HIDE_119
// #define HIDE_138
// #define HIDE_139


// #define HIDE_148
// #define HIDE_149
// #define HIDE_150
// #define HIDE_151
// #define HIDE_152
// #define HIDE_153
// #define HIDE_154
// #define HIDE_155
// #define HIDE_156
// #define HIDE_157
// #define HIDE_158
// #define HIDE_159
	// std::string _t="9675014747112608736850773242048361690409865981458363630705894373979202914072624810773537954622842049373398993797832873339776860075727147259888580079459161264328932129729221929178213767648394882406658458661139787843222912562544351554813090922783715438420126";
	// auto l=monotonic();
	// auto y=bn_class(_t,10);
	// print(monotonic()-l)	
	// l=monotonic();
	// test(str(y),_t)
	// print(monotonic()-l)


// #define HIDE_118
// #define HIDE_119
// #define HIDE_138
// #define HIDE_139


// #define HIDE_159

// #define HIDE_118
// #define HIDE_119
// #define HIDE_138
// #define HIDE_139
// #define HIDE_159


// #define HIDE_162
// auto __h=perf(1);
#include "stdout.cpp"
// ic("total:",__h);

// ic(bn_class(1)/bn_class(1))

// ic(str(bn_class("1000000000000",10)<< *bn_class("a")))
// ic(bn_class("1000000000000",10))
// ic(bn_class("2540be400")*bn_class("a"))


// ic(str(bn_class("-17",10)%bn_class("-10",10)));
// ic(str(bn_class("-17",10)%bn_class("10",10)));
// ic(str(bn_class("17",10)%bn_class("-10",10)));
// ic(str(bn_class("17",10)%bn_class("10",10)));

// ic(sizeof(bn))

// ic(bn_class("10000000000000000000000000000000000000000000000000",10)<<*bn_class("10",10))

}
#endif

#ifdef C_R
int main(){
}
#endif

