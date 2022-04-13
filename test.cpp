// #include "matrix.h"
#include <iostream>
#include <vector>
using namespace std;

#define uint64_t csuns<64>
#define int64_t csint<64>

template<typename T>
T pow(T q,T w,T e){
	T res=1;
	while (w){
		if (w%2){
			res*=q;
			res%=e;
		}
		q*=q;
		q%=e;
		w/=2;
	}
	return res;
}

uint64_t mod=3221225473;
uint64_t root=13;
uint64_t ro=1073741824;

uint64_t rp0[65536];
uint64_t rp1[65536];

void prepare(){
	rp0[0]=1;

	for (size_t w=1;w<65536;++w){
		rp0[w]=rp0[w-1]*root%mod;
	}

	rp1[0]=1;
	rp1[1]=root*rp0[65536-1];

	for (size_t w=2;w<65536;++w){
		rp1[w]=rp1[w-1]*rp1[1]%mod;
	}
}

uint64_t roots(uint64_t n,uint64_t k=1){
	k%=n;
	size_t p=size_t(ro/n*k);
	return (rp0[p%65536]*rp1[p/65536])%mod;
}

vector<uint64_t> bi;

uint64_t bitinv(uint64_t t,uint64_t l){
	while (bi.size()<=t){
		uint64_t r=bi.size();
		uint64_t x=0;
		for (uint64_t c=0;c<32;++c){
			x*=2;
			x+=r%2;
			r/=2;
		}
		bi.push_back(x);
	}
	return size_t(bi[size_t(t)])>>size_t(32-l);
}

void prep(vector<uint64_t>&a){
	uint64_t l=0;
	uint64_t o=a.size();
	while (o){
		o/=2;
		l+=1;
	}
	l-=1;
	for (size_t w=0;w<a.size();++w){
		size_t r=w;
		size_t x=(size_t)bitinv(r,l);
		if (w<x){
			uint64_t t=a[w];
			a[w]=a[x];
			a[x]=t;
		}
	}
}

void fftr(vector<uint64_t>&a,int inv,uint64_t b,uint64_t e){
	uint64_t n=e-b;
	uint64_t h=n/2;
	uint64_t _n=n;
	uint64_t _b=b;
	uint64_t _e=e;
	uint64_t _h=h;
	n=2;
	while (n<=_n){
			// ic(a)
		for (b=_b;b!=_e;b+=n){
			// ic(a)
			e=b+n;
			h=n/2;
			for (uint64_t k=0;k<h;k++){
				uint64_t a0=a[size_t(b+k)];
				uint64_t a1=a[size_t(b+k+h)];
				uint64_t t=inv<0?n-k:n+k;
				uint64_t r=roots(n,t);
				ic(n,t,r)
				r*=a1;
				r%=mod;
				a[size_t(b+k)]=(a0+r)%mod;
				a[size_t(b+k+h)]=(a0+mod-r)%mod;
			}
		}
		n*=2;
	}
}

void fft(vector<uint64_t>&a,int inv){
	uint64_t b=0;
	uint64_t e=a.size();
	uint64_t n=e-b;
	prep(a);
	fftr(a,inv,b,e);
	if (inv==-1){
		for (uint64_t w=0;w<n;++w){
			a[size_t(w)]*=pow(n,mod-2,mod);
			a[size_t(w)]%=mod;
		}
	}
}

void mul(vector<uint64_t>&q,vector<uint64_t> e){
	size_t l=q.size();
	if (q.size()<e.size()){
		l=e.size();
	}
	size_t dl=1;
	while (dl<l){
		dl*=2;
	}
	l=dl*2;
	q.resize(l);
	e.resize(l);
	fft(q,1);
	fft(e,1);
	for (size_t w=0;w<e.size();w++){
		q[w]*=e[w];
		q[w]%=mod;
	}
	fft(q,-1);
}

int main(){
	string s;
	cin>>s;
	vector<uint64_t> q(s.begin(),s.end());
	cin>>s;
	vector<uint64_t> e(s.begin(),s.end());
	reverse(q.begin(),q.end());
	reverse(e.begin(),e.end());
	for (size_t w=0;w<q.size();++w){
		q[w]-='0';
	}
	for (size_t w=0;w<e.size();++w){
		e[w]-='0';
	}
	mul(q,e);
	for (size_t w=0;w<q.size();++w){
		q[w]+='0';
	}
	reverse(q.begin(),q.end());
	s="";
	for (size_t w=0;w<q.size();++w){
		s+='0'+size_t(q[w]);
	}
	cout<<s<<endl;
}
