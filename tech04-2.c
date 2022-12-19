#ifndef assert
#include <assert.h>
#endif
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
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

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

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib


#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// int main()
// {
//     char *str_buffer = calloc(sizeof(char) , PATH_MAX);



//     struct stat f_stat;
//     while (fgets(str_buffer, PATH_MAX, stdin) != NULL)
//     {
//     	str_buffer[strlen(str_buffer) - 1] = '\0';

//     	if (lstat(str_buffer, &f_stat) == 0) {
//     		if(__S_IEXEC&(f_stat.st_mode)) {
// 				int f=open(str_buffer,O_RDONLY);
// 			    char *data = calloc(sizeof(char) , PATH_MAX+2);
// 				read(f,data,PATH_MAX+2);
// 				if (data[1]=='E' and data[2]=='L' and data[3]=='F'){

// 				}else{
// 					if (data[0]=='#' and data[1]=='!'){
// 						for (int w=0;w<PATH_MAX+2;++w){
// 							if (data[w]=='\n' or data[w]=='\r'){
// 								data[w]='\0';
// 								break;
// 							}
// 						}
// 						if (lstat(data+2, &f_stat) == 0){
// 				    		if(__S_IEXEC&(f_stat.st_mode)) {

// 							}else{
// 								printf("%s\n",str_buffer);
// 							}
// 						}else{
// 							printf("%s\n",str_buffer);
// 						}
// 					}else{
// 						printf("%s\n",str_buffer);
// 					}
// 				}
//     		}
//     	}else{
// 		}
//     }

//     free(str_buffer);

//     // printf("%" PRId64 "\n", size_summ);
//     return 0;
// }


extern void normalize_path(char * path){
    {
        char*path_read=path;
        char*path_write=path;
        while (*path_read){
            if (path_read>=1+path and *(path_read-1)=='/' and *path_read=='/'){
                path_write-=1;
            }
            *path_write++=*path_read++;
        }
		*path_write='\0';
    }
    {
        char*path_read=path;
        char*path_write=path;
        while (*path_read){
            if ((path_read>=2+path and *(path_read-2)=='/' or path_read==1+path) and *(path_read-1)=='.' and *path_read=='/'){
                path_write-=2;
            }
            *path_write++=*path_read++;
        }
		*path_write='\0';
    }
    {
        char*path_read=path;
        char*path_write=path;
        while (*path_read){
            if (path_read>=4+path and *(path_read-3)=='/' and *(path_read-2)=='.' and *(path_read-1)=='.' and *path_read=='/'){
                path_write-=4;
                while (path<=path_write and *path_write!='/'){
                    path_write-=1;
                }
            }
            *path_write++=*path_read++;
        }
		*path_write='\0';
    }
}

#if __has_include("d")
char data[1024];
int main(){
	scanf("%s",data);
	normalize_path(data);
	printf("%s\n",data);
}
#endif