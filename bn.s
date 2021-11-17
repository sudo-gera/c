#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>

#if __has_include("h")
#ifndef C_R
#define CPP_R
#endif
#endif

#ifdef CPP_R
#include "bn.h"
#include "d"
#endif

#ifdef C_R
#include "bn.h"
#endif

#define NORMAL_SIZE 0

#define ERRORS 0


#define COLORS 1

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

int bn_init_int(bn *q,int e){
	return bn_init_int(q,int64_t(e));
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

#ifdef CPP_R
#if COLORS
auto print_one(const bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"\x1b[92m%c\x1b[0m",1==q->sign?'+':-1==q->sign?'-':'0');
	int c=0;
	for (int t=q->size-1;t>-1;--t){
		if (c%2){
			sprintf(b+strlen(b),"\x1b[92m");
		}
		sprintf(b+strlen(b),"%0*x",8,q->vect[t]);
		if (c%2){
			sprintf(b+strlen(b),"\x1b[0m");
		}
		++c;
	}
	return str(b);
}

auto print_one(bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"\x1b[92m%c\x1b[0m",1==q->sign?'+':-1==q->sign?'-':'0');
	int c=0;
	for (int t=q->size-1;t>-1;--t){
		if (c%2){
			sprintf(b+strlen(b),"\x1b[92m");
		}
		sprintf(b+strlen(b),"%0*x",8,q->vect[t]);
		if (c%2){
			sprintf(b+strlen(b),"\x1b[0m");
		}
		++c;
	}
	return str(b);
}

#else

auto print_one(const bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"%c",1==q->sign?'+':-1==q->sign?'-':'0');
	int c=0;
	for (int t=q->size-1;t>-1;--t){
		if (c%2){
			sprintf(b,"%s",b);
		}
		sprintf(b+strlen(b),"%0*x",8,q->vect[t]);
		if (c%2){
			sprintf(b,"%s",b);
		}
		++c;
	}
	return str(b);
}

auto print_one(bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"%c",1==q->sign?'+':-1==q->sign?'-':'0');
	int c=0;
	for (int t=q->size-1;t>-1;--t){
		if (c%2){
		}
		sprintf(b+strlen(b),"%0*x",8,q->vect[t]);
		if (c%2){
		}
		++c;
	}
	return str(b);
}
#endif
#endif

int bn_cmp(bn const *q, bn const *e){
	if (q->sign!=e->sign){
		return q->sign-e->sign;
	}
	for (ssize_t c=(q->size>e->size?q->size:e->size)-1;c>=0;--c){
		auto a=q->size>c?q->vect[c]:0;
		auto s=e->size>c?e->vect[c]:0;
		if (a!=s){
			return ((a>s)*2-1)*q->sign;
		}
	}
	return 0;
}

static int bn_M_add_to(bn *q, bn const *e){
	if (!q){
		return BN_NULL_OBJECT;
	}
	if (!e){
		return BN_NULL_OBJECT;
	}
	size_t qs=q->size;
	if (qs and q->vect[qs-1]==0){
		qs-=1;
	}
	size_t es=e->size;
	if (es and e->vect[es-1]==0){
		es-=1;
	}
	qs=(qs>es?qs:es)+1;
	if (qs!=q->size){
		q->vect=(uint32_t*)realloc(q->vect,qs*sizeof(uint32_t));
	}
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;
	}
