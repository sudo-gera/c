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
		memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
		a->mem_size = new_size / el_size;
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#define resize(a, n) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)))
#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
// #define back(a) ((a)[len(a)-1])

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

template<typename T>
struct H;

template<>
struct H<const char*>{
	uint64_t operator()(const char*p)const{
		uint64_t r=0;
		while (*p){
			r*=257;
			r+=*p;
			p++;
		}
		return r;
	}
};

template<typename T1,typename T2>
struct Pair{
	T1 first;
	T2 second;
};

template <typename T>
struct E{
	bool operator()(T q,T w)const{
		return q==w;
	}
};

template <>
struct E<const char*>{
	bool operator()(const char*q,const char* w)const{
		return strcmp(q,w)==0;
	}
};

template<typename K,typename V,typename H,typename E>
struct dict{
	Pair<K,V>**data=0;
	dict(){
		resize(data,65537);
	}
	Pair<K,V>& find_ptr(K key){
		Pair<K,V>*&d=data[H{}(key)%len(data)];
		if (!d){
			resize(d,0);
		}
		for (uint64_t w=0;w<len(d);++w){
			if (d[w].first and E{}(d[w].first,key)){
				return d[w];
			}
		}
		append(d,Pair<K,V>{0,0});
		return d[len(d)-1];
	}
	uint64_t count(K key){
		Pair<K,V>&d=find_ptr(key);
		return (d.first and E{}(d.first,key));
	}
	V&operator[](K key){
		Pair<K,V>&d=find_ptr(key);
		if (!(d.first and E{}(d.first,key))){
			d.first=key;
		}
		return d.second;
	}
	void erase(K key){
		Pair<K,V>&d=find_ptr(key);
		d.first=0;
	}
	~dict(){
		for (uint64_t w=0;w<len(data);++w){
			del(data[w]);
		}
		del(data);
	}
};

#include <unordered_map>

int main(){
	uint64_t n=getint();
	char tmp[31];
	// std::unordered_map<char*,char*,H<const char*>,E<const char*>> d;
	dict<const char*,const char*,H<const char*>,E<const char*>> d;
	for (uint64_t w=0;w<n;++w){
		scanf("%30s",tmp);
		if (strcmp(tmp,"ADD")==0){
			Pair<char*,char*> t;
			t.first=new char[31];
			scanf("%30s",t.first);
			t.second=new char[31];
			scanf("%30s",t.second);
			if (d.count(t.first)){
				printf("ERROR\n");
				delete[] t.first;
				delete[] t.second;
			}else{
				d[t.first]=t.second;
			}
		}
		if (strcmp(tmp,"DELETE")==0){
			Pair<char*,char*> t;
			t.first=new char[31];
			scanf("%30s",t.first);
			if (!d.count(t.first)){
				printf("ERROR\n");
				delete[] t.first;
			}else{
				d.erase(t.first);
			}
		}
		if (strcmp(tmp,"PRINT")==0){
			Pair<char*,char*> t;
			t.first=new char[31];
			scanf("%30s",t.first);
			if (!d.count(t.first)){
				printf("ERROR\n");
				delete[] t.first;
			}else{
				printf("%s %s\n",t.first,d[t.first]);
			}
		}
		if (strcmp(tmp,"EDITPHONE")==0){
			Pair<char*,char*> t;
			t.first=new char[31];
			scanf("%30s",t.first);
			t.second=new char[31];
			scanf("%30s",t.second);
			if (!d.count(t.first)){
				printf("ERROR\n");
				delete[] t.first;
				delete[] t.second;
			}else{
				d[t.first]=t.second;
			}
		}
	}
}
