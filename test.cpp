#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>
#include <type_traits>
template<typename r>
struct rr{
	typedef r e;
}
#define int int64_t
#define print(q) printf("%li\n",int64_t(q));
#define prints(q) printf("%li ",int64_t(q));
#define printt(q) printf("%li\t",int64_t(q));
#define printn(q) printf("%li",int64_t(q));
#define printc(q) printf("%c",char(c));
#define _o(name) (((int*)(name))-1)
#define _c(type,name) ((type)(((int*)(name))+1))
#define _si (sizeof(int))
#if 1
//#define _dt(name) std::remove_reference<decltype(name)>::type
#define _dt(name) rr<decltype(name)>::e
#else
#define _dt(name) decltype(name)
#endif
#define vect(vtype) (_c(vtype*,calloc(1,_si)))
#define len(name) (*_o(name))
#define push(name,val) (name)=_c(_dt(name),realloc(_o(name),_si+(len(name)+1)*sizeof(*name)));(name)[len(name)++]=(val);
int scan(){int64_t q;scanf("%li",&(q));return q;}
#define ff(w,q) for(int w=0;w<(q);++w)
#define fd(w,q) for(int w=0;w>(q);--w)
#define fff(w,e,q) for(int w=(e);w<(q);++w)
#define ffd(w,e,q) for(int w=(e);w>(q);--w)
#define ffff(w,e,q,h) for(int w=(e);w<(q);w+=(h))
#define fffd(w,e,q,h) for(int w=(e);w>(q);w-=(h))
#define let auto
#define s(q,w) (q)=(w);
#define l(q,w) auto (q)=(w);

decltype(0) main(){
	l(q,vect(int*))
	ff(w,4){
		push(q,vect(int))
	}
	ff(w,len(q)){
		ff(e,7){
			push(q[w],w*7+e);
		}
	}
	ff(w,len(q)){
		ff(e,len(q[w])){
			printt(q[w][e])
		}
		printf("\n");
	}
}