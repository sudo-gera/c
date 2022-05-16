#include <bits/stdc++.h>
using namespace std;

template<uint64_t n>
struct sized{
	char a[n];
};

int a[20][20];

int main(){

	for (uint64_t w=0;w<20;++w){
		for (uint64_t e=0;e<20;++e){
			a[w][e]=rand()%10;
		}
	}

	for (uint64_t w=0;w<20;++w){
		for (uint64_t e=0;e<20;++e){
			write(a[w][e]);
		}
		putchar('\n');
	}

		putchar('\n');

	// ic(a,a+1,&a[0][0],&a[0][1],&a[1][0],&a[1][1])
	sort((sized<80>*)(a),(sized<80>*)(a+20),
		[&](const sized<80>&q,const sized<80>&e){
			int*qp=(int*)(&q);
			int*ep=(int*)(&e);
			if (memcmp(qp,ep,80)<0){
				return 1;
			}
			return 0;
		}
		);

	for (uint64_t w=0;w<20;++w){
		for (uint64_t e=0;e<20;++e){
			write(a[w][e]);
		}
		putchar('\n');
	}

}
