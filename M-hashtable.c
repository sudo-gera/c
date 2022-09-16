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
		while(!*vp){}
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
		while(!a){}
		memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
		a->mem_size = new_size / el_size;
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
#define back(a) (a[len(a)-1])

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

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

uint64_t hash(char*s){
	uint64_t r=0;
	while (*s){
		r*=29;
		r+=*s-'a';
		++s;
	}
	return r;
}

typedef struct item{
	char key[44];
	char value[44];
}item;

typedef struct dict{
	item**data;
}dict;

#define hashlen 59243

dict* dict_create(){
	dict*a=(dict*)calloc(1,sizeof(dict));
	resize(a->data,hashlen);
	return a;
}

<<<<<<< HEAD
=======
bool eq(char*q,char*e){
	return strcmp(q,e)==0;
}

>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
void dict_insert(dict*dp,item*tmp){
	if (dp){
		item**a=dp->data+hash(tmp->key)%len(dp->data);
		for (size_t w=0;w<len(*a);++w){
<<<<<<< HEAD
			if (strcmp(a[0][w].key,tmp->key)==0){
=======
			if (eq(a[0][w].key,tmp->key)){
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
				a[0][w]=*tmp;
				return;
			}
		}
		append(a[0],*tmp);
	}
}

void dict_erase(dict*dp,item*tmp){
	if (dp){
		item**a=dp->data+hash(tmp->key)%len(dp->data);
		for (size_t w=0;w<len(*a);++w){
<<<<<<< HEAD
			if (strcmp(a[0][w].key,tmp->key)==0){
=======
			if (eq(a[0][w].key,tmp->key)){
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
				memmove(a[0]+w,a[0]+w+1,(len(a[0])-w-1)*sizeof(item));
				pop(a[0]);
				return;
			}
		}
	}
}

bool dict_find(dict*dp,item*tmp){
	if (dp){
		item**a=dp->data+hash(tmp->key)%len(dp->data);
		for (size_t w=0;w<len(*a);++w){
<<<<<<< HEAD
			if (strcmp(a[0][w].key,tmp->key)==0){
=======
			if (eq(a[0][w].key,tmp->key)){
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
				*tmp=a[0][w];
				return 1;
			}
		}
	}
	return 0;
}

void dict_del(dict*a){
	if (a){
		for (size_t w=0;w<len(a->data);w++){
			del(a->data[w]);
		}
		del(a->data);
		free(a);
	}
}

int main(){
	int c;
	char*com=0;
	dict**data=0;
	resize(data,10);
	while (1){
		resize(com,0);
		while (isspace(c=getchar())){
		}
		if (c==EOF){
			break;
		}
		append(com,c);
		while (isalnum(c=getchar())){
			append(com,c);
		}
		if (c==EOF){
			break;
		}
		com[len(com)]=0;
		if (*com=='c'){
			size_t g=getint();
			if (data[g]==0){
				data[g]=dict_create();
			}
		}
		if (*com=='i'){
			size_t g=getint();
			item tmp;
			scanf("%40s",tmp.key);
			scanf("%40s",tmp.value);
			dict_insert(data[g],&tmp);
		}
		if (*com=='e'){
			size_t g=getint();
			item tmp;
			scanf("%40s",tmp.key);
			dict_erase(data[g],&tmp);
		}
		if (*com=='f'){
			size_t g=getint();
			item tmp;
			scanf("%40s",tmp.key);
			if (dict_find(data[g],&tmp)){
				printf("%s\n",tmp.value);
			}else{
				printf("MISSING\n");
			}
		}
		if (*com=='d'){
			size_t g=getint();
			dict_del(data[g]);
			data[g]=0;
		}
	}
	for (size_t w=0;w<len(data);++w){
		dict_del(data[w]);
	}
	del(data);
	del(com);
}
