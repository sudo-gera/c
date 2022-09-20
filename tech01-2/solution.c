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
    /////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
	#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
	#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
	#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
	#define back(a) ((a)[len(a)-1])
#endif

///////////////////////////////////////////////////end of lib


const char*b64decode=\
    "|||||||||||||||||||||||||||||||||||||||||||\x3e|||\x3f\x34\x35\x36\x37"\
    "\x38\x39\x3a\x3b\x3c\x3d|||\x00|||\x00\x01\x02\x03\x04\x05\x06\x07\x08"\
    "\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19||"\
    "||||\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29"""\
    "\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33||||||||||||||||||||||||||||||"\
    "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"\
    "|||||||||||||||||||||||||||||||||";

char* base64decode(const char*sb64str){
    char c=0;
    char*b64str=0;
    for (long w=0;(c=sb64str[w]);++w){
        if (b64decode[c]!='|'){
            append(b64str,c);
        }
    }
    char*str=0;
    for (long w=0;w<len(b64str);w+=4){
        long t=0;
        t+=(((unsigned)b64decode[b64str[w+0]])<<6*3);
        t+=(((unsigned)b64decode[b64str[w+1]])<<6*2);
        t+=(((unsigned)b64decode[b64str[w+2]])<<6*1);
        t+=(((unsigned)b64decode[b64str[w+3]])<<6*0);
        if (b64str[w+1]!='='){
            append(str,(t>>(8*2))&0xff);
        }
        if (b64str[w+2]!='='){
            append(str,(t>>(8*1))&0xff);
        }
        if (b64str[w+3]!='='){
            append(str,(t>>(8*0))&0xff);
        }
    }
    return str;
}

enum state{
    _new_line, _comment, _value
};

int main(){
    char*str=base64decode(B64STR);
    long state=_new_line;
    long val_start=0;
    long only_digits=0;
    long sum=0;
    for (long w=0;w<len(str);++w){
        if (str[w]=='\n'){
            if (state==_value){
                str[w]='\0';
                if (only_digits){
                    sum+=atoi(str+val_start);
                }else{
                    printf("%s\n",str+val_start);
                }
            }
            state=_new_line;
        }else
        if (str[w]=='#' and state==_new_line){
            state=_comment;
        }else
        if (str[w]=='=' and state==_new_line){
            state=_value;
            val_start=w+1;
            only_digits=1;
        }else
        if (state==_value){
            if (str[w]<'0' or '9'<str[w]){
                only_digits=0;
            }
        }
    }
    printf("%li\n",sum);
}