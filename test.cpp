<<<<<<< HEAD
//#pragma GCC optimize("Ofast")
=======
<<<<<<< HEAD
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char ** argv){
	vector<string> arg(argv,argv+argc);
	for(auto j:arg){
		cout<<j<<'\n';
	}
}
=======
#pragma GCC optimize("Ofast")
>>>>>>> bb62dd0d84c17609fa6c851f0765d2e593b377cb
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define int int64_t
#define print(q) printf("%li\n",int64_t(q));
#define prints(q) printf("%li ",int64_t(q));
#define printt(q) printf("%li\t",int64_t(q));
#define printn(q) printf("%li",int64_t(q));
#define printc(q) printf("%c",char(c));
template<typename r>
struct rr{
	typedef r e;
};
template<typename r>
struct rr<r&>{
	typedef r e;
};
template<typename r>
struct rr<r&&>{
	typedef r e;
};
#define _o(name) (((int*)(name))-2)
#define _c(type,name) ((type)(((int*)(name))+2))
#define _si (sizeof(int))
#if 01
#define _dt(name) rr<decltype(name)>::e
#else
#endif
#define vect(vtype) (_c(vtype*,calloc(1,2*_si)))
#define len(name) (_o(name)[0])
#define _len(name) (_o(name)[1])
#define push(name,val) if(len(name)==_len(name)){(name)=_c(_dt(name),realloc(_o(name),2*_si+(_len(name)*2)*sizeof(*name)));_len(name)=_len(name)?_len(name)<<1:1;}(name)[len(name)++]=(val);
#define del(name) free(_o(name));
int scan(){int64_t q;scanf("%li",&(q));return q;}
#define ff(w,q) for(int w=0;w<(q);++w)
#define fd(w,q) for(int w=0;w>(q);--w)
#define fff(w,e,q) for(int w=(e);w<(q);++w)
#define ffd(w,e,q) for(int w=(e);w>(q);--w)
#define ffff(w,e,q,h) for(int w=(e);w<(q);w+=(h))
#define fffd(w,e,q,h) for(int w=(e);w>(q);w-=(h))
#define let auto
#define s(q,w) (q)=(w);
#define as(q,w) (q)+=(w);
#define ss(q,w) (q)-=(w);
#define ms(q,w) (q)*=(w);
#define ds(q,w) (q)/=(w);
#define ps(q,w) (q)%=(w);
#define l(q,w) auto (q)=(w);
#define i(q,w) int (q)=(w);

decltype(0) main(decltype(0) argc,char**argv){
	if (argc==2){
		l(q,std::vector<int>());
		ff(w,100000000){
			q.push_back(w);
		}
		i(c,0)
		ff(w,q.size()){
			as(c,q[w])
		}
		print(c)
	}else{
		l(q,vect(int));
		ff(w,100000000){
			push(q,w);
		}
		i(c,0)
		ff(w,len(q)){
			as(c,q[w])
		}
		print(c)
	}
<<<<<<< HEAD
}
=======
	del(q)
}
>>>>>>> ecf269ba7419be6c5a059ff4b5966bbc048770f6
>>>>>>> bb62dd0d84c17609fa6c851f0765d2e593b377cb
