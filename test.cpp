#include "bn.c"
// uint64_t pow(uint64_t q,uint64_t w,uint64_t e){
// 	uint64_t res=1;
// 	while (w){
// 		if (w%2){
// 			res*=q;
// 			res%=e;
// 		}
// 		q*=q;
// 		q%=e;
// 		w/=2;
// 	}
// 	return res;
// }

// uint64_t mod=3221225473;
// uint64_t root=13;
// uint64_t ro=1073741824;

// uint64_t rp0[65536];
// uint64_t rp1[65536];

// void prepare(){
// 	rp0[0]=1;

// 	for (size_t w=1;w<65536;++w){
// 		rp0[w]=rp0[w-1]*root%mod;
// 	}

// 	rp1[0]=1;
// 	rp1[1]=root*rp0[65536-1];
// 	rp1[1]%=mod;

// 	for (size_t w=2;w<65536;++w){
// 		rp1[w]=rp1[w-1]*rp1[1]%mod;
// 	}
// }

// uint64_t roots(uint64_t n,uint64_t k=1){
// 	assert(rp0[0]==1);
// 	k%=n;
// 	size_t p=size_t(ro/n*k);
// 	return (rp0[p%65536]*rp1[p/65536])%mod;
// }

// uint64_t* bi=0;
// uint64_t bil=0;
// uint64_t bim=0;

// uint64_t bitinv(uint64_t t,uint64_t l){
// 	while (bil<=t){
// 		uint64_t r=bil;
// 		uint64_t x=0;
// 		for (uint64_t c=0;c<32;++c){
// 			x*=2;
// 			x+=r%2;
// 			r/=2;
// 		}
// 		if (bil==bim){
// 			uint64_t*t=(uint64_t*)malloc(sizeof(uint64_t)*(bim*2+1));
// 			memcpy(t,bi,bim*sizeof(bi[0]));
// 			free(bi);
// 			bi=t;
// 			bim*=2;
// 			bim+=1;
// 		}
// 		bi[bil++]=x;
// 	}
// 	return size_t(bi[size_t(t)])>>size_t(32-l);
// }

// void prep(uint64_t*a,uint64_t n){
// 	uint64_t l=0;
// 	uint64_t o=n;
// 	while (o){
// 		o/=2;
// 		l+=1;
// 	}
// 	l-=1;
// 	for (size_t w=0;w<n;++w){
// 		size_t r=w;
// 		size_t x=(size_t)bitinv(r,l);
// 		if (w<x){
// 			uint64_t t=a[w];
// 			a[w]=a[x];
// 			a[x]=t;
// 		}
// 	}
// }

// void fftr(uint64_t*a,int inv,uint64_t b,uint64_t e){
// 	uint64_t n=e-b;
// 	uint64_t h=n/2;
// 	uint64_t _n=n;
// 	uint64_t _b=b;
// 	uint64_t _e=e;
// 	uint64_t _h=h;
// 	n=2;
// 	while (n<=_n){
// 		for (b=_b;b!=_e;b+=n){
// 			e=b+n;
// 			h=n/2;
// 			for (uint64_t k=0;k<h;k++){
// 				uint64_t a0=a[size_t(b+k)];
// 				uint64_t a1=a[size_t(b+k+h)];
// 				uint64_t t=inv<0?n-k:n+k;
// 				uint64_t r=roots(n,t);
// 				r*=a1;
// 				r%=mod;
// 				a[size_t(b+k)]=(a0+r)%mod;
// 				a[size_t(b+k+h)]=(a0+mod-r)%mod;
// 			}
// 		}
// 		n*=2;
// 	}
// }

// void fft(uint64_t*a,uint64_t n,int inv){
// 	uint64_t b=0;
// 	uint64_t e=n;
// 	prep(a,n);
// 	fftr(a,inv,b,e);
// 	if (inv==-1){
// 		for (uint64_t w=0;w<n;++w){
// 			a[size_t(w)]*=pow(n,mod-2,mod);
// 			a[size_t(w)]%=mod;
// 		}
// 	}
// }


