#ifndef C_R
#define CPP_R
#endif


#define NORMAL_SIZE 0

#define ERRORS 0


#define COLORS 1


#ifdef CPP_R
#include "bn.h"
#include "d"
#endif

#ifdef C_R
#include "bn.h"
#include "d"
#endif




#ifdef CPP_R
#include "bn.c"
#endif

#ifdef C_R
#include "bn.c"
#endif



#ifdef CPP_R
int bn_init_str(bn *q,string e){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;
	}
#endif
	if (q->vect){
		free(q->vect);
	}
	q->vect=(uint32_t*)calloc(sizeof(uint32_t)*(e.size()/8+bool(e.size()%8)),1);
#if ERRORS
	if (!q->vect){
		return BN_NO_MEMORY;
	}
#endif
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
		for (auto w:range(e.size())){
			q->vect[w/8]|=uint32_t(uint8_t(e.end()[-1-w]))<<(w%8)*4;
		}
	}
	size_t g=q->size;
	while (g>0 and q->vect[g-1]==0){
		g-=1;
	}
	if (g==0){
		q->sign=0;
#if NORMAL_SIZE
		q->size=0;
		free(q->vect);
		q->vect=nullptr;
#endif
	}else{
#if NORMAL_SIZE
		q->size=g;
		q->vect=(uint32_t*)realloc(q->vect,(g)*sizeof(uint32_t));
#if ERRORS
		if (!q->vect){
			return BN_NO_MEMORY;
		}
#endif
#endif
	}
	return BN_OK;
}
#endif



#ifdef CPP_R

class BigInteger{
public:
	bn *q;
	BigInteger(){
		q=bn_new();
	}
	BigInteger(bn*q){
		this->q=q;
	}
	BigInteger(const BigInteger& orig){
		q=bn_init(orig.q);
	}
	BigInteger(const long orig){
		q=bn_new();
		bn_init_int(q,int64_t(orig));
	}
	BigInteger(const int orig){
		q=bn_new();
		bn_init_int(q,int64_t(orig));
	}
	BigInteger(const string orig){
		q=bn_new();
		bn_init_str(q,orig.c_str());
	}
	BigInteger(const string orig,int64_t r){
		q=bn_new();
		bn_init_string_radix(q,orig.c_str(),r);
	}
	auto&operator=(int64_t orig){
		bn_init_int(q,orig);
		return *this;
	}
	auto&operator=(const BigInteger&orig){
		bn_delete(q);
		q=bn_init(orig.q);
		return *this;
	}
	template <typename T>
	friend auto &operator<<(T& q,BigInteger f){
		q<<print_one(f.q);
		return q;
	}
	bool operator<(BigInteger const&q){
		return bn_cmp(this->q,q.q)<0;
	}
	bool operator==(BigInteger const&q){
		return bn_cmp(this->q,q.q)==0;
	}
	bool operator>(BigInteger const&q){
		return bn_cmp(this->q,q.q)>0;
	}
	bool operator<=(BigInteger const&q){
		return bn_cmp(this->q,q.q)<=0;
	}
	bool operator!=(BigInteger const&q){
		return bn_cmp(this->q,q.q)!=0;
	}
	bool operator>=(BigInteger const&q){
		return eic(bn_cmp(this->q,q.q))>=0;
	}
	~BigInteger(){
		bn_delete(q);
	}
	auto&operator+=(const BigInteger&q){
		bn_add_to(this->q,q.q);
		return *this;
	}
	auto&operator-=(const BigInteger&q){
		bn_sub_to(this->q,q.q);
		return *this;
	}
	auto&operator*=(const BigInteger&q){
		bn_mul_to(this->q,q.q);
		return *this;
	}
	auto&operator/=(const BigInteger&q){
		bn_div_to(this->q,q.q);
		return *this;
	}
	auto&operator%=(const BigInteger&q){
		bn_mod_to(this->q,q.q);
		return *this;
	}
	struct pow{
		const BigInteger&q;
		pow(const BigInteger&w):q(w){}
		friend BigInteger operator*(const BigInteger&q,const pow&w){
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=0;
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			return bn_pow(q.q,r);
		}
		friend BigInteger operator/(const BigInteger&q,const pow&w){
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=0;
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			return bn_root(q.q,r);
		}
		friend auto operator<<(const BigInteger&q,const pow&w){
			bn*e=w.q.q;
			uint64_t r;
			if (e->size==0){
				r=0;
			}else if (e->size==1){
				r=e->vect[0];
			}else{
				r=e->vect[0]|uint64_t(e->vect[1])<<32;
			}
			auto h=bn_to_string(q.q,r);
			auto g=std::string(h);
			char *u=(char*)h;
			free(u);
			return g;
		}
	};
	pow operator*(){
		return pow(*this);
	}
	friend BigInteger operator+(const BigInteger&q,const BigInteger&w){
		return bn_add(q.q,w.q);
	}
	friend BigInteger operator-(const BigInteger&q,const BigInteger&w){
		return bn_sub(q.q,w.q);
	}
	friend BigInteger operator*(const BigInteger&q,const BigInteger&w){
		return bn_mul(q.q,w.q);
	}
	friend BigInteger operator/(const BigInteger&q,const BigInteger&w){
		return bn_div(q.q,w.q);
	}
	friend BigInteger operator%(const BigInteger&q,const BigInteger&w){
		return bn_mod(q.q,w.q);
	}
	std::string str(int64_t w)const{
		auto h=bn_to_string(q,w);
		auto g=std::string(h);
		char *u=(char*)h;
		free(u);
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
		return g;
	}
};

