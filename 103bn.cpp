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
	int32_t *vect;
};

bn *bn_new(){
	bn *q=(bn*)calloc(sizeof(bn));
	return q;
}

bn *bn_init(bn const*orig){
	if(!orig){
		return nullptr;
	}
	bn *q=(bn*)malloc(sizeof(bn));

	// bn *q=calloc(sizeof(bn));
	// return q;
}


int main(){
	bn *q = bn_new();
}

