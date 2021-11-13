#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>

#if __has_include("h") && __cplusplus
#define CPP_R
#endif

#ifdef CPP_R
#include "bn.h"
#include "d"
using namespace std;
#endif


#define NORMAL_SIZE 0

#define ERRORS 0


#if ERRORS

#define minit_e(q,s,e) (q)->size=(s);(q)->vect=malloc(sizeof(uint32_t)*(s)); if (!q){return e;}
#define cinit_e(q,s,e) (q)->size=(s);(q)->vect=calloc(sizeof(uint32_t)*(s)); if (!q){return e;}
#define reinit_e(q,s,e) (q)->size=(s);(q)->vect=realloc(sizeof(uint32_t)*(s)); if (!q){return e;}

#else

#define minit(q,s) (q)->size=(s);(q)->vect=malloc(sizeof(uint32_t)*(s));
#define cinit(q,s) (q)->size=(s);(q)->vect=calloc(sizeof(uint32_t)*(s));
#define reinit(q,s) (q)->size=(s);(q)->vect=realloc(sizeof(uint32_t)*(s));
#define minit_e(q,s,e) (q)->size=(s);(q)->vect=malloc(sizeof(uint32_t)*(s));
#define cinit_e(q,s,e) (q)->size=(s);(q)->vect=calloc(sizeof(uint32_t)*(s));
#define reinit_e(q,s,e) (q)->size=(s);(q)->vect=realloc(sizeof(uint32_t)*(s));

#endif

// #define NORMALIZE(q) 

struct bn_s{
	int8_t sign;
	size_t size;
	uint32_t *vect;
};

bn *bn_new(){
	return (bn*)calloc(sizeof(bn),1);
}

bn *bn_init(bn const*orig){
#if ERRORS
	if(!orig){
		return nullptr;
	}
#endif
	bn *q=(bn*)malloc(sizeof(bn));
#if ERRORS
	if (!q){
		return nullptr;
	}
#endif
	*q=*orig;
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
#if ERRORS
	if (!q->vect){
		return nullptr;
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];
	}
	return q;
}

int bn_init_bn(bn* q,const bn*orig){
#if ERRORS
	if(!orig){
		return nullptr;
	}
	if(!q){
		return nullptr;
	}
#endif
	if (q->vect){
		free(q->vect);
	}
	*q=*orig;
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
#if ERRORS
	if (!q->vect){
		return nullptr;
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];
	}
	return BN_OK;
}

int bn_init_int(bn *q,int64_t e){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;
	}
#endif
	if (q->vect){
		free(q->vect);
	}
	q->vect=(uint32_t*)malloc(sizeof(uint32_t)*2);
#if ERRORS
	if (!q->vect){
		return BN_NO_MEMORY;
	}
#endif
	q->size=2;
	q->sign=e>0?1:e<0?-1:0;
	*(uint64_t*)(q->vect)=e>0?e:-e;
#if NORMAL_SIZE
	if (!q->vect[1]){
		q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);
		q->size=1;
		if (!q->vect[0]){
			q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);
			q->size=0;
		}
	}
#endif
	return BN_OK;
}


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
			w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[w];
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

int bn_delete(bn *q){
	if (!q){
		return BN_NULL_OBJECT;
	}
	if (q->vect){
		free(q->vect);
	}
	free(q);
	return BN_OK;
}


