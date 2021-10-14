#include <stdio.h>
#include <stdlib.h>
#include "bn.h"

struct bn_s{
	int8_t sign;
	size_t size;
	uint32_t *vect;
};

bn *bn_new(){
	bn *q=(bn*)calloc(sizeof(bn),1);
	return q;
}

bn *bn_init(bn const*orig){
	if(!orig){
		return nullptr;
	}
	bn *q=(bn*)malloc(sizeof(bn));
	*q=*orig;
	q->vect=(uint32_t*)malloc(q->size*sizeof(uint32_t));
	for (size_t w=0;w<q->size;++w){
		q->vect[w]=orig->vect[w];
	}
	return q;
}

int bn_init_int(bn *q,int64_t e){
	if (!q){
		return BN_NULL_OBJECT;
	}
	if (q->vect){
		free(q->vect);
	}
	q->vect=(uint32_t*)malloc(sizeof(uint32_t)*2);
	if (!q->vect){
		return BN_NO_MEMORY;
	}
	q->size=2;
	q->sign=e>0?1:e<0?-1:0;
	*(uint64_t*)(q->vect)=e>0?e:-e;
	if (!q->vect[1]){
		q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);
		q->size=1;
		if (!q->vect[0]){
			q->vect=(uint32_t*)realloc(q->vect,sizeof(uint32_t)*1);
			q->size=0;
		}
	}
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

#if __has_include("/Users/gera/c/header.hpp") && __cplusplus
#include "header.hpp"
using namespace std;


class usable{
public:
	bn *q;
	usable(){
		q=bn_new();
	}
	usable(const usable& orig){
		q=bn_init(orig.q);
	}
	usable(const int64_t orig){
		q=bn_new();
		bn_init_int(q,orig);
	}
	int operator=(int64_t orig){
		return bn_init_int(q,orig);
	}
	template <typename T>
	friend auto &operator<<(T& q,usable f){
		printf("\x1b[92m%c\x1b[0m",1==f.q->sign?'+':-1==f.q->sign?'-':'0');
		int c=0;
		for (int t=f.q->size-1;t>-1;--t){
			if (c%2){
				printf("\x1b[92m");
			}
			printf("%0:8x",f.q->vect[t]);
			if (c%2){
				printf("\x1b[0m");
			}
			++c;
		}
		return q;
	}
	~usable(){
		bn_delete(q);
	}
};


int main(){
	auto t=usable(4294967296);
	auto r=usable(-2147483648);
	auto e=usable(0);
	// print(vector(t.q->vect,t.q->vect+t.q->size));
	print(t,r,e);
}

#endif