template <typename T>
std::string output_time(T q){
	if (q>20){
		return "\x1b[91m"+to_string(q)+"\x1b[0m";
	}
	if (q>2){
		return "\x1b[93m"+to_string(q)+"\x1b[0m";
	}
	return "\x1b[92m"+to_string(q)+"\x1b[0m";
}


signed main(){
	test(BigInteger("1"),"\x1b[92m+\x1b[0m00000001");
	test(BigInteger("-1"),"\x1b[92m-\x1b[0m00000001");
	test(BigInteger("1234"),"\x1b[92m+\x1b[0m00001234");
	test(BigInteger("-1234"),"\x1b[92m-\x1b[0m00001234");
	test(BigInteger("12345678"),"\x1b[92m+\x1b[0m12345678");
	test(BigInteger("-12345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	test(BigInteger("012345678"),"\x1b[92m+\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	test(BigInteger("-012345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");
	test(BigInteger("876543210"),"\x1b[92m+\x1b[0m00000008\x1b[92m76543210\x1b[0m");
	test(BigInteger("-876543210"),"\x1b[92m-\x1b[0m00000008\x1b[92m76543210\x1b[0m");
	test(BigInteger("fedcba9876543210"),"\x1b[92m+\x1b[0mfedcba98\x1b[92m76543210\x1b[0m");
	test(BigInteger("-fedcba9876543210"),"\x1b[92m-\x1b[0m00000000\x1b[92mfedcba98\x1b[0m76543210");
	test(BigInteger("1234567898765432123456789876543212345678987654321234567"),"\x1b[92m+\x1b[0m01234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567");
	test(BigInteger("0"),"\x1b[92m0\x1b[0m00000000");
	test(BigInteger(4294967296),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(BigInteger(4294967295),"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger(-2147483648),"\x1b[92m-\x1b[0m00000000\x1b[92m80000000\x1b[0m");
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(BigInteger()==BigInteger(),"True");
	test(BigInteger(0)==BigInteger(0),"True");
	test(BigInteger(0)==BigInteger("0"),"True");
	test(BigInteger(1)==BigInteger(0),"False");
	test(BigInteger(1)==BigInteger(-1),"False");
	test(BigInteger(1)==BigInteger("1"),"True");
	test(BigInteger(-1)==BigInteger("-1"),"True");
	test(BigInteger(2)>BigInteger(1),"True");
	test(BigInteger(-2)<BigInteger(-1),"True");
	test(BigInteger("ffffffffffffffffffffffffffffffff")<BigInteger(2),"False");
	test(BigInteger(),"\x1b[92m0\x1b[0m")
	auto q=BigInteger(1);
	test(q+=1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(q+=-1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q-=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(q+=-1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=-1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(q-=-3,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=0,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000003\x1b[0m");
	test(q-=-2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(q+=1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q+=0,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	auto h=BigInteger("ffffffffffffffffffffffff");
	test(q+=h,"\x1b[92m+\x1b[0m00000001\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(q-=h,"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	test(q-=1,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	test(q-=0,"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	test(q-=1,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	test(q-=0,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	test(q-=h,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000");
	test(q+=2,"\x1b[92m-\x1b[0m00000000\x1b[92m00000000\x1b[0mffffffff\x1b[92mffffffff\x1b[0mfffffffe");
	test(q+=h,"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	q=1;
	test(q*1,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(q*2,"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	q=-4;
	test(q*-4,"\x1b[92m+\x1b[0m00000000\x1b[92m00000010\x1b[0m");
	q=-2147483648;
	test(q*2147483648,"\x1b[92m+\x1b[0m00000000\x1b[92m40000000\x1b[0m00000000");
	// test(q/2147483648,"\x1b[92m+\x1b[0m00000001");
	// test(BigInteger(17)/10,"\x1b[92m+\x1b[0m00000001");
	// test(BigInteger(-17)/10,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(BigInteger(17)/(-10),"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(BigInteger(-17)/(-10),"\x1b[92m+\x1b[0m00000001");
	// test(BigInteger(0)/(-10),"\x1b[92m0\x1b[0m");
	// test(BigInteger(0)/(+10),"\x1b[92m0\x1b[0m");
	h=BigInteger("ffffffffffffffffffffffffffffffff");
	test(h/15,"\x1b[92m+\x1b[0m11111111\x1b[92m11111111\x1b[0m11111111\x1b[92m11111111\x1b[0m")
	test(h/BigInteger("ffffffff"),"\x1b[92m+\x1b[0m00000001\x1b[92m00000001\x1b[0m00000001\x1b[92m00000001\x1b[0m")
	test(h%BigInteger("ffffffff"),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000")
	test(q/2147483648,"\x1b[92m+\x1b[0m00000001");
	test(BigInteger(17)/10,"\x1b[92m+\x1b[0m00000001");
	test(BigInteger(-17)/10,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(BigInteger(17)/(-10),"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(BigInteger(-17)/(-10),"\x1b[92m+\x1b[0m00000001");
	test(BigInteger(0)/(-10),"\x1b[92m0\x1b[0m");
	test(BigInteger(0)/(+10),"\x1b[92m0\x1b[0m");
	h=BigInteger("ffffffffffffffffffffffffffffffff");
	test(h/15,"\x1b[92m+\x1b[0m11111111\x1b[92m11111111\x1b[0m11111111\x1b[92m11111111\x1b[0m")
	test(h/BigInteger("ffffffff"),"\x1b[92m+\x1b[0m00000001\x1b[92m00000001\x1b[0m00000001\x1b[92m00000001\x1b[0m")
	test(h%BigInteger("ffffffff"),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000")
	test(BigInteger(2) ** BigInteger(2),"\x1b[92m+\x1b[0m00000000\x1b[92m00000004\x1b[0m");
	test(BigInteger(2) ** BigInteger(10),"\x1b[92m+\x1b[0m00000000\x1b[92m00000400\x1b[0m");
	test(BigInteger(7) ** BigInteger(7),"\x1b[92m+\x1b[0m00000000\x1b[92m000c90f7\x1b[0m");
	test(BigInteger(23) ** BigInteger(23),"\x1b[92m+\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	test(BigInteger(-23) ** BigInteger(23),"\x1b[92m-\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	test(BigInteger(23) ** BigInteger(24),"\x1b[92m+\x1b[0m00000000\x1b[92m000017ad\x1b[0m9de92445\x1b[92m8933ffd9\x1b[0m2a3d9ac1");
	test(BigInteger(-23) ** BigInteger(24),"\x1b[92m+\x1b[0m00000000\x1b[92m000017ad\x1b[0m9de92445\x1b[92m8933ffd9\x1b[0m2a3d9ac1");
	test(BigInteger(16)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000002");
	test(BigInteger(15)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	test(BigInteger(16)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000002");
	test(BigInteger(15)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000000\x1b[0m00000001");
	// test(BigInteger(16)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	// test(BigInteger(15)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger("123456",7),"\x1b[92m+\x1b[0m00000000\x1b[92m0000595b\x1b[0m");
	// ic()
	test(BigInteger("zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m+\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	// ic()
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m-\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	test(1**BigInteger(1000000000),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger("-0",10),"\x1b[92m0\x1b[0m00000000")
	test(str(BigInteger(1)),"1")
	test(str(BigInteger()),"0")
	test(str(BigInteger("-12345678901",10)),"-12345678901")
	test(str(BigInteger("-12345678901",11).str(11)),"-12345678901")
	test(str(BigInteger("-1234567890123456789",16).str(16)),"-1234567890123456789")
	test(str(BigInteger("-1234567890123456789",22).str(22)),"-1234567890123456789")
	test(str(BigInteger("-1234567890123456789",32).str(32)),"-1234567890123456789")
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36).str(36),"-ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210");
	test(BigInteger(10).str(10),"10");
	test(BigInteger(10).str(2),"1010");
	test(BigInteger(65536).str(2),"10000000000000000");
	// // // // // // // _rand
	// // // // // // // vector<int> a(40);
	// // // // // // // for (auto q:range(9)){
	// // // // // // // 	auto f=BigInteger(rand());
	// // // // // // // 	f=f**BigInteger(rand()%9);
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
	// // 	auto f=BigInteger(rand());
	// // 	f=f**BigInteger(rand()%9);
	// // 	for (auto w:range(2,37)){
	// // 		if (f.str(w)!=f.str1(w)){
	// // 			a[w]+=1;
	// // 		}
	// // 	}
	// // }
	// // print(a);
	// test(BigInteger(0).str(36),"0");
	// test(str(BigInteger("100000000000000000000000000000000000000000000000000000000",10)/BigInteger("100000000000000000000000000000000000000000000000000000001",10)),"0")
	// test(str(BigInteger("0",10)%BigInteger("10",10)),"0")
	// test(BigInteger("0",10)<BigInteger("2",10),"True")
	// test(str(BigInteger("-0",10)+BigInteger("0",10)),"0")
	// // // // // // std::string _t="9675014747112608736850773242048361690409865981458363630705894373979202914072624810773537954622842049373398993797832873339776860075727147259888580079459161264328932129729221929178213767648394882406658458661139787843222912562544351554813090922783715438420126";
	// // // // // // auto l=monotonic();
	// // // // // // auto y=BigInteger(_t,10);
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
	// auto y=BigInteger(_t,10);
	// print(monotonic()-l)	
	// l=monotonic();
	// test(str(y),_t)
	// print(monotonic()-l)


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
// #define HIDE_162
#include "stdout.cpp"
}
#endif

#ifdef C_R
int main(){
}
#endif