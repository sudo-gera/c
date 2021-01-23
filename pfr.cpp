#include <bits/stdc++.h>
#define int int64_t
int scan(){int q;scanf("%li",&(q));return q;}
#define printn(q) printf("%li\n",(q));
#define print(q) printf("%li",(q));
#define prints(q) printf("%li ",(q));
#define ffff(w,a,o,e) for(int w=a;w<o;w+=e)
#define fffb(w,a,o,e) for(int w=a;w>o;w+=e)
#define fff(w,a,o) for(int w=a;w<o;w++)
#define ff(w,o) for(int w=0;w<o;w++)
#define vect(t,n) auto n=(t*)malloc(0);int n##_size=0;
#define push(n,v) n=(decltype(n))realloc(n,(n##_size+1)*sizeof(decltype(*n)));n[n##_size++]=v;

#define 

decltype(0) main(){
	int n=scan(),m=scan();
	vect(int,a);
	vect(int,b);
	vect(int,x);
	vect(int,c);
	ff(w,n){
		push(a,scan());
		push(b,scan());
	}
	ff(w,m){
		push(x,scan());
		push(c,0);
	}
	vect(int,e);
	ff(w,a_size){
		push(e,(a[w]<<32)+(1<<30));
	}
	ff(w,b_size){
		push(e,(b[w]<<32)+(3<<30));
	}
	ff(w,x_size){
		push(e,(x[w]<<32)+w+(2<<30));
	}
	std::sort(e,e+e_size);
	int o=0;
	ff(w,e_size){
		if ((e[w]&((1l<<32)-(1l<<30)))==1){
			o++;
		}
		if ((e[w]&((1l<<32)-(1l<<30)))==3){
			o--;
		}
		if ((e[w]&((1l<<32)-(1l<<30)))==2){
			c[(e[w]&((1l<<30)-(1l<<0)))]=o;
		}
	}
	ff(w,c_size){
		printn(c[w]);
	}
}