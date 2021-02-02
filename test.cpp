#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>
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
#define int int64_t
#define print(q) printf("%li\n",int64_t(q));
#define prints(q) printf("%li ",int64_t(q));
#define printt(q) printf("%li\t",int64_t(q));
#define printn(q) printf("%li",int64_t(q));
#define printc(q) printf("%c",char(c));
#define _o(name) (((int*)(name))-2)
#define _c(type,name) ((type)(((int*)(name))+2))
#define _si (sizeof(int))
#if 01
#define _dt(name) rr<decltype(name)>::e
#else
#define _dt(name) decltype(name)
#endif
#define vect(vtype) (_c(vtype*,calloc(1,2*_si)))
#define len(name) (_o(name)[0])
#define _len(name) (_o(name)[1])
template<typename y>
y lp(y j){
	print(int64_t(j))
	return j;
}
#define push(name,val) if(len(name)==_len(name)){(name)=_c(_dt(name),realloc(_o(name),lp(2*_si+(_len(name)*2)*sizeof(*name))));_len(name)=_len(name)?_len(name)<<1:1;}(name)[len(name)++]=(val);
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

decltype(0) main(){
	l(q,vect(int))
	ff(w,100000000){
		push(q,w)
	}
	l(c,0)
	ff(w,len(q)){
		as(c,w)
	}
	print(c)
}