// int bn_init_string(bn *q,const char*e){
// 	size_t le=strlen(e)
// #if ERRORS
// 	if (!q){
// 		return BN_NULL_OBJECT;
// 	}
// #endif
// 	if (q->vect){
// 		free(q->vect);
// 	}
// 	q->vect=(uint32_t*)calloc(sizeof(uint32_t)*(le/9+1),1);
// #if ERRORS
// 	if (!q->vect){
// 		return BN_NO_MEMORY;
// 	}
// #endif
// 	q->size=le/9+1;
// 	if (le==0){
// 		q->sign=0;
// 	}else{
// 		size_t c=0;
// 		q->sign=1;
// 		if (e[0]=='-'){
// 			q->sign=-1;
// 			c=1;
// 		}
// 		for(;c<le;++c){
// 			size_t w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[e[le-1-c]];
// 			q->vect[w/8]|=uint32_t(uint8_t(w))<<(w%8)*4;
// 		}
// 		for (auto&w:e){
// 			w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[w];
// 		}
// 		for (auto w:range(strlen(e))){
// 			q->vect[w/8]|=uint32_t(uint8_t(e.end()[-1-w]))<<(w%8)*4;
// 		}
// 	}
// 	int64_t g=q->size;
// 	while (g>0 and q->vect[g-1]==0){
// 		g-=1;
// 	}
// 	if (g==0){
// 		q->sign=0;
// 		q->size=0;
// 		free(q->vect);
// 		q->vect=nullptr;
// 	}else{
// #if NORMAL_SIZE
// 		q->size=g;
// 		q->vect=(uint32_t*)realloc(q->vect,(g)*sizeof(uint32_t));
// #if ERRORS
// 		if (!q->vect){
// 			return BN_NO_MEMORY;
// 		}
// #endif
// #endif
// 	}
// 	return BN_OK;
// }


static int bn_M_add_to(bn *q, bn const *e){
	if (!q){
		return BN_NULL_OBJECT;
	}
	if (!e){
		return BN_NULL_OBJECT;
	}
	q->size=(q->size>e->size?q->size:e->size)+1;
	q->vect=(uint32_t*)realloc(q->vect,q->size*sizeof(uint32_t));
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;
	}
#endif
	uint64_t buff=0;
	for (size_t w=0;w<q->size;++q){
		if (w<q->size){
			buff+=q->vect[w];
		}
		if (w<e->size){
			buff+=e->vect[w];
		}
		q->vect[w]=buff&0b11111111111111111111111111111111;
		buff>>=32;
	}
	return BN_OK;
}

static int bn_M_sub_to(bn *q, bn const *e){
	if (!q){
		return BN_NULL_OBJECT;
	}
	if (!e){
		return BN_NULL_OBJECT;
	}
	q->size=(q->size>e->size?q->size:e->size)+1;
	q->vect=(uint32_t*)realloc(q->vect,q->size*sizeof(uint32_t));
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;
	}
