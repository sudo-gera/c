#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

struct bn_s{
	int8_t sign;
	uint32_t size;
	uint32_t*vect;
};

typedef struct bn_s bn;



#ifdef CPP_R
auto print_one(const bn*q){
	char b[99999];
	b[0]=0;
	sprintf(b+strlen(b),"\x1b[92m%s\x1b[0m",1==q->sign?"+":-1==q->sign?"-":1<q->sign?"++":-1>q->sign?"--":"0");
	int c=0;
	if (q->size){
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
	}else{
		sprintf(b+strlen(b),"\x1b[93m%0*llx\x1b[0m",16,uint64_t(q->vect));
	}
	return str(b);
}

auto print_one(bn*q){
	return print_one((const bn*)q);
}
#endif

bn *bn_new(){
	return (bn*)calloc(sizeof(bn),1);
}

bn *bn_init(bn const*orig){
	bn *q=(bn*)malloc(sizeof(bn));
	*q=*orig;
	if (orig->size){
		q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
		for (size_t w=0;w<q->size;++w){
			q->vect[w]=orig->vect[w];
		}
	}
	return q;
}

static int bn_init_bn(bn* q,const bn*orig){
	if (q->size and q->vect){
		free(q->vect);
	}
	*q=*orig;
	if (q->size){
		q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
		for (size_t w=0;w<q->size;++w){
			q->vect[w]=orig->vect[w];
		}
	}
	return 0;
}

int bn_init_int(bn *q,int e){
	if (q->size and q->vect){
		free(q->vect);
	}
	q->sign=e>0?1:e<0?-1:0;
	q->size=0;
	q->vect=(uint32_t*)(uint64_t)(q->sign*(int64_t)(e));
	// q->vect=(uint32_t*)malloc(sizeof(uint32_t)*1);
	// q->size=1;
	// q->sign=e>0?1:e<0?-1:0;
	// q->vect[0]=q->sign*e;
	return 0;
}

int bn_delete(bn *q){
	if (q->size and q->vect){
		free(q->vect);
	}
	free(q);
	return 0;
}

static int bn_del(bn *q){
	if (q->size and q->vect){
		free(q->vect);
	}
	return 0;
}

int bn_cmp(bn const *q, bn const *e){
	if (q->sign!=e->sign){
		return ((q->sign)-(e->sign));
	}
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	for (size_t c=(qs>es?qs:es)-1;;--c){
		size_t a=qs>c?qv[c]:0;
		size_t s=es>c?ev[c]:0;
		if (a!=s){
			return ((a>s)*2-1)*q->sign;
		}
		if (!c){break;}
	}
	return 0;
	return 0;
}

static int bn_M_add_to(bn *q, bn const *e){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	while (qs and qv[qs-1]==0){
		qs-=1;
	}
	while (es and ev[es-1]==0){
		es-=1;
	}
	qs=(qs>es?qs:es)+1;
	if (q->size and qs>q->size){
		q->vect=(uint32_t*)realloc(q->vect,qs*sizeof(uint32_t));
		qv=q->vect;
		for (size_t w=q->size;w<qs;++w){
			q->vect[w]=0;
		}
		q->size=qs;
	}else if (q->size==0 and qs>2){
		uint64_t tmp=*(uint64_t*)&(q->vect);
		q->vect=(uint32_t*)calloc(1,qs*sizeof(uint32_t));
		*(uint64_t*)(q->vect)=tmp;
		qv=q->vect;
		q->size=qs;
	}else if (q->size and qs<3){
		uint64_t tmp=*(uint64_t*)(q->vect);
		free(q->vect);
		q->size=0;
		*(uint64_t*)&(q->vect)=tmp;
		qv=(uint32_t*)&(q->vect);
	}
	uint64_t buff=0;
	for (size_t w=0;w<qs;++w){
		buff+=qv[w];
		if (w<es){
			buff+=ev[w];
		}
		qv[w]=buff&0b11111111111111111111111111111111;
		buff>>=32;
	}
	return 0;
}

static int bn_M_add_to_fast(bn *q, bn const *e,uint64_t start){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	if (qs and qv[qs-1]==0){
		qs-=1;
	}
	if (es and ev[es-1]==0){
		es-=1;
	}
	qs=(qs>es?qs:es)+1;
	if (q->size and qs>q->size){
		q->vect=(uint32_t*)realloc(q->vect,qs*sizeof(uint32_t));
		qv=q->vect;
		for (size_t w=q->size;w<qs;++w){
			q->vect[w]=0;
		}
		q->size=qs;
	}else if (q->size==0 and qs>2){
		uint64_t tmp=*(uint64_t*)&(q->vect);
		q->vect=(uint32_t*)calloc(1,qs*sizeof(uint32_t));
		*(uint64_t*)(q->vect)=tmp;
		qv=q->vect;
		q->size=qs;
	}else if (q->size and qs<3){
		uint64_t tmp=*(uint64_t*)(q->vect);
		free(q->vect);
		q->size=0;
		*(uint64_t*)&(q->vect)=tmp;
		qv=(uint32_t*)&(q->vect);
	}
	uint64_t buff=0;
	for (size_t w=start;w<qs;++w){
		buff+=qv[w];
		if (w<es){
			buff+=ev[w];
		}
		qv[w]=buff&0b11111111111111111111111111111111;
		buff>>=32;
		if (!buff and w>start){
			return 0;
		}
	}
	return 0;
}

