#include "matrix.h"
#include <iostream>
using namespace std;

#define mod 17
#define root 2
#define ro 8

Residue<mod> roots(size_t n,size_t k=1){
	k%=n;
	size_t p=root;
	while (n<ro){
		n*=2;
		p*=p;
	}
	assert(n==ro);
	return pow(p,k,mod);
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
	size_t w=0;
	vector({_set(s[w++][0],Residue<17>(a))...});
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
	// size_t w=0;
	// vector({_set(s[w++][0],Residue<17>(a))...});
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
	// size_t w=0;
	// vector({_set(s[w++][0],Residue<17>(a))...});
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
	size_t w=0;
	vector({_set(s[w++][0],Residue<17>(a))...});
	auto z= create<sizeof...(a)>().inverted()*s;
	auto x=vector<Residue<mod>>();
	for (size_t w=0;w<sizeof...(a);++w){
		x.push_back(z[w][0]);
	}
	return x;
}


int main(){
	vector<Residue<mod>> a(8);
	for (auto&w:a){
		cin>>w;
	}
	a=vsft<8>(a);
	for (auto&w:a){
		cout<<w<<endl;
	}
	// print(isft(2,0))
}
