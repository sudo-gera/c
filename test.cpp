#include "matrix.h"
#include <iostream>
using namespace std;

// #define uint64_t csint<64>

#define mod 17
#define root 2
#define ro 8
// #define mod 3221225473
// #define root uint64_t(125)
// #define ro uint64_t(1073741824)
// #define mod 3221225473
// #define root uint64_t(13)
// #define ro uint64_t(1073741824)

Residue<mod> roots(uint64_t n,uint64_t k=1){
	k%=n;
	uint64_t p=root;
	while (n<ro){
		n*=2;
		p*=p;
		p%=mod;
	}
	assert(n==ro);
	return pow(p,k,uint64_t(mod));
}

template<size_t N>
auto create(){
	Matrix<N,N,Residue<mod>> a;
	for (size_t w=0;w<N;w++){
		for(size_t h=0;h<N;h++){
			a[w][h]=roots(N,w*h);
		}
	}
	return a;
}


template<typename T1>
auto&_set(T1&q,const T1&w){
	q=w;
	return q;
}

template<typename...T>
auto sft(T...a){
	Matrix<sizeof...(a),1,Residue<mod>>s;
	uint64_t w=0;
	vector({_set(s[w++][0],Residue<mod>(a))...});
	auto z= create<sizeof...(a)>()*s;
	auto x=vector<Residue<mod>>();
	for (size_t w=0;w<sizeof...(a);++w){
		x.push_back(z[w][0]);
	}
	return x;
}

template<size_t N>
auto vsft(vector<Residue<mod>> a){
	Matrix<N,1,Residue<mod>>s;
	for (size_t w=0;w<N;++w){
		s[w][0]=a[w];
	}
	auto z= create<N>()*s;
	auto x=vector<Residue<mod>>();
	for (size_t w=0;w<N;++w){
		x.push_back(z[w][0]);
	}
	return x;
}

template<size_t N>
auto visft(vector<Residue<mod>> a){
	Matrix<N,1,Residue<mod>>s;
	for (size_t w=0;w<N;++w){
		s[w][0]=a[w];
	}
	auto z= create<N>().inverted()*s;
	auto x=vector<Residue<mod>>();
	for (size_t w=0;w<N;++w){
		x.push_back(z[w][0]);
	}
	return x;
}

template<typename...T>
auto isft(T...a){
	Matrix<sizeof...(a),1,Residue<mod>>s;
	uint64_t w=0;
	vector({_set(s[w++][0],Residue<mod>(a))...});
	auto z= create<sizeof...(a)>().inverted()*s;
	auto x=vector<Residue<mod>>();
	for (size_t w=0;w<sizeof...(a);++w){
		x.push_back(z[w][0]);
	}
	return x;
}

#define MAX_ 8

int main(){
	// vector<Residue<mod>> a(MAX_);
	// for (auto&w:a){
	// 	cin>>w;
	// }
	// auto s=vsft<MAX_>(a);
	// for (auto&w:s){
	// 	cout<<w<<' ';
	// }
	// cout<<endl;
	// s=visft<MAX_>(a);
	// for (auto&w:s){
	// 	cout<<w<<' ';
	// }
	// cout<<endl;
	size_t n;
	cin>>n;
	size_t oq=n;
	vector<Residue<mod>> q;
	while (n){
		q.push_back(n%10);
		n/=10;
	}
	cin>>n;
	size_t oe=n;
	vector<Residue<mod>> e;
	while (n){
		e.push_back(n%10);
		n/=10;
	}
	q.resize(8);
	e.resize(8);
	print(q,e,oq,oe)
	q=vsft<MAX_>(q);
	e=vsft<MAX_>(e);
	print(q,e)
	for (auto w : range(len(q))){
		q[w]*=e[w];
	}
	print(q)
	q=visft<MAX_>(q);
	print(q)
	reverse(q.begin(), q.end());
	size_t r=0;
	for (auto w : q){
		r*=10;
		r+=size_t(w);
	}
	print(r,oq*oe)
	assert (r==oq*oe);
}
