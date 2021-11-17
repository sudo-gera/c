#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>

struct bn_s{
	int8_t sign;
	size_t size;
	uint32_t *vect;
};

#ifdef CPP_R
#if COLORS
auto print_one(const bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"\x1b[92m%s\x1b[0m",1==q->sign?"+":-1==q->sign?"-":1<q->sign?"++":-1>q->sign?"--":"0");
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
	return print_one((const bn*)q);
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


enum bn_codes {
	BN_OK, BN_NULL_OBJECT, BN_NO_MEMORY, BN_DIVIDE_BY_ZERO
};

int bn_codes=1;

bn *bn_new(){
	return (bn*)calloc(sizeof(bn),1);
}

bn *bn_init(bn const*orig){
#if ERRORS
	if(!orig){
		return 0;
	}
#endif
	bn *q=(bn*)malloc(sizeof(bn));
#if ERRORS
	if (!q){
		return 0;
	}
#endif
	*q=*orig;
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
#if ERRORS
	if (!q->vect){
		return 0;
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];
	}
	return q;
}

static int bn_init_bn(bn* q,const bn*orig){
#if ERRORS
	if(!orig){
		return 0;
	}
	if(!q){
		return 0;
	}
#endif
	if (q->vect){
		free(q->vect);
	}
	*q=*orig;
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
#if ERRORS
	if (!q->vect){
		return 0;
	}
#endif
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];
	}
	return BN_OK;
}


