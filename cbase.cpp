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
#define _o(name) (((int*)(name))-1)
#define _c(type,name) ((type)(((int*)(name))+1))
#define _si (sizeof(int))
#if 01
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
	l(q,vect(int8_t***))
	ff(w,2){
		push(q,vect(int8_t**))
		ff(e,2){
			push(q[w],vect(int8_t*))
			ff(r,2){
				push(q[w][e],vect(int8_t))
				ff(t,2){
					push(q[w][e][r],w*8+e*4+r*2+t)
				}
			}
		}
	}
	ff(w,len(q)){
		ff(e,len(q[w])){
			ff(r,len(q[w][e])){
				ff(t,len(q[w][e][r])){
					print(q[w][e][r][t])
				}
			}
		}
	}
}