#endif
	for (size_t w=q->size;w<qs;++w){
		q->vect[w]=0;
	}
	q->size=qs;
	uint64_t buff=0;
	for (size_t w=0;w<q->size;++w){
		buff+=q->vect[w];
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
	size_t qs=q->size;
	if (qs and q->vect[qs-1]==0){
		qs-=1;
	}
	size_t es=e->size;
	if (es and e->vect[es-1]==0){
		es-=1;
	}
	qs=(qs>es?qs:es)+1;
	q->vect=(uint32_t*)realloc(q->vect,qs*sizeof(uint32_t));
#if ERRORS
	if(!q->vect){
		return BN_NO_MEMORY;
	}
#endif
	for (size_t w=q->size;w<qs;++w){
		q->vect[w]=0;
	}
	q->size=qs;
	int64_t buff=0;
	for (size_t w=0;w<q->size;++w){
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

int bn_add_to(bn*q,const bn*e){
	bn* h=bn_new();
	int j=q->sign;
	int k=e->sign;
	int8_t qs=q->sign;
	q->sign=e->sign;
	int l=bn_cmp(q,e);
	q->sign=qs;
	bn_delete(h);
	if (!k){
		return BN_OK;
	}
	if (j<=0){
		if (k<0){
			bn_M_add_to(q,e);
			q->sign=-1;
		}else{
			if (l>=0){
				bn_M_sub_to(q,e);
			}else{
				bn*h=bn_init(q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
				bn_delete(h);
			}
		}
	}else{
		if (k<0){
			if (l<=0){
				bn_M_sub_to(q,e);
			}else{
				bn*h=bn_init(q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
				bn_delete(h);
			}
		}else{
			bn_M_add_to(q,e);
			q->sign=1;
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

int bn_sub_to(bn*q,const bn*e){
	q->sign*=-1;
	bn* h=bn_new();
	int j=q->sign;
	int k=e->sign;
	int8_t qs=q->sign;
	q->sign=e->sign;
	int l=bn_cmp(q,e);
	q->sign=qs;
	bn_delete(h);
	if (!k){
		q->sign*=-1;
		return BN_OK;
	}
	if (j<=0){
		if (k<0){
			bn_M_add_to(q,e);
			q->sign=-1;
		}else{
			if (l>=0){
				bn_M_sub_to(q,e);
			}else{
				bn*h=bn_init(q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
				bn_delete(h);
			}
		}
	}else{
		if (k<0){
			if (l<=0){
				bn_M_sub_to(q,e);
			}else{
				bn*h=bn_init(q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
				bn_delete(h);
			}
		}else{
			bn_M_add_to(q,e);
			q->sign=1;
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
	q->sign*=-1;
	return BN_OK;
}

bn* bn_add(const bn*q,const bn*w){
	bn*h=bn_init(q);
	bn_add_to(h,w);
	return h;
}

bn* bn_sub(const bn*q,const bn*w){
	bn*h=bn_init(q);
	bn_sub_to(h,w);
	return h;
}

bn* bn_mul(bn const*q,const bn*e){
	bn*res=bn_new();
	bn*tmp=bn_new();
	size_t qs=q->size;
	size_t es=e->size;
	if (qs and q->vect[qs-1]==0){
		--qs;
	}
	if (es and e->vect[es-1]==0){
		--es;
	}
	res->size=qs+es;
	tmp->size=qs+es;
	res->vect=(uint32_t*)realloc(res->vect,res->size*sizeof(uint32_t));
	tmp->vect=(uint32_t*)realloc(tmp->vect,tmp->size*sizeof(uint32_t));
	for (size_t w=0;w<res->size;++w){
		res->vect[w]=0;
		tmp->vect[w]=0;
	}
	tmp->sign=1;
	for (size_t w=0;w<qs;++w){
		for (size_t r=0;r<es;++r){
			*(uint64_t*)(tmp->vect+w+r)=uint64_t(q->vect[w])*uint64_t(e->vect[r]);
			bn_add_to(res,tmp);
			*(uint64_t*)(tmp->vect+w+r)=0;
		}
	}
	res->sign=q->sign*e->sign;
	bn_delete(tmp);
	return res;
}

int bn_mul_to(bn*q,bn const*w){
	bn*u=bn_mul(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return BN_OK;
}

int bn_neg(bn*q){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;
	}
#endif
	q->sign*=-1;
	return BN_OK;
}

int bn_abs(bn*q){
#if ERRORS
	if (!q){
		return BN_NULL_OBJECT;
	}
#endif
	q->sign=q->sign<0?-q->sign:q->sign;
	return BN_OK;
}

int bn_sign(bn*q){
	return q->sign>0?1:q->sign<0?-1:0;
}

static int bn_half(bn*q){
	if (q->size){
		q->vect[0]>>=1;
	}
	for (size_t w=1;w<q->size;++w){
		q->vect[w-1]|=(q->vect[w]&1)<<31;
		q->vect[w]>>=1;
	}
	return BN_OK;
}

int bn_P_div_(bn*q,bn*e){
	bn*_b=bn_new();
	bn*_e=bn_init(q);
	bn*_c=bn_new();
	bn*_d=bn_new();	
	bn*_f=bn_new();
	bn*_g=bn_new();
	bn_init_int(_g,2);
	while (1){
		bn_init_bn(_f,_e);
		bn_sub_to(_f,_b);
		if (bn_cmp(_f,_g)<0){
			break;
		}
		bn_init_bn(_c,_b);
		bn_add_to(_c,_e);
		bn_half(_c);
		bn_init_bn(_d,_c);
		bn_mul_to(_d,e);
		int j=bn_cmp(_d,q);
		if (j<0){
			bn_init_bn(_b,_c);
		}else
		if (j>0){
			bn_init_bn(_e,_c);
		}else
		if (j==0){
			bn_init_bn(_e,_c);
			bn_init_bn(_b,_c);
		}
	}
	bn_delete(_c);
	bn_delete(_d);
	bn_delete(_f);
	bn_delete(_g);
	bn_init_bn(q,_b);
	bn_init_bn(e,_e);
	bn_delete(_e);
	bn_delete(_b);
	return BN_OK;
}

bn* bn_div(const bn*q,const bn*e){
	bn*a=bn_init(q);
	bn_abs(a);
	bn*d=bn_new();
	if (bn_cmp(d,e)==0){
		return nullptr;
	}
	bn_init_bn(d,e);
	bn_abs(d);
	bn_P_div_(a,d);
	d->sign*=-1;
	if (q->sign*e->sign<0){
		bn_delete(a);
		return d;
	}else{
		bn_delete(d);
		return a;
	}
}

int bn_div_to(bn*q,bn const*w){
	auto h=bn_new();
	if (bn_cmp(w,h)==0){
		return BN_DIVIDE_BY_ZERO;
	}
	bn*u=bn_div(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	bn_delete(h);
	return BN_OK;
}

int bn_mod_to(bn*q,const bn*w){
	auto h=bn_new();
	if (bn_cmp(w,h)==0){
		return BN_DIVIDE_BY_ZERO;
	}
	bn_delete(h);
	h=bn_div(q,w);
	bn_mul_to(h,w);
	bn_sub_to(q,h);
	bn_delete(h);
	return BN_OK;
}

bn* bn_mod(bn*q,const bn*w){
	bn*h=bn_init(q);
	bn_mod_to(h,w);
	return h;
}

int bn_pow_to(bn*q,uint64_t e){
	size_t s=0;
	for (size_t w=0;w<64;++w){
		if ((1ULL<<w&e)){
			s=w+1;
		}
	}
	if(s){
		bn**a=(bn**)malloc(sizeof(bn*)*s);
		a[0]=bn_init(q);
		for (size_t w=1;w<s;++w){
			a[w]=bn_init(a[w-1]);
			bn_mul_to(a[w],a[w]);
		}
		bn_init_int(q,1);
		for (size_t w=0;w<s;++w){
			if ((1<<w)&e){
				bn_mul_to(q,a[w]);
			}
		}
		for (size_t w=0;w<s;++w){
			bn_delete(a[w]);
		}
		free(a);
	}else{
		bn_init_int(q,1);
	}
	return BN_OK;
}

static bn* bn_pow(bn*q,uint64_t w){
	bn*h=bn_init(q);
	bn_pow_to(h,w);
	return h;
}

int bn_root_to(bn*q,uint64_t e){
	bn*_b=bn_new();
	bn*_e=bn_init(q);
	bn*_c=bn_new();
	bn*_d=bn_new();	
	bn*_f=bn_new();
	bn*_g=bn_new();
	bn_init_int(_g,2);
	while (1){
		bn_init_bn(_f,_e);
		bn_sub_to(_f,_b);
		if (bn_cmp(_f,_g)<0){
			break;
		}
		bn_init_bn(_c,_b);
		bn_add_to(_c,_e);
		bn_half(_c);
		bn_init_bn(_d,_c);
		bn_pow_to(_d,e);
		int j=bn_cmp(_d,q);
		if (j<0){
			bn_init_bn(_b,_c);
		}else
		if (j>0){
			bn_init_bn(_e,_c);
		}else
		if (j==0){
			bn_init_bn(_e,_c);
			bn_init_bn(_b,_c);
		}
	}
	bn_delete(_c);
	bn_delete(_d);
	bn_delete(_f);
	bn_delete(_g);
	bn_init_bn(q,_b);
	bn_delete(_b);
	bn_delete(_e);
	return BN_OK;
}

static bn* bn_root(bn*q,uint64_t w){
	bn*h=bn_init(q);
	bn_root_to(h,w);
	return h;
}

int bn_init_string_radix(bn*q,const char*e,int t){
	size_t l=strlen(e);
	q->size=l/9+1;
	q->sign=0;
	if (q->vect){
		free(q->vect);
	}
	q->vect=(uint32_t*)calloc(sizeof(uint32_t),q->size);
	bn*a=bn_new();
	bn*y=bn_new();
	bn_init_int(y,t);
	int g=0;
	if (l and e[0]=='-'){
		g=1;
	}
	for (size_t w=g;w<l;++w){
		bn_mul_to(q,y);
		bn_init_int(a,"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[int(e[w])]);
		bn_add_to(q,a);
	}
	q->sign+=(-2)*g;
	bn_delete(a);
	bn_delete(y);
	return BN_OK;
}

int bn_init_string(bn*q,const char*e){
	return bn_init_string_radix(q,e,10);
}

const char* bn_to_string(const bn*q,int e){
	bn*r=bn_init(q);
	bn_abs(r);
	bn*t=bn_new();
	bn*y;
	bn*u=bn_new();
	bn_init_int(u,e);
	char*a=(char*)calloc(sizeof(char),q->size*32);
	int s=0;
	while (bn_cmp(r,t)){
		y=bn_mod(r,u);
		a[s++]=y->size?y->vect[0]:0;
		bn_delete(y);
		bn_div_to(r,u);
	}
	for (size_t w=0;w<s;++w){
		a[w]="0123456789abcdefghijklmnopqrstuvwxyz"[int(a[w])];
	}
	if (q->sign<0){
		a[s++]='-';
	}
	for (size_t w=0;w*2<s;++w){
		char t=a[w];
		a[w]=a[s-1-w];
		a[s-1-w]=t;
	}
	bn_delete(r);
	bn_delete(t);
	bn_delete(u);
	return a;
}


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
#if COLORS
	template <typename T>
	friend auto &operator<<(T& q,BigInteger f){
		char b[99999];
		b[0]=0;
		sprintf(b+strlen(b),"\x1b[92m%c\x1b[0m",1==f.q->sign?'+':-1==f.q->sign?'-':'0');
		int c=0;
		for (int t=f.q->size-1;t>-1;--t){
			if (c%2){
				sprintf(b+strlen(b),"\x1b[92m");
			}
			sprintf(b+strlen(b),"%0*x",8,f.q->vect[t]);
			if (c%2){
				sprintf(b+strlen(b),"\x1b[0m");
			}
			++c;
		}
		q<<b;
		return q;
	}
#else
	template <typename T>
	friend auto &operator<<(T& q,BigInteger f){
		char b[99999];
		b[0]=0;
		sprintf(b+strlen(b),"%c",1==f.q->sign?'+':-1==f.q->sign?'-':'0');
		int c=0;
		for (int t=f.q->size-1;t>-1;--t){
			if (c%2){
			}
			sprintf(b+strlen(b),"%0*x",8,f.q->vect[t]);
			if (c%2){
			}
			++c;
		}
		q<<b;
		return q;
	}
#endif
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
	std::string str(int64_t w){
		auto h=bn_to_string(q,w);
		auto g=std::string(h);
		char *u=(char*)h;
		free(u);
		return g;
	}
};


signed main(){
#if COLORS
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
	test(q*2147483648,"\x1b[92m-\x1b[0m00000000\x1b[92m40000000\x1b[0m00000000");
	test(q/2147483648,"\x1b[92m-\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger(17)/10,"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger(-17)/10,"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(BigInteger(17)/(-10),"\x1b[92m-\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(BigInteger(-17)/(-10),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger(0)/(-10),"\x1b[92m0\x1b[0m");
	test(BigInteger(0)/(+10),"\x1b[92m0\x1b[0m");
	h=BigInteger("ffffffffffffffffffffffffffffffff");
	test(h/15,"\x1b[92m+\x1b[0m00000000\x1b[92m11111111\x1b[0m11111111\x1b[92m11111111\x1b[0m11111111")
	test(h/BigInteger("ffffffff"),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m00000001\x1b[92m00000001\x1b[0m00000001")
	test(h%BigInteger("ffffffff"),"\x1b[92m0\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000\x1b[92m00000000\x1b[0m00000000")
	test(BigInteger(2) ** BigInteger(2),"\x1b[92m+\x1b[0m00000000\x1b[92m00000004\x1b[0m");
	test(BigInteger(2) ** BigInteger(10),"\x1b[92m+\x1b[0m00000000\x1b[92m00000400\x1b[0m");
	test(BigInteger(7) ** BigInteger(7),"\x1b[92m+\x1b[0m00000000\x1b[92m000c90f7\x1b[0m");
	test(BigInteger(23) ** BigInteger(23),"\x1b[92m+\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	test(BigInteger(-23) ** BigInteger(23),"\x1b[92m-\x1b[0m00000000\x1b[92m00000107\x1b[0m8c6e4f7d\x1b[92m75450b1f\x1b[0mb3ec6ae7");
	test(BigInteger(23) ** BigInteger(24),"\x1b[92m+\x1b[0m00000000\x1b[92m000017ad\x1b[0m9de92445\x1b[92m8933ffd9\x1b[0m2a3d9ac1");
	test(BigInteger(16)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000002\x1b[0m");
	test(BigInteger(15)/ *BigInteger(4),"\x1b[92m+\x1b[0m00000000\x1b[92m00000001\x1b[0m");
	test(BigInteger("123456",7),"\x1b[92m+\x1b[0m00000000\x1b[92m0000595b\x1b[0m");
	test(BigInteger("zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m+\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36),"\x1b[92m-\x1b[0m00000000\x1b[92m0455d441\x1b[0me55a3723\x1b[92m9ab4c303\x1b[0m18957607\x1b[92m1af5578f\x1b[0mfca80504");
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36).str(36),"-zyxwvutsrqponmlkjihgfedcba9876543210");
#else
	test(BigInteger("1"),"+00000001");
	test(BigInteger("-1"),"-00000001");
	test(BigInteger("1234"),"+00001234");
	test(BigInteger("-1234"),"-00001234");
	test(BigInteger("12345678"),"+12345678");
	test(BigInteger("-12345678"),"-0000000012345678");
	test(BigInteger("012345678"),"+0000000012345678");
	test(BigInteger("-012345678"),"-0000000012345678");
	test(BigInteger("876543210"),"+0000000876543210");
	test(BigInteger("-876543210"),"-0000000876543210");
	test(BigInteger("fedcba9876543210"),"+fedcba9876543210");
	test(BigInteger("-fedcba9876543210"),"-00000000fedcba9876543210");
	auto _h=BigInteger("1234567898765432123456789876543212345678987654321234567");
	test(_h,"+01234567898765432123456789876543212345678987654321234567");
	test(BigInteger("1234567898765432123456789876543212345678987654321234567"),"+01234567898765432123456789876543212345678987654321234567");
	test(BigInteger("0"),"000000000");
	test(BigInteger(4294967296),"+0000000100000000");
	test(BigInteger(4294967295),"+00000000ffffffff");
	test(BigInteger(-2147483648),"-0000000080000000");
	test(BigInteger(0),"00000000000000000");
	test(BigInteger(0),"00000000000000000");
	test(BigInteger(0)==BigInteger(0),"True");
	test(BigInteger(0)==BigInteger("0"),"True");
	test(BigInteger(1)==BigInteger(0),"False");
	test(BigInteger(1)==BigInteger(-1),"False");
	test(BigInteger(1)==BigInteger("1"),"True");
	test(BigInteger(-1)==BigInteger("-1"),"True");
	test(BigInteger(2)>BigInteger(1),"True");
	test(BigInteger(-2)<BigInteger(-1),"True");
	test(BigInteger("ffffffffffffffffffffffffffffffff")<BigInteger(2),"False");
	test(BigInteger(),"0")
	auto q=BigInteger(1);
	test(q+=1,"+0000000000000002");
	test(q+=-1,"+0000000000000001");
	test(q-=1,"00000000000000000");
	test(q+=-1,"-0000000000000001");
	test(q+=-1,"-0000000000000002");
	test(q-=-3,"+0000000000000001");
	test(q+=-2,"-0000000000000001");
	test(q+=0,"-0000000000000001");
	test(q+=-2,"-0000000000000003");
	test(q-=-2,"-0000000000000001");
	test(q+=1,"00000000000000000");
	test(q+=1,"+0000000000000001");
	test(q+=0,"+0000000000000001");
	auto h=BigInteger("ffffffffffffffffffffffff");
	test(q+=h,"+00000001000000000000000000000000");
	test(q-=h,"+0000000000000000000000000000000000000001");
	test(q-=1,"00000000000000000000000000000000000000000");
	test(q-=0,"00000000000000000000000000000000000000000");
	test(q-=1,"-0000000000000000000000000000000000000001");
	test(q-=0,"-0000000000000000000000000000000000000001");
	test(q-=h,"-0000000000000001000000000000000000000000");
	test(q+=2,"-0000000000000000fffffffffffffffffffffffe");
	test(q+=h,"+0000000000000000000000000000000000000001");
	q=1;
	test(q*1,"+0000000000000001");
	test(q*2,"+0000000000000002");
	q=-4;
	test(q*-4,"+0000000000000010");
	q=-2147483648;
	test(q*2147483648,"-000000004000000000000000");
	test(q/2147483648,"-0000000000000001");
	test(BigInteger(17)/10,"+0000000000000001");
	test(BigInteger(-17)/10,"-0000000000000002");
	test(BigInteger(17)/(-10),"-0000000000000002");
	test(BigInteger(-17)/(-10),"+0000000000000001");
	test(BigInteger(0)/(-10),"0");
	test(BigInteger(0)/(+10),"0");
	h=BigInteger("ffffffffffffffffffffffffffffffff");
	test(h/15,"+0000000011111111111111111111111111111111")
	test(h/BigInteger("ffffffff"),"+0000000000000001000000010000000100000001")
	test(h%BigInteger("ffffffff"),"00000000000000000000000000000000000000000")
	test(BigInteger(2) ** BigInteger(2),"+0000000000000004");
	test(BigInteger(2) ** BigInteger(10),"+0000000000000400");
	test(BigInteger(7) ** BigInteger(7),"+00000000000c90f7");
	test(BigInteger(23) ** BigInteger(23),"+00000000000001078c6e4f7d75450b1fb3ec6ae7");
	test(BigInteger(-23) ** BigInteger(23),"-00000000000001078c6e4f7d75450b1fb3ec6ae7");
	test(BigInteger(23) ** BigInteger(24),"+00000000000017ad9de924458933ffd92a3d9ac1");
	test(BigInteger(16)/ *BigInteger(4),"+0000000000000002");
	test(BigInteger(15)/ *BigInteger(4),"+0000000000000001");
	test(BigInteger("123456",7),"+000000000000595b");
	test(BigInteger("zyxwvutsrqponmlkjihgfedcba9876543210",36),"+000000000455d441e55a37239ab4c303189576071af5578ffca80504");
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36),"-000000000455d441e55a37239ab4c303189576071af5578ffca80504");
	test(BigInteger("-zyxwvutsrqponmlkjihgfedcba9876543210",36).str(36),"-zyxwvutsrqponmlkjihgfedcba9876543210");
#endif
}
#endif

#ifdef C_R
int main(){
}
#endif