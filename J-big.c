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

<<<<<<< HEAD
#ifdef print
#undef print
#define hash hash_
#endif

=======
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
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
<<<<<<< HEAD
#define back(a) ((a)[len(a)-1])
=======
#define back(a) (a[len(a)-1])
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6

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

<<<<<<< HEAD
// static inline void write(uint64_t out) {
// 	putint(out);
// 	putchar(' ');
// }
=======
static inline void write(uint64_t out) {
	putint(out);
	putchar(' ');
}
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6

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
	char*key;
	char*value;
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

bool eq(char*q,char*e){
	return strcmp(q,e)==0;
}

void dict_insert(dict*dp,item*tmp){
	if (dp){
		item**a=dp->data+hash(tmp->key)%len(dp->data);
		for (size_t w=0;w<len(*a);++w){
			if (eq(a[0][w].key,tmp->key)){
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
			if (eq(a[0][w].key,tmp->key)){
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
			if (eq(a[0][w].key,tmp->key)){
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

<<<<<<< HEAD
typedef struct part{
	uint64_t l;
	char*p;
	char*sp;
	uint64_t sl;
}part;

#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


char*alloc(uint64_t s,long*next){
	char g[80];
	sprintf(g,"tmp%li.trash.trash",++*next);
	FILE* file=fopen(g,"w");
	fseek(file, s , SEEK_SET);
	fputc('\0', file);
	fclose(file);
	int fd=open(g,O_RDWR);
	struct stat statbuf;
	fstat(fd,&statbuf);
	char*mmem=(char*)mmap(0,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	return mmem;


	// ic(itervect(*a,*a+len(*a)))
	// char*r=0;
	// if (!len(*a) or back(*a).l<s){
	// 	print(99999);
	// 	resize(*a,len(*a)+1);
	// 	back(*a).sl=sysconf(_SC_PAGE_SIZE)*4100;
	// 	back(*a).sp=(char*)mmap ( NULL, sysconf(_SC_PAGE_SIZE)*4100  ,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
	// 	back(*a).l=back(*a).sl;
	// 	back(*a).p=back(*a).sp;
	// }
	// back(*a).l-=s;
	// r=back(*a).p+=s;
	// r-=s;
	// r[0]=0;
	// r[s-1]=0;
	// return r;
}

=======
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
int main(){
	uint64_t n=getint();
	char* com=0,*key=0,*val=0;
	resize(com,40);
	resize(key,4100);
	resize(val,4100);
<<<<<<< HEAD
	long next=0;
	// part*mem=0;
	// int fd=open("tmpmem.trash.trash",O_RDWR);
	// struct stat statbuf;
	// fstat(fd,&statbuf);
	// FILE* file=fopen("tmpmem.trash.trash","w");
	// fseek(file, n*4100*2 , SEEK_SET);
	// fputc('\0', file);
	// fclose(file);
	// int fd=open("tmpmem.trash.trash",O_RDWR);
	// struct stat statbuf;
	// fstat(fd,&statbuf);
	// char*mmem=(char*)mmap(0,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	// close(fd);
	dict*d=dict_create();
	// append(mem,(part){.l=n*4100*2,.p=mmem,.sp=mmem,.sl=n*4100*2});
	// ic(itervect(mem,mem+len(mem)))
=======
	dict*d=dict_create();
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
	for (uint64_t w=0;w<n;++w){
		scanf("%35s",com);
		scanf("%4096s",key);
		if (com[0]=='A'){
			scanf("%4096s",val);
			item t;
			t.key=key;
			if (dict_find(d,&t)){
				printf("ERROR\n");
			}else{
<<<<<<< HEAD
				t.key=alloc(4100,&next);
				t.value=alloc(4100,&next);
				// t.key=(char*)malloc(4100);
				// t.value=(char*)malloc(4100);
				strcpy(t.key,key);
=======
				t.key=(char*)malloc(4100);
				strcpy(t.key,key);
				t.value=(char*)malloc(4100);
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
				strcpy(t.value,val);
				dict_insert(d,&t);
			}
		}
		if (com[0]=='D'){
			item t;
			t.key = key;
			if (dict_find(d,&t)){
				dict_erase(d,&t);
<<<<<<< HEAD
				// free(t.key);
				// free(t.value);
=======
				free(t.key);
				free(t.value);
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
			}else{
				printf("ERROR\n");
			}
		}
		if (com[0]=='U'){
			scanf("%4096s",val);
			item t;
			t.key=key;
			if (dict_find(d,&t)){
				dict_erase(d,&t);
<<<<<<< HEAD
				// free(t.key);
				// free(t.value);
				t.key=alloc(4100,&next);
				t.value=alloc(4100,&next);
				// t.key=(char*)malloc(4100);
				// t.value=(char*)malloc(4100);
				strcpy(t.key,key);
=======
				free(t.key);
				free(t.value);
				t.key=(char*)malloc(4100);
				strcpy(t.key,key);
				t.value=(char*)malloc(4100);
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
				strcpy(t.value,val);
				dict_insert(d,&t);
			}else{
				printf("ERROR\n");
			}
		}
		if (com[0]=='P'){
			item t;
			t.key=key;
			if (dict_find(d,&t)){
				printf("%s %s\n",t.key,t.value);
			}else{
				printf("ERROR\n");
			}
		}
	}
<<<<<<< HEAD
	// for (uint64_t w=0;w<len(d->data);++w){
	// 	for (uint64_t e=0;e<len(d->data[w]);++e){
	// 		free(d->data[w][e].key);
	// 		free(d->data[w][e].value);
	// 	}
	// }
	// for (uint64_t w=0;w<len(mem);++w){
		// free(mem[w].sp);
		// munmap(mem[w].sp, mem[w].sl);
	// }
	// del(mem);
=======
	for (uint64_t w=0;w<len(d->data);++w){
		for (uint64_t e=0;e<len(d->data[w]);++e){
			free(d->data[w][e].key);
			free(d->data[w][e].value);
		}
	}
>>>>>>> a2553e7337c89409150c4a381a8fd7af7974c7c6
	dict_del(d);
	del(com);
	del(key);
	del(val);
}
