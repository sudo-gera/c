#include <stdio.h>
#include <stdlib.h>
// #include "bn.h"

// #define debug

// #ifdef debug
// #include <bits/stdc++.h>
// using namespace std;
// #endif

// struct bn_s{
// 	char sign;
// 	size_t size;
// 	int32_t *vect;
// };

// bn *bn_new(){
// 	bn q={0,0,0};
// 	// printf("%i %zu %zu\n",q.sign,q.size,size_t(q.vect));
// }


#define qq 0

void run(int64_t q){
	q%=1000;
#if qq
		int*a=(int*)malloc(sizeof(int)*q);
		free(a);
#else
		int a[q];
#endif
}


int main(){
	int q;
	scanf("%i",&q);
	srand(q);
#if qq
	printf("malloc\n");
#else
	printf("new\n");
#endif
	for (int64_t q=0;q<1'000'000'00;++q){
		run(q+rand());
	}
}

