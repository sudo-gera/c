#include <bits/stdc++.h>
using namespace std;


#define bit_get(a,s)   ((a)[(s)/8]>>(s)%8)
#define bit_set(a,s,d) {(a)[(s)/8]&=1<<(s)%8;(a)[(s)/8]+=((d)&1)<<(s)%8;}


int main(){
	auto a=new uint8_t [12500000]();
	size_t v,n;
	cin>>v>>n;
	for (size_t w=0;w<v;++w){
		size_t q;
		cin>>q;
		bit_set(a,q,1);
	}
}