int bn_init_int(bn *q,int _e){
	int64_t e=_e;
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


int bn_cmp(bn const *q, bn const *e){
	if (q->sign!=e->sign){
		return ((q->sign)-(e->sign));
	}
	if (q->size+e->size==0){
		return 0;
	}
	for (size_t c=(q->size>e->size?q->size:e->size)-1;;--c){
		size_t a=q->size>c?q->vect[c]:0;
		size_t s=e->size>c?e->vect[c]:0;
		if (a!=s){
			return ((a>s)*2-1)*q->sign;
		}
		if (!c){break;}
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
		q->vect=0;
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
		q->vect=0;
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
		q->vect=0;
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
	while (qs and q->vect[qs-1]==0){
		--qs;
	}
	while (es and e->vect[es-1]==0){
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
		if (q->vect[w]){
			for (size_t r=0;r<es;++r){
				*(uint64_t*)(tmp->vect+w+r)=(uint64_t)(q->vect[w])*(uint64_t)(e->vect[r]);
				bn_M_add_to(res,tmp);
				*(uint64_t*)(tmp->vect+w+r)=0;
			}
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

int bn_sign(const bn*q){
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
	size_t r=0;
	for (size_t w=0;w<q->size;++w){
		if (q->vect[w]){
			r=1;
			break;
		}
	}
	if (!r){
		q->sign=0;
	}
	return BN_OK;
}

int bn_M_div_to(bn*q,bn*e){
	size_t qs=q->size;
	size_t es=e->size;
	while (qs and q->vect[qs-1]==0){
		--qs;
	}
	while (es and e->vect[es-1]==0){
		--es;
	}
	bn*t=bn_new();
	t->size=qs+1;
	t->sign=1;
	t->vect=(uint32_t*)calloc(sizeof(uint32_t),t->size);
	for(size_t w=0;w<es;++w){
		t->vect[qs-es+1+w]=e->vect[w];
	}
	ssize_t f=(qs-es+1)*32;
	bn*r=bn_new();
	r->size=qs+1-es;
	r->sign=1;
	r->vect=(uint32_t*)calloc(sizeof(uint32_t),r->size);
	while (f>=0){
		if (bn_cmp(q,t)>=0){
			r->vect[f/32]|=(1LL<<(f%32));
			bn_M_sub_to(q,t);
		}
		f-=1;
		bn_half(t);
	}
	size_t rs=r->size;
	while (rs and r->vect[rs-1]==0){
		--rs;
	}
	if (!rs){
		r->sign=0;
	}
	bn_init_bn(e,r);
	bn_delete(r);
	bn_delete(t);
	return BN_OK;
}

bn* bn_div(const bn*q,const bn*e){
	bn*a=bn_init(q);
	bn_abs(a);
	if (e->sign==0){
		return 0;
	}
	bn*d=bn_init(e);
	bn_abs(d);
	bn_M_div_to(a,d);
	if (q->sign*e->sign<0){
		if (a->sign){
			bn_init_int(a,-1);
			bn_sub_to(a,d);
			bn_delete(d);
			return a;
		}
		d->sign*=-1;
		bn_delete(a);
		return d;
	}else{
		bn_delete(a);
		return d;
	}
}

int bn_div_to(bn*q,bn const*w){
	if (!w->sign){
		return BN_DIVIDE_BY_ZERO;
	}
	bn*u=bn_div(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return BN_OK;
}

// int bn_mod_to(bn*q,const bn*w){
// 	if (!w->sign){
// 		return BN_DIVIDE_BY_ZERO;
// 	}
// 	bn* h=bn_div(q,w);
// 	bn_mul_to(h,w);
// 	bn_sub_to(q,h);
// 	bn_delete(h);
// 	return BN_OK;
// }

// bn* bn_mod(const bn*q,const bn*w){
// 	bn*h=bn_init(q);
// 	bn_mod_to(h,w);
// 	return h;
// }

bn* bn_mod(const bn*q,const bn*e){
	bn*a=bn_init(q);
	bn_abs(a);
	if (e->sign==0){
		return 0;
	}
	bn*d=bn_init(e);
	bn_abs(d);
	bn_M_div_to(a,d);
	a->sign*=q->sign;
	if (q->sign*e->sign<0){
		if (a->sign){
			bn*r=bn_init(e);
			// bn_abs(r);
			r->sign*=-1;
			bn_sub_to(a,r);
			bn_delete(d);
			bn_delete(r);
			return a;
		}
		bn_delete(d);
		return a;
	}else{
		bn_delete(d);
		return a;
	}
}

int bn_mod_to(bn*q,bn const*w){
	if (!w->sign){
		return BN_DIVIDE_BY_ZERO;
	}
	bn*u=bn_mod(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return BN_OK;
}


int bn_pow_to(bn*q,int _e){
	int64_t e=_e;
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

static bn* bn_pow(bn*q,int w){
	bn*h=bn_init(q);
	bn_pow_to(h,w);
	return h;
}

int bn_root2_to(bn*q){
	bn*r=bn_new();
	r->size=q->size+1;
	r->sign=1;
	r->vect=(uint32_t*)calloc(sizeof(uint32_t),r->size);
	bn*p=bn_new();
	p->size=q->size+1;
	p->sign=1;
	p->vect=(uint32_t*)calloc(sizeof(uint32_t),p->size);
	p->vect[p->size-1]=1;
	bn*u;
	while(p->sign){
		u=bn_add(r,p);
		if (bn_cmp(q,u)>=0){
			bn_sub_to(q,u);
			bn_add_to(r,p);
			bn_add_to(r,p);
		}
		bn_half(r);
		bn_half(p);
		bn_half(p);
		bn_delete(u);
	}
	bn_init_bn(q,r);
	bn_delete(r);
	bn_delete(p);
	return BN_OK;
}

int bn_root_to(bn*q,int __e){
	if (__e==2){
		return bn_root2_to(q);
	}
	uint64_t e=__e;
	bn*_b=bn_new();
	bn*_e=bn_new();
	_e->size=q->size/2+1;
	_e->sign=1;
	_e->vect=(uint32_t*)calloc(sizeof(uint32_t),_e->size);
	if (_e->size){
		_e->vect[_e->size-1]=1;
	}
	bn*_c=bn_new();
	bn*_d=bn_new();	
	bn*_f=bn_new();
	bn*_g=bn_new();
	bn_init_int(_g,2);
	while (1){
		// ic(_b,_e)
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

static bn* bn_root(bn*q,int _w){
	uint64_t w=_w;
	bn*h=bn_init(q);
	bn_root_to(h,w);
	return h;
}

int bn_init_string_radix(bn*q,const char*e,int t){
	size_t l=strlen(e);
	q->size=l/6+1;
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
		bn_init_int(a,"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"
			[(int)(e[w])]);
		bn_add_to(q,a);
	}
	q->sign*=(-2)*g+1;  
	bn_delete(a);
	bn_delete(y);
	return BN_OK;
}

int bn_init_string(bn*q,const char*e){
	return bn_init_string_radix(q,e,10);
}



const char* bn_to_string(const bn*q,int e){
	uint64_t _t=e;
	bn*r=bn_init(q);
	bn_abs(r);
	bn*t=bn_new();
	char*a=(char*)calloc(sizeof(char),(q->size+1)*32);
	size_t s=0;
	while (r->sign){
		uint64_t b=0;
		uint64_t t=0;
		for (size_t _w=r->size;_w>0;--_w){size_t w=_w-1;
			t=r->vect[w];
			t+=b<<32;
			b=t%_t;
			t/=_t;
			r->vect[w]=t;
		}
		r->sign=0;
		for (size_t _w=r->size;_w>0;--_w){size_t w=_w-1;
			if (r->vect[w]){
				r->sign=1;
				break;
			}
		}
		a[s++]=b;
	}
	for (size_t w=0;w<s;++w){
		a[w]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(int)(a[w])];
	}
	if (q->sign<0){
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
	bn_delete(r);
	bn_delete(t);
	return a;
}
















