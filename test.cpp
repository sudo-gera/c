#include <bits/stdc++.h>
using namespace std;

template <size_t N,size_t START,size_t COUNT>
struct N_not_div_all{
	static const bool value=N_not_div_all<N,START,COUNT/2>::value and N_not_div_all<N,START+COUNT/2,COUNT-COUNT/2>::value;
};

template <size_t N,size_t START>
struct N_not_div_all<N,START,1>{
	static const bool value=N%START;
};

template <size_t N,size_t START>
struct N_not_div_all<N,START,0>{
	static const bool value=true;
};

template <size_t N,size_t BIT>
struct root_s{
	static const size_t v1=root_s<N,BIT+1>::value;
	static const size_t v2=v1+(1ULL<<BIT);
	static const size_t value=v2*v2>N?v1:v2;
};

template <size_t N>
struct root_s<N,32>{
	static const size_t value=0;
};

template <size_t N>
const size_t root=root_s<N,0>::value;

template <size_t N>
const bool is_prime=N_not_div_all<N,2,root<N>-1>::value;

template<>
const bool is_prime<0> = 0;

template<>
const bool is_prime<1> = 0;


// template<uint64_t n>
// struct sized{
// 	char a[n];
// };

// int a[20][20];

int main(){

	// for (uint64_t w=0;w<20;++w){
	// 	for (uint64_t e=0;e<20;++e){
	// 		a[w][e]=rand()%10;
	// 	}
	// }

	// for (uint64_t w=0;w<20;++w){
	// 	for (uint64_t e=0;e<20;++e){
	// 		write(a[w][e]);
	// 	}
	// 	putchar('\n');
	// }

	// 	putchar('\n');

	// using tmp=int[20];

	// ic(a,a+1,&a[0][0],&a[0][1],&a[1][0],&a[1][1])
	// sort((tmp*)(a),(tmp*)(a+20),
	// 	[&](const tmp&q,const tmp&e){
	// 		int*qp=(int*)(&q);
	// 		int*ep=(int*)(&e);
	// 		if (memcmp(qp,ep,80)<0){
	// 			return 1;
	// 		}
	// 		return 0;
	// 	}
	// 	);

	// for (uint64_t w=0;w<20;++w){
	// 	for (uint64_t e=0;e<20;++e){
	// 		write(a[w][e]);
	// 	}
	// 	putchar('\n');
	// }

	// cout<<is_prime<1000000000039><<endl;
	set<int> a;
	auto p=a.begin();
	next(p,20);

}