// int bn_fft_to(bn *q , const bn*e) {
// 	uint64_t base=16;
// 	uint32_t* qv = q -> size ? q -> vect : (uint32_t*)&(q -> vect) ;
// 	uint32_t qs = q -> size ? q -> size : 2 ;
// 	const uint32_t* ev = e -> size ? e -> vect : (const uint32_t*)&(e -> vect) ;
// 	uint32_t es = e -> size ? e -> size : 2 ;
// 	while (qs and qv[qs-1] == 0) {
// 		--qs ;
// 	}
// 	while (es and ev[es-1] == 0) {
// 		--es ;
// 	}
// 	bn data[1] ;
// 	memset(data , 0 , sizeof(data)) ;
// 	bn*res = data+0 ;
// 	if (qs+es > 2) {
// 		uint8_t*qb=(uint8_t*)qv;
// 		uint8_t*eb=(uint8_t*)ev;
// 		size_t l=qs;
// 		if (es>qs){
// 			l=es;
// 		}
// 		size_t dl=1;
// 		while (dl<l){
// 			dl*=2;
// 		}
// 		l=dl*2*8;
// 		uint64_t*a=(uint64_t*)calloc(l,sizeof(uint64_t));
// 		for (size_t w=0;w<qs*4;w++){
// 			a[w*2]=qb[w]&0xF;
// 			a[w*2+1]=qb[w]>>4;
// 		}
// 		uint64_t*s=(uint64_t*)calloc(l,sizeof(uint64_t));
// 		for (size_t w=0;w<es*4;w++){
// 			s[w*2]=eb[w]&0xF;
// 			s[w*2+1]=eb[w]>>4;
// 		}
// 		fft(a,l,1);
// 		fft(s,l,1);
// 		for (size_t w=0;w<l;w++){
// 			a[w]*=s[w];
// 			a[w]%=mod;
// 		}
// 		fft(a,l,-1);
// 		for (size_t w=1;w<l;w++){
// 			a[w]+=a[w-1]/base;
// 			a[w-1]%=base;
// 		}
// 		res -> size = qs+es;
// 		res -> vect = (uint32_t*)calloc(1 , res -> size*sizeof(uint32_t)) ;
// 		res -> sign = q -> sign*e -> sign ;

// 		uint8_t*rb=(uint8_t*)(res->vect);

// 		for (size_t w=0;w<res->size*4;++w){
// 			rb[w]|=a[2*w];
// 			rb[w]|=a[2*w+1]<<4;
// 		}
// 		free(a);
// 		free(s);
// 	} else {
// 		res -> sign = q -> sign*e -> sign ;
// 		res -> size = 0 ;

// 		uint64_t*tmp_wp = (uint64_t*)&(res -> vect) ;
// 		*tmp_wp = *(uint64_t*)(qv)* *(const uint64_t*)(ev) ;
// 	}
// 	bn_swap(res , q) ;
// 	bn_del(res) ;
// 	return 0 ;
// }


#include <iostream>
#include <vector>
using namespace std;

// void mul(vector<uint64_t>&q,vector<uint64_t> e,size_t base=10){
// 	size_t l=q.size();
// 	if (q.size()<e.size()){
// 		l=e.size();
// 	}
// 	size_t dl=1;
// 	while (dl<l){
// 		dl*=2;
// 	}
// 	l=dl*2;
// 	q.resize(l);
// 	e.resize(l);
// 	fft(q.data(),l,1);
// 	fft(e.data(),l,1);
// 	for (size_t w=0;w<l;w++){
// 		q[w]*=e[w];
// 		q[w]%=mod;
// 	}
// 	fft(q.data(),l,-1);
// 	for (size_t w=1;w<l;w++){
// 		q[w]+=q[w-1]/base;
// 		q[w-1]%=base;
// 	}
// 	while (q.end()[-1]==0){
// 		q.pop_back();
// 	}
// }



int main(){
	// prepare();
	for (size_t w=0;w<40;++w){
		cerr<<(w)<<endl;
		string s;
		cin>>s;
		bn*q=bn_new();
		bn_init_string(q,s.c_str());
		// vector<uint64_t> q(s.begin(),s.end());
		cin>>s;
		bn*e=bn_new();
		bn_init_string(e,s.c_str());
		// vector<uint64_t> e(s.begin(),s.end());
		// reverse(q.begin(),q.end());
		// reverse(e.begin(),e.end());
		// for (size_t w=0;w<q.size();++w){
		// 	q[w]-='0';
		// }
		// for (size_t w=0;w<e.size();++w){
		// 	e[w]-='0';
		// }
		// mul(q,e);
		// for (size_t w=0;w<q.size();++w){
		// 	q[w]+='0';
		// }
		// reverse(q.begin(),q.end());
		// s="";
		// for (size_t w=0;w<q.size();++w){
		// 	s+=(size_t)q[w];
		// }
		bn*t=bn_init(q);
		perf();
		bn_div_to(q,e);
		perf();
		print()
		s=bn_to_string(q,10);
		// cout<<s<<endl;
	}
}
