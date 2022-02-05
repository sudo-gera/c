#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define ____(x) #x
#define ___(x) ____(x)
#pragma message(___(__cplusplus))


#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>
template<typename T>
void radixsort(T*_A,uint32_t n){
	auto A=reinterpret_cast<typename std::make_unsigned<typename std::remove_reference<decltype(_A[0])>::type>::type*>(_A);
	if (std::is_signed<typename std::remove_reference<decltype(_A[0])>::type>::value){
		for (size_t w=0;w<n;++w){
			A[w]^=static_cast<typename std::remove_reference<decltype(A[0])>::type>(1)<<(8*sizeof(_A[0])-1);
		}
	}
	auto C=reinterpret_cast<uint32_t*>(malloc(sizeof(uint32_t)*65536));
	auto B=reinterpret_cast<decltype(A)>(malloc(sizeof(decltype(A[0]))*n));
	for (size_t w=0;w<sizeof(A[0])/2;++w){
		memset(C,0,65536*sizeof(C[0]));
		for(size_t i=0;i<n;++i){
			++C[ reinterpret_cast<uint16_t*>(A+i)[w] ];
		}
		for (size_t j=1;j<65536;++j){
			C[j] += C[j - 1];
		}
		--A;
		for (size_t i=n;i>0;--i){
			B[ --C[ reinterpret_cast<uint16_t*>(A+i)[w] ] ] = A[i];
		}
		++A;
		auto t=A;
		A=B;
		B=t;
	}
	if (sizeof(A[0])/2%2){
		auto t=A;
		A=B;
		B=t;
		for (size_t w=0;w<n;++w){
			A[w]=B[w];
		}
	}
	free(C);
	free(B);
	if (std::is_signed<typename std::remove_reference<decltype(_A[0])>::type>::value){
		for (size_t w=0;w<n;++w){
			A[w]^=static_cast<typename std::remove_reference<decltype(A[0])>::type>(1)<<(8*sizeof(_A[0])-1);
		}
	}
}

int main(){
	size_t n,m;
	scanf("%zu%zu",&n,&m);
	int*v=new int[n];
	for (size_t w=0;w<n;++w){
		scanf("%i",v+w);
	}
	radixsort(v,n);
	for (size_t w=0;w<m;++w){
		size_t z=0,x=0;
		int p;
		scanf("%i",&p);
		while (z<n and x<n){
			if (v[z]+v[n-1-x]<p){
				++z;
			}else
			if (v[z]+v[n-1-x]>p){
				++x;
			}else
			if (v[z]+v[n-1-x]==p){
				if (z==n-1-x){
					++z;
					if (z<n){
						if (v[z]+v[n-1-x]==p){
							break;
						}
					}
					--z;
					++x;
					if (x<n){
						if (v[z]+v[n-1-x]==p){
							break;
						}
					}
					++z;
				}else{
					break;
				}
			}
		}
		if (z<n and x<n and v[z]+v[n-1-x]==p){
			printf("%i %i\n",v[z]<v[n-1-x]?v[z]:v[n-1-x],v[z]>v[n-1-x]?v[z]:v[n-1-x]);
		}else{
			printf("Not found\n");
		}
	}
	delete[] v;
}
