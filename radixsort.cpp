#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

template <int n>
struct sized_uns{};
template <>
struct sized_uns<1>{using uns=__uint8_t;using shu=uint8_t;};
template <>
struct sized_uns<2>{using uns=__uint16_t;using shu=uint16_t;};
template <>
struct sized_uns<4>{using uns=__uint32_t;using shu=uint16_t;};
template <>
struct sized_uns<8>{using uns=__uint64_t;using shu=uint16_t;};
template <>
struct sized_uns<16>{using uns=__uint128_t;using shu=uint16_t;};

template<typename T>
void radixsort(T A,uint32_t n){
	using uns=typename sized_uns<sizeof(A[0])>::uns;
	using shu=typename sized_uns<sizeof(A[0])>::shu;
	using val=typename std::remove_reference<decltype(A[0])>::type;
	const uns pow=static_cast<uns>(1)<<(8*sizeof(A[0])-1);
	if (std::is_signed<val>::value){
		for (size_t w=0;w<n;++w){
			if (std::is_floating_point<val>::value and 
				reinterpret_cast<uns&>(A[w])&pow){
					reinterpret_cast<uns&>(A[w])=~reinterpret_cast<uns&>(A[w]);
			}else{
				reinterpret_cast<uns&>(A[w])^=static_cast<uns>(1)<<(8*sizeof(A[0])-1);
			}
		}
	}
	const int k=1<<(sizeof(shu)*8);
	auto C=reinterpret_cast<uint32_t*>(malloc(sizeof(uint32_t)*k));
	auto B=reinterpret_cast<uns*>(malloc(sizeof(uns)*n));
	for (size_t w=0;w<sizeof(uns)/sizeof(shu);++w){
		memset(C,0,k*sizeof(C[0]));
		for(size_t i=0;i<n;++i){
			++C[ reinterpret_cast<shu*>(reinterpret_cast<uns*>(&(A[i])))[w] ];
		}
		for (size_t j=1;j<k;++j){
			C[j] += C[j - 1];
		}
		--A;
		for (size_t i=n;i>0;--i){
			B[ --C[ reinterpret_cast<shu*>(reinterpret_cast<uns*>(&(A[i]))) [w] ] ] = reinterpret_cast<uns&>(A[i]);
		}
		++A;
		++w;
		if (sizeof(uns)<4){
			for (size_t w=0;w<n;++w){
				A[w]=B[w];
			}
			break;
		}
		memset(C,0,k*sizeof(C[0]));
		for(size_t i=0;i<n;++i){
			++C[ reinterpret_cast<shu*>(B+i)[w] ];
		}
		for (size_t j=1;j<k;++j){
			C[j] += C[j - 1];
		}
		--B;
		for (size_t i=n;i>0;--i){
			A[ --C[ reinterpret_cast<shu*>(B+i)[w] ] ] = reinterpret_cast<decltype(A[0])>(B[i]);
		}
		++B;
	}
	free(C);
	free(B);
	if (std::is_signed<val>::value){
		for (size_t w=0;w<n;++w){
			if (std::is_floating_point<val>::value and 
				~reinterpret_cast<uns&>(A[w])&pow){
					reinterpret_cast<uns&>(A[w])=~reinterpret_cast<uns&>(A[w]);
			}else{
				reinterpret_cast<uns&>(A[w])^=static_cast<uns>(1)<<(8*sizeof(A[0])-1);
			}
		}
	}
}
