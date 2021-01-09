<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#define int int64_t
#define scan(q) scanf("%li",&(q));
#define print(q) printf("%li\n",q);
#define vect(type,name) auto name=(type*)calloc(sizeof(type),0);int name##_size=0;
#define push(name,q) name=(decltype(name))realloc(name,(name##_size+1)*sizeof(*name));name[name##_size++]=q;
#define ff(w,q) for(int w=0;w<q;w++)

decltype(0) main(){
	vect(int,q);
	ff(w,4){
		int h;
		scan(h);
		push(q,h);
	}
	ff(w,q_size){
		print(q[w]);
	}
}
=======
#include <iostream>
#define int int64_t
struct a{
 char d[7];
};
decltype(0) main(){
 a* d=0;
 std::cout<<(int)(d)<<'\n';
 d++;
 std::cout<<(int)(d)<<'\n';
 d+=3;
 std::cout<<(int)(d)<<'\n';
}
>>>>>>> 8b44a6a500e903736a3fa73be40feb3017180c27
