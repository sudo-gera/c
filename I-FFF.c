#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stddef.h>

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

struct array_s {
	size_t mem_size;
	size_t el_count;
	char data[0];
};

static inline size_t len(void *a) {
	if (a == NULL) {
		return 0;
	}
	return ((struct array_s *)(a))[-1].el_count;
}

static inline void del(void *a) {
	if (a != NULL) {
		free(((struct array_s *)(a)) - 1);
	}
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
	if (*vp == NULL) {
		*vp = (struct array_s *)calloc(1, sizeof(struct array_s));
		assert(*vp);
		*vp += 1;
	}
	struct array_s *a = *vp - 1;
	assert(a->data == *(char **)vp);
	if (a->mem_size < n + 1) {
		size_t cur_size = a->mem_size * el_size;
		size_t new_size;
		if (a->mem_size * 2 > n) {
			new_size = a->mem_size * 2 * el_size;
		} else {
			new_size = (n + 1) * el_size;
		}
		a = (struct array_s *)realloc(a, sizeof(struct array_s) + new_size);
		assert(a);
		memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
		a->mem_size = new_size / el_size;
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#ifdef __cplusplus
	template<typename T>
	auto resize(const T& a,uint64_t n){
		return (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)));
	}
	template<typename T,typename Y>
	auto append(const T& a,const Y& s){
		return (resize((a), len(a) + 1), (a)[len(a) - 1] = (s));
	}
	template<typename T>
	auto pop(const T& a){
		return (resize((a), len(a) - 1), (a)[len(a)]);
	}
	template<typename T>
	auto&back(const T& a){
		return ((a)[len(a)-1]);
	}
#else
	#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
	#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
	#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
	#define back(a) ((a)[len(a)-1])
#endif

static inline int64_t getint() {
	int sign = 1;
	int c;
	size_t res = 0;
	while (c = getchar_unlocked(), isspace(c))
		;
	if (c == '-') {
		sign = -1;
	} else {
		res = c - '0';
	}
	while (c = getchar_unlocked(), isdigit(c)) {
		res *= 10;
		res += c - '0';
	}
	return (int64_t)(res)*sign;
}

static inline void putint(uint64_t out) {
	if (out > (1LLU << 63) - 1) {
		putchar_unlocked('-');
		out = 1 + ~out;
	}
	char data[44];
	char *dend = data;
	while (out) {
		*++dend = (unsigned)('0') + out % 10;
		out /= 10;
	}
	if (dend == data) {
		putchar_unlocked('0');
	}
	for (; dend != data; --dend) {
		putchar_unlocked(*dend);
	}
}

static inline void print(uint64_t out) {
	putint(out);
	putchar('\n');
}

static inline void write(uint64_t out) {
	putint(out);
	putchar(' ');
}

// #define min(a,s) ((a)<(s)?(a):(s))
// #define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

uint64_t f(uint64_t x){
	return x&(x+1);
}

uint64_t g(uint64_t x){
	return x|(x+1);
}

long prefix(uint64_t x,uint64_t y,std::unordered_map<uint64_t,int>&fen){
	long s = 0;
	for (uint64_t w=x;w<unsigned(-1);w=f(w)-1){
		for (uint64_t e=y;e<unsigned(-1);e=f(e)-1){
			s += fen[(w<<32)+e];
		}
	}
	return s;
}

void add(uint64_t x,uint64_t y,std::unordered_map<uint64_t,int>&fen,int v) {
	for (uint64_t w = x; w < unsigned(-1); w = g(w)) {
		for (uint64_t e = y; e < unsigned(-1); e = g(e)) {
			fen[(w<<32)+e] += v;
		}
	}
}

int main(){
	uint64_t n=getint();
	std::vector<int> a(n*3);
	// int*a=0;
	// resize(a,n*3);
	for (uint64_t w=0;w<3*n;++w){
		a[w]=getint();
	}
	// int*unzip_x=0;
	// int*unzip_y=0;
	// resize(unzip_x,n);
	// resize(unzip_y,n);
	// for (uint64_t w=0;w<n;++w){
	// 	unzip_x[w]=a[3*w+0];
	// 	unzip_y[w]=a[3*w+1];
	// }
	// std::sort(unzip_x,unzip_x+len(unzip_x));
	// std::sort(unzip_y,unzip_y+len(unzip_y));
	// // ic(itervect(unzip_x,unzip_x+len(unzip_x)));
	// // ic(itervect(unzip_y,unzip_y+len(unzip_y)));
	// resize(unzip_x,(std::unique(unzip_x,unzip_x+len(unzip_x))-unzip_x));
	// resize(unzip_y,(std::unique(unzip_y,unzip_y+len(unzip_y))-unzip_y));
	// // ic(itervect(unzip_x,unzip_x+len(unzip_x)));
	// // ic(itervect(unzip_y,unzip_y+len(unzip_y)));
	// std::map<int,int> zip_x;
	// std::map<int,int> zip_y;
	// for (uint64_t w=0;w<len(unzip_x);++w){
	// 	zip_x[unzip_x[w]]=w;
	// }
	// for (uint64_t w=0;w<len(unzip_y);++w){
	// 	zip_y[unzip_y[w]]=w;
	// }
	// for (uint64_t w=0;w<n;++w){
	// 	a[w*3+0]=zip_x[a[w*3+0]];
	// 	a[w*3+1]=zip_y[a[w*3+1]];
	// }
	// ic(itervect(a,a+len(a)))
	// int**fen=0;
	// resize(fen,len(unzip_x)+1);
	// for (uint64_t w=0;w<len(fen);++w){
	// 	resize(fen[w],len(unzip_y)+1);
	// }
	std::unordered_map<uint64_t,int> fen;
	for (uint64_t w=0;w<n;++w){
		add(a[w*3+0],a[w*3+1],fen,a[w*3+2]);
	}
	uint64_t m=getint();
	char com[30];
	for (uint64_t w=0;w<m;++w){
		scanf("%20s",com);
		uint64_t c=getint(),v=getint();
		if (com[0]=='g'){
			// auto cp=zip_x.upper_bound(c);
			// auto vp=zip_y.upper_bound(v);
			// if (cp==zip_x.begin()){
			// 	print(0);
			// 	goto _e;
			// }else{
			// 	--cp;
			// 	c=cp->second;
			// }
			// if (vp==zip_y.begin()){
			// 	print(0);
			// 	goto _e;
			// }else{
			// 	--vp;
			// 	v=vp->second;
			// }
			print(prefix(c,v,fen));
			_e:
			{}
		}else{
			c-=1;
			add(a[3*c+0],a[3*c+1],fen,v-a[3*c+2]);
			a[3*c+2]=v;
		}
	}
}
