#include <stdio.h>
#include <stdlib.h>
#include "bn.h"

#define debug

#ifdef debug
#include <bits/stdc++.h>
using namespace std;
#endif

struct bn_s{
	char sign;
	size_t size;
	uint32_t *vect;
};

bn *bn_new(){
	bn *q=(bn*)calloc(sizeof(bn),1);
	return q;
}

// bn *bn_init(bn const*orig){
// 	if(!orig){
// 		return nullptr;
// 	}
// 	// bn *q=(bn*)malloc(sizeof(bn));

// 	// bn *q=calloc(sizeof(bn));
// 	// return q;
// }

bn *bn_init_from_int(int64_t e){
	bn *q=(bn*)malloc(sizeof(bn)*1);
	q->vect=(uint32_t*)malloc(sizeof(uint32_t)*2);
	q->size=2;
	q->sign=e>0?1:e<0?-1:0;
	*(uint64_t*)(q->vect)=e>0?e:-e;
	return q;
}


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
		q=bn_init_from_int(orig);
	}
	template <typename T>
	friend auto &operator<<(T& q,usable f){
		for (int t=f.q->size-1;t>-1;--t){
			printf("%o",f.q->vect[t]);
		}
		return q;
	}
};


int main(){
	cout<<usable(12);
}

