#include<stdio.h>
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
#endif


#define NORMAL_SIZE 0

#define ERRORS 0


// #if ERRORS

// #define minit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=malloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__); if (!q){return e;printf("\x02\x03%i\x01",__LINE__);}
// #define cinit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=calloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__); if (!q){return e;printf("\x02\x03%i\x01",__LINE__);}
// #define reinit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=realloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__); if (!q){return e;printf("\x02\x03%i\x01",__LINE__);}

// #else

// #define minit(q,s) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=malloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);
// #define cinit(q,s) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=calloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);
// #define reinit(q,s) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=realloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);
// #define minit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=malloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);
// #define cinit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=calloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);
// #define reinit_e(q,s,e) (q)->size=(s);printf("\x02\x03%i\x01",__LINE__);(q)->vect=realloc(sizeof(uint32_t)*(s));printf("\x02\x03%i\x01",__LINE__);

// #endif

// #define NORMALIZE(q) 

//(
struct bn_s{
	int8_t sign;
	size_t size;
	uint32_t *vect;
};
//)

bn *bn_new(){
	return (bn*)calloc(sizeof(bn),1);printf("\x02\x03%i\x01",__LINE__);
}

bn *bn_init(bn const*orig){
#if ERRORS
	if(!orig){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	bn *q=(bn*)malloc(sizeof(bn));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if (!q){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	*q=*orig;printf("\x02\x03%i\x01",__LINE__);
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if (!q->vect){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];printf("\x02\x03%i\x01",__LINE__);
	}
	return q;printf("\x02\x03%i\x01",__LINE__);
}

int bn_init_bn(bn* q,const bn*orig){
#if ERRORS
	if(!orig){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
	if(!q){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	if (q->vect){
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
	}
	*q=*orig;printf("\x02\x03%i\x01",__LINE__);
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if (!q->vect){
		return nullptr;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];printf("\x02\x03%i\x01",__LINE__);
	}
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}

int bn_init_int(bn *q,int64_t e){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	if (q->vect){
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
	}
	q->vect=(uint32_t*)malloc(sizeof(uint32_t)*2);printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if (!q->vect){
		return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	q->size=2;printf("\x02\x03%i\x01",__LINE__);
	q->sign=e>0?1:e<0?-1:0;printf("\x02\x03%i\x01",__LINE__);
	*(uint64_t*)(q->vect)=e>0?e:-e;printf("\x02\x03%i\x01",__LINE__);
#if NORMAL_SIZE
	if (!q->vect[1]){
		q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);printf("\x02\x03%i\x01",__LINE__);
		q->size=1;printf("\x02\x03%i\x01",__LINE__);
		if (!q->vect[0]){
			q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);printf("\x02\x03%i\x01",__LINE__);
			q->size=0;printf("\x02\x03%i\x01",__LINE__);
		}
	}
#endif
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}


#ifdef CPP_R
int bn_init_str(bn *q,string e){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	if (q->vect){
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
	}
	q->vect=(uint32_t*)calloc(sizeof(uint32_t)*(e.size()/8+bool(e.size()%8)),1);printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if (!q->vect){
		return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	q->size=e.size()/8+bool(e.size()%8);printf("\x02\x03%i\x01",__LINE__);
	if (e.size()==0){
		q->sign=0;printf("\x02\x03%i\x01",__LINE__);
	}else{
		q->sign=1;printf("\x02\x03%i\x01",__LINE__);
		if (e[0]=='-'){
			q->sign=-1;printf("\x02\x03%i\x01",__LINE__);
			e=string(e.begin()+1,e.end());printf("\x02\x03%i\x01",__LINE__);
		}
		for (auto&w:e){
			w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[w];printf("\x02\x03%i\x01",__LINE__);
		}
		for (auto w:range(e.size())){
			q->vect[w/8]|=uint32_t(uint8_t(e.end()[-1-w]))<<(w%8)*4;printf("\x02\x03%i\x01",__LINE__);
		}
	}
	size_t g=q->size;printf("\x02\x03%i\x01",__LINE__);
	while (g>0 and q->vect[g-1]==0){
		g-=1;printf("\x02\x03%i\x01",__LINE__);
	}
	if (g==0){
		q->sign=0;printf("\x02\x03%i\x01",__LINE__);
#if NORMAL_SIZE
		q->size=0;printf("\x02\x03%i\x01",__LINE__);
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
		q->vect=nullptr;printf("\x02\x03%i\x01",__LINE__);
#endif
	}else{
#if NORMAL_SIZE
		q->size=g;printf("\x02\x03%i\x01",__LINE__);
		q->vect=(uint32_t*)realloc(q->vect,(g)*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
		if (!q->vect){
			return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
		}
#endif
#endif
	}
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}
#endif

int bn_delete(bn *q){
	if (!q){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
	if (q->vect){
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
	}
	free(q);printf("\x02\x03%i\x01",__LINE__);
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}


// int bn_init_string(bn *q,const char*e){
// 	size_t le=strlen(e)
// #if ERRORS
// 	if (!q){
// 		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
// 	}
// #endif
// 	if (q->vect){
// 		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
// 	}
// 	q->vect=(uint32_t*)calloc(sizeof(uint32_t)*(le/9+1),1);printf("\x02\x03%i\x01",__LINE__);
// #if ERRORS
// 	if (!q->vect){
// 		return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
// 	}
// #endif
// 	q->size=le/9+1;printf("\x02\x03%i\x01",__LINE__);
// 	if (le==0){
// 		q->sign=0;printf("\x02\x03%i\x01",__LINE__);
// 	}else{
// 		size_t c=0;printf("\x02\x03%i\x01",__LINE__);
// 		q->sign=1;printf("\x02\x03%i\x01",__LINE__);
// 		if (e[0]=='-'){
// 			q->sign=-1;printf("\x02\x03%i\x01",__LINE__);
// 			c=1;printf("\x02\x03%i\x01",__LINE__);
// 		}
// 		for(;c<le;++c){
// 			size_t w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[e[le-1-c]];printf("\x02\x03%i\x01",__LINE__);
// 			q->vect[w/8]|=uint32_t(uint8_t(w))<<(w%8)*4;printf("\x02\x03%i\x01",__LINE__);
// 		}
// 		for (auto&w:e){
// 			w="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[w];printf("\x02\x03%i\x01",__LINE__);
// 		}
// 		for (auto w:range(strlen(e))){
// 			q->vect[w/8]|=uint32_t(uint8_t(e.end()[-1-w]))<<(w%8)*4;printf("\x02\x03%i\x01",__LINE__);
// 		}
// 	}
// 	int64_t g=q->size;printf("\x02\x03%i\x01",__LINE__);
// 	while (g>0 and q->vect[g-1]==0){
// 		g-=1;printf("\x02\x03%i\x01",__LINE__);
// 	}
// 	if (g==0){
// 		q->sign=0;printf("\x02\x03%i\x01",__LINE__);
// 		q->size=0;printf("\x02\x03%i\x01",__LINE__);
// 		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
// 		q->vect=nullptr;printf("\x02\x03%i\x01",__LINE__);
// 	}else{
// #if NORMAL_SIZE
// 		q->size=g;printf("\x02\x03%i\x01",__LINE__);
// 		q->vect=(uint32_t*)realloc(q->vect,(g)*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
// #if ERRORS
// 		if (!q->vect){
// 			return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
// 		}
// #endif
// #endif
// 	}
// 	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
// }


int bn_cmp(bn const *q, bn const *e){
	if (q->sign!=e->sign){
		return q->sign-e->sign;printf("\x02\x03%i\x01",__LINE__);
	}
	for (ssize_t c=(q->size>e->size?q->size:e->size)-1;c>=0;--c){
		auto a=q->size>c?q->vect[c]:0;printf("\x02\x03%i\x01",__LINE__);
		auto s=e->size>c?e->vect[c]:0;printf("\x02\x03%i\x01",__LINE__);
		if (a!=s){
			return (a-s)*q->sign;printf("\x02\x03%i\x01",__LINE__);
		}
	}
	return 0;printf("\x02\x03%i\x01",__LINE__);
}

static int bn_M_add_to(bn *q, bn const *e){
	if (!q){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
	if (!e){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
	q->size=(q->size>e->size?q->size:e->size)+1;printf("\x02\x03%i\x01",__LINE__);
	q->vect=(uint32_t*)realloc(q->vect,q->size*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	uint64_t buff=0;printf("\x02\x03%i\x01",__LINE__);
	for (size_t w=0;w<q->size;++q){
		if (w<q->size){
			buff+=q->vect[w];printf("\x02\x03%i\x01",__LINE__);
		}
		if (w<e->size){
			buff+=e->vect[w];printf("\x02\x03%i\x01",__LINE__);
		}
		q->vect[w]=buff&0b11111111111111111111111111111111;printf("\x02\x03%i\x01",__LINE__);
		buff>>=32;printf("\x02\x03%i\x01",__LINE__);
	}
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}

static int bn_M_sub_to(bn *q, bn const *e){
	if (!q){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
	if (!e){
		return BN_NULL_OBJECT;printf("\x02\x03%i\x01",__LINE__);
	}
	q->size=(q->size>e->size?q->size:e->size)+1;printf("\x02\x03%i\x01",__LINE__);
	q->vect=(uint32_t*)realloc(q->vect,q->size*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
	}
#endif
	int64_t buff=0;printf("\x02\x03%i\x01",__LINE__);
	for (size_t w=0;w<q->size;++q){
		if (w<q->size){
			buff+=q->vect[w];printf("\x02\x03%i\x01",__LINE__);
		}
		if (w<e->size){
			buff-=e->vect[w];printf("\x02\x03%i\x01",__LINE__);
		}
		q->vect[w]=buff&0b11111111111111111111111111111111;printf("\x02\x03%i\x01",__LINE__);
		buff>>=32;printf("\x02\x03%i\x01",__LINE__);
	}
	size_t g=q->size;printf("\x02\x03%i\x01",__LINE__);
	while (g>0 and q->vect[g-1]==0){
		g-=1;printf("\x02\x03%i\x01",__LINE__);
	}
	if (g==0){
		q->sign=0;printf("\x02\x03%i\x01",__LINE__);
#if NORMAL_SIZE
		q->size=0;printf("\x02\x03%i\x01",__LINE__);
		free(q->vect);printf("\x02\x03%i\x01",__LINE__);
		q->vect=nullptr;printf("\x02\x03%i\x01",__LINE__);
#endif
	}else{
#if NORMAL_SIZE
		q->size=g;printf("\x02\x03%i\x01",__LINE__);
		q->vect=(uint32_t*)realloc(q->vect,(g)*sizeof(uint32_t));printf("\x02\x03%i\x01",__LINE__);
#if ERRORS
		if (!q->vect){
			return BN_NO_MEMORY;printf("\x02\x03%i\x01",__LINE__);
		}
#endif
#endif
	}	
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}

int bn_add_to(bn*q,const bn*e){
#if ERRORS
#error
#endif
	bn* h=bn_new();printf("\x02\x03%i\x01",__LINE__);
	int j=bn_cmp(q,h);printf("\x02\x03%i\x01",__LINE__);
	int k=bn_cmp(e,h);printf("\x02\x03%i\x01",__LINE__);
	int l=bn_cmp(q,e);printf("\x02\x03%i\x01",__LINE__);
	if (!k){
		return BN_OK;printf("\x02\x03%i\x01",__LINE__);
	}
	if (j<=0){
		if (k<0){
			bn_M_add_to(q,e);printf("\x02\x03%i\x01",__LINE__);
		}else{
			if (l<=0){
				bn_M_sub_to(q,e);printf("\x02\x03%i\x01",__LINE__);
			}else{
				bn*h=bn_init(q);printf("\x02\x03%i\x01",__LINE__);
				bn_init_bn(q,e);printf("\x02\x03%i\x01",__LINE__);
				bn_M_sub_to(q,h);printf("\x02\x03%i\x01",__LINE__);
				q->sign*=-1;printf("\x02\x03%i\x01",__LINE__);
			}
		}
	}else{
		if (k<0){
				bn*h=bn_init(q);printf("\x02\x03%i\x01",__LINE__);
				bn_init_bn(q,e);printf("\x02\x03%i\x01",__LINE__);
				bn_M_sub_to(q,h);printf("\x02\x03%i\x01",__LINE__);
				q->sign*=-1;printf("\x02\x03%i\x01",__LINE__);
		}else{
			bn_M_add_to(q,e);printf("\x02\x03%i\x01",__LINE__);
		}
	}
	return BN_OK;printf("\x02\x03%i\x01",__LINE__);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CPP_R

class BigInteger{
public:
	//(
	bn *q;
	//)
	BigInteger(){
		q=bn_new();printf("\x02\x03%i\x01",__LINE__);
	}
	BigInteger(const BigInteger& orig){
		q=bn_init(orig.q);printf("\x02\x03%i\x01",__LINE__);
	}
	BigInteger(const int64_t orig){
		q=bn_new();printf("\x02\x03%i\x01",__LINE__);
		bn_init_int(q,orig);printf("\x02\x03%i\x01",__LINE__);
	}
	BigInteger(const string orig){
		q=bn_new();printf("\x02\x03%i\x01",__LINE__);
		bn_init_str(q,orig.c_str());printf("\x02\x03%i\x01",__LINE__);
	}
	BigInteger(const string orig,istream&f){
		q=bn_new();printf("\x02\x03%i\x01",__LINE__);
		bn_init_string(q,orig.c_str());printf("\x02\x03%i\x01",__LINE__);
	}
	BigInteger(const string orig,int64_t r){
		q=bn_new();printf("\x02\x03%i\x01",__LINE__);
		bn_init_string_radix(q,orig.c_str(),r);printf("\x02\x03%i\x01",__LINE__);
	}
	int operator=(int64_t orig){
		return bn_init_int(q,orig);printf("\x02\x03%i\x01",__LINE__);
	}
	template <typename T>
	friend auto &operator<<(T& q,BigInteger f){
		char b[99999];printf("\x02\x03%i\x01",__LINE__);
		b[0]=0;printf("\x02\x03%i\x01",__LINE__);
		sprintf(b,"%s\x1b[92m%c\x1b[0m",b,1==f.q->sign?'+':-1==f.q->sign?'-':'0');printf("\x02\x03%i\x01",__LINE__);
		int c=0;printf("\x02\x03%i\x01",__LINE__);
		for (int t=f.q->size-1;t>-1;--t){
			if (c%2){
				sprintf(b,"%s\x1b[92m",b);printf("\x02\x03%i\x01",__LINE__);
			}
			sprintf(b,"%s%0*x",b,8,f.q->vect[t]);printf("\x02\x03%i\x01",__LINE__);
			if (c%2){
				sprintf(b,"%s\x1b[0m",b);printf("\x02\x03%i\x01",__LINE__);
			}
			++c;printf("\x02\x03%i\x01",__LINE__);
		}
		q<<b;printf("\x02\x03%i\x01",__LINE__);
		return q;printf("\x02\x03%i\x01",__LINE__);
	}
	// BigInteger&operator+=(BigInteger const&q){
	// 	this->q+=q.q;printf("\x02\x03%i\x01",__LINE__);
	// 	return *this;printf("\x02\x03%i\x01",__LINE__);
	// }
	bool operator<(BigInteger const&q){
		return bn_cmp(this->q,q.q)<0;printf("\x02\x03%i\x01",__LINE__);
	}
	bool operator==(BigInteger const&q){
		return bn_cmp(this->q,q.q)==0;printf("\x02\x03%i\x01",__LINE__);
	}
	bool operator>(BigInteger const&q){
		return bn_cmp(this->q,q.q)>0;printf("\x02\x03%i\x01",__LINE__);
	}
	bool operator<=(BigInteger const&q){
		return bn_cmp(this->q,q.q)<=0;printf("\x02\x03%i\x01",__LINE__);
	}
	bool operator!=(BigInteger const&q){
		return bn_cmp(this->q,q.q)!=0;printf("\x02\x03%i\x01",__LINE__);
	}
	bool operator>=(BigInteger const&q){
		return eic(bn_cmp(this->q,q.q))>=0;printf("\x02\x03%i\x01",__LINE__);
	}
	~BigInteger(){
		bn_delete(q);printf("\x02\x03%i\x01",__LINE__);
	}
	auto&operator+=(const BigInteger&q){
		bn_add_to(this->q,q.q);printf("\x02\x03%i\x01",__LINE__);
		return *this;printf("\x02\x03%i\x01",__LINE__);
	}
//(
};
//)



µ{
	test(BigInteger("1"),"\x1b[92m+\x1b[0m00000001");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-1"),"\x1b[92m-\x1b[0m00000001");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("1234"),"\x1b[92m+\x1b[0m00001234");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-1234"),"\x1b[92m-\x1b[0m00001234");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("12345678"),"\x1b[92m+\x1b[0m12345678");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-12345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("012345678"),"\x1b[92m+\x1b[0m00000000\x1b[92m12345678\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-012345678"),"\x1b[92m-\x1b[0m00000000\x1b[92m12345678\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("876543210"),"\x1b[92m+\x1b[0m00000008\x1b[92m76543210\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-876543210"),"\x1b[92m-\x1b[0m00000008\x1b[92m76543210\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("fedcba9876543210"),"\x1b[92m+\x1b[0mfedcba98\x1b[92m76543210\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("-fedcba9876543210"),"\x1b[92m-\x1b[0m00000000\x1b[92mfedcba98\x1b[0m76543210");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("1234567898765432123456789876543212345678987654321234567"),"\x1b[92m+\x1b[0m01234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567\x1b[92m89876543\x1b[0m21234567");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger("0"),"\x1b[92m0\x1b[0m00000000");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(4294967296),"\x1b[92m+\x1b[0m00000001\x1b[92m00000000\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(4294967295),"\x1b[92m+\x1b[0m00000000\x1b[92mffffffff\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(-2147483648),"\x1b[92m-\x1b[0m00000000\x1b[92m80000000\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(0),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(0)==BigInteger(0),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(0)==BigInteger("0"),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(1)==BigInteger(0),"False");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(1)==BigInteger(-1),"False");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(1)==BigInteger("1"),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(-1)==BigInteger("-1"),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(2)>BigInteger(1),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(-2)<BigInteger(-1),"True");printf("\x02\x03%i\x01",__LINE__);
	test(BigInteger(),"\x1b[92m0\x1b[0m")
	ic()
	auto q=BigInteger(1);printf("\x02\x03%i\x01",__LINE__);
	test(q+=3)
}

#endif