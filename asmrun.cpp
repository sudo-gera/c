#include <bits/stdc++.h>
using namespace std;

#ifdef print
#undef print
#endif

#ifdef write
#undef write
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

extern "C"
void print(uint64_t out)
asm ("print");
void print(uint64_t out) {
    putint(out);
    putchar('\n');
}


using llu=long long unsigned;

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }

///////////////////////////////////////////////////end of lib



// extern "C"
// uint64_t _c(uint64_t A,uint64_t B,uint64_t C,uint64_t D)
// asm ("_c");

// int main(){
//     cout<<_c(4,6,3,8)<<endl;
// }

extern "C"
void memdump(char*mem,uint64_t len)
asm ("memdump");

void memdump(char*mem,uint64_t len){
    for (uint64_t w=0;w<len;++w){
        printf("%4" PRIu64,(uint64_t)uint8_t(mem[w]));
        // printf("%c",uint8_t(mem[w]));
    }
    cout<<endl;
}

// void make(){
//     int c;
//     char*f=0;
//     uint64_t fl=0;
//     uint64_t fs=0;
//     while ((c=getchar_unlocked())!=EOF){
//         if (fl)
//     }
// }