#endif
	int64_t buff=0;
	for (size_t w=0;w<q->size;++q){
		if (w<q->size){
			buff+=q->vect[w];
		}
		if (w<e->size){
			buff-=e->vect[w];
		}
		q->vect[w]=buff&0b11111111111111111111111111111111;
		buff>>=32;
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

int bn_cmp(bn const *q, bn const *e){
	if (q->sign!=e->sign){
		return q->sign-e->sign;
	}
	for (ssize_t c=(q->size>e->size?q->size:e->size)-1;c>=0;--c){
		auto a=q->size>c?q->vect[c]:0;
		auto s=e->size>c?e->vect[c]:0;
		if (a!=s){
			return (a-s)*q->sign;
		}
	}
	return 0;
}

int bn_add_to(bn*q,const bn*e){
#if ERRORS
#error
#endif
	auto h=bn_new();
	auto j=bn_cmp(q,h);
	auto k=bn_cmp(e,h);
	auto l=bn_cmp(q,e);
	if (j<0){
		if (k<0){
			bn_M_add_to(q,e);
		}else if(k==0){
			/*pass*/
		}else{
			if (l<0){
				bn_M_sub_to(q,e);
			}else if (l==0){
				bn_init_int(q,0);
			}else{
				
			}
		}
	}else if(j==0){
		if (k<0){

		}else if(k==0){
			/*pass*/
		}else{

		}
	}else{
		if (k<0){
			
		}else if(k==0){
			/*pass*/
		}else{
			bn_M_add_to(q,e);
		}
	}
	return BN_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CPP_R

class BigInteger{
public:
	bn *q;
	BigInteger(){
		q=bn_new();
	}
	BigInteger(const BigInteger& orig){
		q=bn_init(orig.q);
	}
	BigInteger(const int64_t orig){
		q=bn_new();
		bn_init_int(q,orig);
	}
	BigInteger(const string orig){
		q=bn_new();
		bn_init_str(q,orig.c_str());
	}
	BigInteger(const string orig,istream&f){
		q=bn_new();
		bn_init_string(q,orig.c_str());
	}
	BigInteger(const string orig,int64_t r){
		q=bn_new();
		bn_init_string_radix(q,orig.c_str(),r);
	}
	int operator=(int64_t orig){
		return bn_init_int(q,orig);
	}
	template <typename T>
	friend auto &operator<<(T& q,BigInteger f){
		char b[99999];
		b[0]=0;
		sprintf(b,"%s\x1b[92m%c\x1b[0m",b,1==f.q->sign?'+':-1==f.q->sign?'-':'0');
		int c=0;
		for (int t=f.q->size-1;t>-1;--t){
			if (c%2){
				sprintf(b,"%s\x1b[92m",b);
			}
			sprintf(b,"%s%0*x",b,8,f.q->vect[t]);
			if (c%2){
				sprintf(b,"%s\x1b[0m",b);
			}
			++c;
		}
		q<<b;
		return q;
	}
	// BigInteger&operator+=(BigInteger const&q){
	// 	this->q+=q.q;
	// 	return *this;
	// }
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
};


µ{
	test(BigInteger("1"),"\x1b[92m+\x1b[0m00000001");
	test(BigInteger("-1"),"\x1b[92m-\x1b[0m00000001");
	test(BigInteger("1234"),"\x1b[92m+\x1b[0m00001234");
<<<<<<< HEAD
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
	test(BigInteger(4294967296),"\x1b[92m+\x1b[0m00000001\x1b[92m00000000\x1b[0m");
	test(BigInteger(4294967295),"\x1b[92m+\x1b[0m00000000\x1b[92mffffffff\x1b[0m");
	test(BigInteger(-2147483648),"\x1b[92m-\x1b[0m00000000\x1b[92m80000000\x1b[0m");
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");
	test(BigInteger(0)==BigInteger(0),"True");
	test(BigInteger(0)==BigInteger("0"),"True");
	test(BigInteger(1)==BigInteger(0),"False");
	test(BigInteger(1)==BigInteger(-1),"False");
	test(BigInteger(1)==BigInteger("1"),"True");
	test(BigInteger(-1)==BigInteger("-1"),"True");
	test(BigInteger(2)>BigInteger(1),"True");
	test(BigInteger(-2)<BigInteger(-1),"True");
	test(BigInteger(),"\x1b[92m0\x1b[0m")
=======
	test(BigInteger("-1234"));
	test(BigInteger("12345678"));
	test(BigInteger("-12345678"));
	test(BigInteger("012345678"));
	test(BigInteger("-012345678"));
	test(BigInteger("876543210"));
	test(BigInteger("-876543210"));
	test(BigInteger("fedcba9876543210"));
	test(BigInteger("-fedcba9876543210"));
	test(BigInteger("1234567898765432123456789876543212345678987654321234567"));
	test(BigInteger("0"));
	test(BigInteger(4294967296));
	test(BigInteger(4294967295));
	test(BigInteger(-2147483648));
	test(BigInteger(0));
	test(BigInteger(0));
	test(BigInteger(0)==BigInteger(0));
	test(BigInteger(0)==BigInteger("0"));
	test(BigInteger(1)==BigInteger(0));
	test(BigInteger(1)==BigInteger(-1));
	test(BigInteger(1)==BigInteger("1"));
	test(BigInteger(-1)==BigInteger("-1"));
>>>>>>> 8d5eb8b300b9b6a2b30f95c6262590dd5a0deb25
}

#endif