#if __has_include("d")
#include "d"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

void fast_sort(unsigned* A,unsigned* E){
	uint32_t n=E-A;
	#define size 1
	#if size==1
	typedef uint8_t shu;
	uint32_t C0[256];
	uint32_t C1[256];
	uint32_t C2[256];
	uint32_t C3[256];
	#else
	typedef uint16_t shu;
	uint32_t C0[65536];
	uint32_t C1[65536];
	#endif
	unsigned* B=(unsigned*)(malloc(sizeof(unsigned)*n));
	memset(C0,0,sizeof(C0));
	memset(C1,0,sizeof(C1));
	#if size==1
	memset(C2,0,sizeof(C2));
	memset(C3,0,sizeof(C3));
	#endif
	--A;
	for(unsigned* Ai=A+n;Ai!=A;--Ai){
		++C0[ ((shu*)(Ai))[0] ];
		++C1[ ((shu*)(Ai))[1] ];
		#if size==1
		++C2[ ((shu*)(Ai))[2] ];
		++C3[ ((shu*)(Ai))[3] ];
		#endif
	}
	for (unsigned j=1;j<sizeof(C0)/sizeof(C0[0]);++j){
		C0[j] += C0[j-1];
		C1[j] += C1[j-1];
		#if size==1
		C2[j] += C2[j-1];
		C3[j] += C3[j-1];
		#endif
	}
	for (unsigned* Ai=A+n;Ai!=A;--Ai){
		B[ --C0[ ((shu*)(Ai))[0] ] ] = *Ai;
	}
	++A;
	--B;
	for (unsigned* Bi=B+n;Bi!=B;--Bi){
		A[ --C1[ ((shu*)(Bi))[1] ] ] = *Bi;
	}
	++B;
	#if size==1
	--A;
	for (unsigned* Ai=A+n;Ai!=A;--Ai){
		B[ --C2[ ((shu*)(Ai))[2] ] ] = *Ai;
	}
	++A;
	--B;
	for (unsigned* Bi=B+n;Bi!=B;--Bi){
		A[ --C3[ ((shu*)(Bi))[3] ] ] = *Bi;
	}
	++B;
	#endif
	free(B);
	#undef size
}


#ifdef HOME
int main(){
	int n=scan(int);
	vector<unsigned> a(n);
	for (auto&w:a){
		cin>>w;
	}
	auto s=a;
	fast_sort(a.data(),a.data()+a.size());
	sort(s.begin(),s.end());
	if (a!=s){
		print(a)
		print(s)
	}
	assert(a==s);
}
#endif
