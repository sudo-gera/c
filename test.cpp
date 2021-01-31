#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>
#include <type_traits>
#define int int64_t
#define print(q) printf("%li\n",(q));
template<typename t>
#define _o(name) (((int*)(name))-1)
#define _c(type,name) ((type)(((int*)(name))+1))
#define _si (sizeof(int))
#define vect(vtype) (_c(vtype*,calloc(1,_si)))
#define len(name) (*_o(name))
#define push(name,val) (name)=_c(std::remove_reference<decltype(name)>::type,realloc(_o(name),_si+(len(name)+1)*sizeof(*name)));(name)[len(name)++]=(val);
int scan(){int64_t q;scanf("%li",&(q));return q;}
#define ff(w,q) for(int w=0;w<(q);++w)
#define let auto

decltype(0) main(){
	let q=vect(int*);
	ff(w,5){
		push(q,vect(int));
	}
	ff(w,5){
		ff(e,7){
			push(q[w],0);
		}
	}
	ff(w,5){
		ff(e,7){
			q[w][e]=w*7+e;
		}
	}
	ff(w,5){
		ff(e,7){
			print(q[w][e]);
		}
		print(9999999)
	}
}