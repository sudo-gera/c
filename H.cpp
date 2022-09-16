#include <bits/stdc++.h>
using namespace std;

long*tree_acess(uint64_t b,uint64_t e,long*t,uint64_t p){
	assert(b<e and e<=p);
	return t+(p+b)/(e-b);
}

long tree_init(uint64_t b,uint64_t e,long*s,long*t,uint64_t p,long (*f)(long,long)){
	assert(b<e and e<=p);
	if (b+1==e){
		return tree_acess(b,e,t,p)[0]=s[b];
	}
	uint64_t c=(b+e)/2;
	long z=tree_init(b,c,s,t,p,f);
	long x=tree_init(c,e,s,t,p,f);
	z=f(z,x);
	tree_acess(b,e,t,p)[0]=z;
	return z;
}

long tree_get(uint64_t ub,uint64_t ue,uint64_t b,uint64_t e,long*t,uint64_t p,long (*f)(long,long)){
	if (ub==ue){
		return 0;
	}
	if (ub==b and ue==e){
		return tree_acess(b,e,t,p)[0];
	}
	uint64_t c=(b+e)/2;
	if (b<=ub and ue<=c){
		return tree_get(ub,ue,b,c,t,p,f);
	}
	if (c<=ub and ue<=e){
		return tree_get(ub,ue,c,e,t,p,f);
	}
	long z=tree_get(ub,c,b,c,t,p,f);
	long x=tree_get(c,ue,c,e,t,p,f);
	return f(z,x);
}

long tree_get(uint64_t ub,uint64_t ue,uint64_t b,uint64_t e,long*t,uint64_t p,long (*f)(long,long)){
	if (ub==ue){
		return 0;
	}
	if (ub==b and ue==e){
		return tree_acess(b,e,t,p)[0];
	}
	uint64_t c=(b+e)/2;
	if (b<=ub and ue<=c){
		return tree_get(ub,ue,b,c,t,p,f);
	}
	if (c<=ub and ue<=e){
		return tree_get(ub,ue,c,e,t,p,f);
	}
	long z=tree_get(ub,c,b,c,t,p,f);
	long x=tree_get(c,ue,c,e,t,p,f);
	return f(z,x);
}

// void tree_set(uint64_t u,long v,uint64_t b,uint64_t e,long*t,uint64_t p,long (*f)(long,long)){
// 	assert(b<=u and u<e and e<=p);
// 	long z=tree_get(b,u,0,p,t,p,f);
// 	long x=tree_get(u+1,e,0,p,t,p,f);
// 	long*l=tree_acess(b,e,t,p);
// 	l[0]=f(f(z,v),x);
// 	uint64_t c=(b+e)/2;
// 	if (b+1==e){
// 		return;
// 	}
// 	if (u<c){
// 		tree_set(u,v,b,c,t,p,f);
// 	}else{
// 		tree_set(u,v,c,e,t,p,f);
// 	}
// }

// long _sum(long q,long e){
// 	return q+e;
// }

long _xor(long q,long e){
	return q^e;
}

long _sum(long q,long e){
	return max(q,e);
}

int main(){
	uint64_t n=getint();
	uint64_t m=getint();
	uint64_t p=-1;
	p^=p>>1;
	while(p>=n*2+2){
		p>>=1;
	}
	assert(p>=n);
	long*v=0;
	resize(v,p);
	for (uint64_t w=0;w<n;++w){
		v[w]=getint();
	}
	long*sums=0;
	resize(sums,p*2);
	long*xors=0;
	resize(xors,p*2);
	tree_init(0,p,v,sums,p,_sum);
	tree_init(0,p,v,xors,p,_xor);
	for (uint64_t w=0;w<m;++w){
		// for (uint64_t r=0;r<n;++r){
		// 	write(tree_get(r,r+1,0,p,sums,p,_sum));
		// }
		// putchar('\n');
		// for (uint64_t r=0;r<n;++r){
		// 	write(tree_get(r,r+1,0,p,xors,p,_xor));
		// }
		// putchar('\n');
		uint64_t q=getint();
		if (q==1){
			uint64_t l=getint(),r=getint()+1;
			// ic(q,l,r)
			print(tree_get(l,r,0,p,xors,p,_xor));
		}
		if (q==2){
			uint64_t l=getint(),r=getint()+1;
			// ic(q,l,r)
			print(tree_get(l,r,0,p,sums,p,_sum));
			// print(8);
		}
		if (q==3){
			uint64_t l=getint();
			long v=getint();
			// ic(q,l,v)
			// long vs=tree_get(l,l+1,0,p,sums,p,_sum);
			// vs=v-vs;
			// tree_add(l,vs,0,p,sums,p,_sum);
			// long vx=tree_get(l,l+1,0,p,xors,p,_xor);
			// vx=v^vx;
			// tree_add(l,vx,0,p,xors,p,_xor);
			tree_set(l,v,0,p,sums,p,_sum);
			tree_set(l,v,0,p,xors,p,_xor);
		}
	}
}


int main(){


}