static int bn_M_sub_to(bn *q, bn const *e){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	while (qs and qv[qs-1]==0){
		qs-=1;
	}
	while (es and ev[es-1]==0){
		es-=1;
	}
	qs=(qs>es?qs:es)+1;
	if (q->size and qs>q->size){
		q->vect=(uint32_t*)realloc(q->vect,qs*sizeof(uint32_t));
		qv=q->vect;
		for (size_t w=q->size;w<qs;++w){
			q->vect[w]=0;
		}
		q->size=qs;
	}else if (q->size==0 and qs>2){
		uint64_t tmp=*(uint64_t*)&(q->vect);
		q->vect=(uint32_t*)calloc(1,qs*sizeof(uint32_t));
		*(uint64_t*)(q->vect)=tmp;
		qv=q->vect;
		q->size=qs;
	}else if (q->size and qs<3){
		uint64_t tmp=*(uint64_t*)(q->vect);
		free(q->vect);
		q->size=0;
		*(uint64_t*)&(q->vect)=tmp;
		qv=(uint32_t*)&(q->vect);
	}
	int64_t buff=0;
	for (size_t w=0;w<qs;++w){
		buff+=qv[w];
		if (w<es){
			buff-=ev[w];
		}
		qv[w]=buff&0b11111111111111111111111111111111;
		buff>>=32;
	}
	size_t b=0;
	for (size_t w=0;w<qs;++w){
		if (qv[w]){
			b=1;
			break;
		}
	}
	if (!b){
		q->sign=0;
	}
	return 0;
}

int bn_add_to(bn*q,const bn*e){
	int j=q->sign;
	int k=e->sign;
	int l;
	{
		int8_t qs=q->sign;
		q->sign=e->sign;
		l=bn_cmp(q,e);
		q->sign=qs;
	}
	if (!k){
		return 0;
	}
	bn data[1];
	memset(data,0,sizeof(data));
	bn*h=data[0];
	if (j<=0){
		if (k<0){
			bn_M_add_to(q,e);
			q->sign=-1;
		}else{
			if (l>=0){
				bn_M_sub_to(q,e);
			}else{
				bn_init_bn(h,q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
			}
		}
	}else{
		if (k<0){
			if (l<=0){
				bn_M_sub_to(q,e);
			}else{
				bn_init_bn(h,q);
				bn_init_bn(q,e);
				bn_M_sub_to(q,h);
				bn_delete(h);
			}
		}else{
			bn_M_add_to(q,e);
			q->sign=1;
		}
	}
	bn_del(h);
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	size_t b=0;
	for (size_t w=0;w<qs;++w){
		if (qv[w]){
			b=1;
			break;
		}
	}
	if (!b){
		q->sign=0;
	}
	return 0;
}

int bn_sub_to(bn*q,const bn*e){
	q->sign*=-1;
	bn_add_to(q,e);
	q->sign*=-1;
	return 0;
}

bn* bn_add(const bn*q,const bn*w){
	bn*h=bn_init(q);
	bn_add_to(h,w);
	return h;
	return 0;
}

bn* bn_sub(const bn*q,const bn*w){
	bn*h=bn_init(q);
	bn_sub_to(h,w);
	return h;
	return 0;
}

bn* bn_mul(bn const*q,const bn*e){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	while (qs and qv[qs-1]==0){
		--qs;
	}
	while (es and ev[es-1]==0){
		--es;
	}
	bn data[2];
	memset(data,0,sizeof(data));
	bn*res=data+0;
	if (qs+es>2){
		bn*tmp=data+1;
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
			if (qv[w]){
				for (size_t r=0;r<es;++r){
					*(uint64_t*)(tmp->vect+w+r)=((uint64_t)(qv[w]))*((uint64_t)(ev[r]));
					bn_M_add_to_fast(res,tmp,w+r);
					*(uint64_t*)(tmp->vect+w+r)=0;
				}
			}
		}
		res->sign=q->sign*e->sign;
		bn_delete(tmp);
	}else{
		res->sign=q->sign*e->sign;
		res->size=0;
		*(uint64_t*)&(res->vect)=*(uint64_t*)(qv)**(uint64_t*)(ev);
	}
	return res;
	return 0;
}

int bn_mul_to(bn*q,bn const*w){
	bn*u=bn_mul(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return 0;
}

int bn_neg(bn*q){
	q->sign*=-1;
	return 0;
}

int bn_abs(bn*q){
	q->sign=(bool)(q->sign);
	return 0;
}

int bn_sign(const bn*q){
	return q->sign;
	return 0;
}

static int bn_half(bn*q){
	if (q->size){
		q->vect[0]>>=1;
	}else{
		*(uint64_t*)&(q->vect)>>=1;
		if (!*(uint64_t*)&(q->vect)){
			q->sign=0;
		}
		return 0;
	}
	for (size_t w=1;w<q->size;++w){
		q->vect[w-1]|=(q->vect[w]&1)<<31;
		q->vect[w]>>=1;
	}
	size_t b=0;
	for (size_t w=0;w<q->size;++w){
		if (q->vect[w]){
			b=1;
			break;
		}
	}
	if (!b){
		q->sign=0;
	}
	return 0;
}


int bn_M_div_to(bn*q,bn*e){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	uint32_t* ev=e->size?e->vect:(uint32_t*)&(e->vect);
	uint32_t es=e->size?e->size:2;
	// ic(q,e)
	while (qs and qv[qs-1]==0){
		--qs;
	}
	while (es and ev[es-1]==0){
		--es;
	}
	bn data[2];
	memset(data,0,sizeof(data));
	if(qs>=es){
		bn*t=data+0;
		t->size=qs+2;
		t->sign=1;
		t->vect=(uint32_t*)calloc(sizeof(uint32_t),t->size);
		for(size_t w=0;w<es;++w){
			t->vect[qs-es+2+w]=ev[w];
		}
		// bn**a=(bn**)malloc(sizeof(bn*)*32);
		// a[31]=bn_init(t);
		// bn_half(a[31]);
		// for (size_t w=31;w>1;--w){
		// 	a[w-1]=bn_init(a[w]);
		// 	bn_half(a[w-1]);
		// }
		// a[0]=bn_init(t);
		// uint64_t*o=(uint64_t*)calloc(32,sizeof(uint64_t));
		ssize_t f=(qs-es+2)*32;
		bn*r=data+1;
		uint32_t*rv;
		uint32_t rs;
		if (qs+1-es>2){
			r->size=qs+1-es;
			r->sign=1;
			r->vect=(uint32_t*)calloc(sizeof(uint32_t),r->size);
			rv=r->vect;
			rs=r->size;
		}else{
			r->size=0;
			r->sign=1;
			r->vect=0;
			rv=(uint32_t*)&(r->vect);
			rs=2;
		}
		while (f>=0){
			// ic(q,r,a[f&0b11111],f)
			// if (bn_cmp(q,a[f&0b11111])>=0){
			// 	rv[f>>5]|=(1LL<<(f&0b11111));
			// 	bn_M_sub_to(q,a[f&0b11111]);
			// }
			// a[f&0b11111]->size-=1;
			// a[f&0b11111]->vect+=1;
			// o[f&0b11111]+=1;
			// f-=1;
			// // bn_half(t);
			if (bn_cmp(q,t)>=0){
				rv[f>>5]|=(1LL<<(f&0b11111));
				bn_M_sub_to(q,t);
			}
			// t->size-=1;
			// t->vect+=1;
			// o[f&0b11111]+=1;
			f-=1;
			bn_half(t);
		}
		size_t b=0;
		for (size_t w=0;w<rs;++w){
			if (rv[w]){
				b=1;
				break;
			}
		}
		if (!b){
			r->sign=0;
		}
		// for (size_t w=0;w<32;++w){
		// 	a[w]->vect-=o[w];
		// 	// ic(a[w]->vect)
		// 	bn_delete(a[w]);
		// }
		// free(o);
		// free(a);
		bn_init_bn(e,r);
		bn_delete(r);
		bn_delete(t);
	}else{
		bn_init_int(e,0);
	}
	return 0;
}

bn* bn_div(const bn*q,const bn*e){
	bn data[2];
	memset(data,0,sizeof(data));
	a=data+0;
	d=data+1;
	bn_init_bn(a,q);
	a->sign=(bool)(a->sign);
	bn_init_bn(d,e);
	d->sign=(bool)(d->sign);
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
	return 0;
}

int bn_div_to(bn*q,bn const*w){
	bn*u=bn_div(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return 0;
}

bn* bn_mod(const bn*q,const bn*e){
	bn data[3];
	memset(data,0,sizeof(data));
	a=data+0;
	d=data+1;
	bn_init_bn(a,q);
	a->sign=(bool)(a->sign);
	bn_init_bn(d,e);
	d->sign=(bool)(d->sign);
	bn_M_div_to(a,d);
	if (q->sign*e->sign<0){
		if (a->sign){
			bn*r=data+2;
			bn_init_bn(r,e);
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
	return 0;
}

int bn_mod_to(bn*q,bn const*w){
	bn*u=bn_mod(q,w);
	bn_init_bn(q,u);
	bn_delete(u);
	return 0;
}


int bn_pow_to(bn*q,int _e){
	int64_t e=_e;
	size_t s=0;
	for (size_t w=0;w<64;++w){
		if ((1ULL<<w)&e){
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
	return 0;
}

static bn* bn_pow(bn*q,int w){
	bn*h=bn_init(q);
	bn_pow_to(h,w);
	return h;
	return 0;
}

int bn_root2_to(bn*q){
	bn data[2];
	memset(data,0,sizeof(data));
	bn*r=data+0;
	bn*p=data+1;
	// uint32_t*rv,pv;
	// uint32_t ps,rs;
	if(q->size+1>2){
		r->size=q->size+1;
		r->sign=1;
		r->vect=(uint32_t*)calloc(sizeof(uint32_t),r->size);
		// rv=r->vect;
		// rs=r->size;
		p->size=q->size+1;
		p->sign=1;
		p->vect=(uint32_t*)calloc(sizeof(uint32_t),p->size);
		p->vect[p->size-1]=1;
		// pv=p->vect;
		// ps=p->size;
	}else{
		r->size=0;
		r->sign=1;
		r->vect=0;
		// rv=(uint32_t*)&(r->vect);
		// rs=2;
		p->size=0;
		p->sign=1;
		p->vect=(uint32_t*)(uint64_t)(1LL<<32);
		// pv=(uint32_t*)&(p->vect);
		// ps=2;
	}
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
	return 0;
}

int bn_root_to(bn*q,int __e){
	if (__e==2){
		return bn_root2_to(q);
	}
	bn data[6];
	memset(data,0,sizeof(data));
	uint64_t e=__e;
	bn*_b=data+0;
	bn*_e=data+1;
	uint32_t tmp=q->size/e+1;
	if (tmp>2){
		_e->size=tmp;
		_e->sign=1;
		_e->vect=(uint32_t*)calloc(sizeof(uint32_t),_e->size);
		_e->vect[_e->size-1]=1LL<<31;
	}else{
		_e->size=0;
		_e->sign=1;
		_e->vect=(uint32_t*)(uint64_t)(1LL<<63);
	}
	bn*_c=data+2;
	bn*_d=data+3;	
	bn*_f=data+4;
	bn*_g=data+5;
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
	return 0;
}

static bn* bn_root(bn*q,int _w){
	uint64_t w=_w;
	bn*h=bn_init(q);
	bn_root_to(h,w);
	return h;
	return 0;
}

int bn_init_string_radix(bn*q,const char*e,int t){
	size_t l=strlen(e);
	uint32_t qs=l/"\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"
		[t]+1;
	if (q->size and q->vect){
		free(q->vect);
	}
	if (qs>2){
		q->size=qs;
		q->vect=(uint32_t*)calloc(sizeof(uint32_t),q->size);
	}else{
		q->size=0;
		q->vect=0;
	}
	q->sign=0;
	bn data[2];
	memset(data,0,sizeof(data));
	bn*a=data+0;
	bn*y=data+1;
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
	return 0;
}

int bn_init_string(bn*q,const char*e){
	return bn_init_string_radix(q,e,10);
	return 0;
}



const char* bn_to_string(const bn*q,int e){
	uint32_t* qv=q->size?q->vect:(uint32_t*)&(q->vect);
	uint32_t qs=q->size?q->size:2;
	while (qs and qv[qs-1]==0){
		--qs;
	}
	uint64_t _t=e;
	bn*r=bn_init(q);
	r->sign=(bool)(r->sign);
	uint32_t* rv=r->size?r->vect:(uint32_t*)&(r->vect);
	uint32_t rs=qs;
	bn data[1];
	memset(data,0,sizeof(data));
	bn*t=data+0;
	char*a=(char*)calloc(sizeof(char),2+(qs+1)*"\x00\x00\x20\x15\x10\x0e\x0d\x0c\x0b\x0b\x0a\x0a\x09\x09\x09\x09\x08\x08\x08\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07"[_t]);
	size_t s=0;
	while (r->sign){
		uint64_t b=0;
		uint64_t t=0;
		r->sign=0;
		for (size_t _w=rs;_w>0;--_w){size_t w=_w-1;
			t=rv[w];
			t+=b<<32;
			b=t%_t;
			t/=_t;
			rv[w]=t;
			if (t){
				r->sign=1;
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