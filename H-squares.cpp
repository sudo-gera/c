#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <assert.h>
using std::cin, std::cout, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map, std::min,std::max;

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

static inline void print(uint64_t out) {
    putint(out);
    putchar('\n');
}

static inline void write(uint64_t out) {
    putint(out);
    putchar(' ');
}

using llu=long long unsigned;

///////////////////////////////////////////////////end of lib

llu floor_root(llu q){
	llu r=0;
	llu p=1ULL<<62;
	llu u=0;
    while (p){
		u=r+p;
		if (q >= u) {
			q-=u;
			r+=p;
			r+=p;
        }
		r>>=1;
		p>>=2;
    }
	return r;
}


struct squares
{
    vector<llu> cache;

    llu find(llu n,llu dep=-1){
        write(n);print(dep);
        if (dep==0){
            return -1;
        }
        if (cache[n]){
            llu c=cache[n];
            if (c>dep){
                return -1;
            }
        }
        llu r=floor_root(n);
        llu ans=n-1;
        while (r)
        {
            ans=min(ans,find(n-r*r,min(dep-1,ans)));
            r-=1;
        }
        cache[n]=ans+1;
        return ans+1;
    }
};


int main(){
    llu n=getint();
    squares s;
    s.cache.resize(n+1);
    print(s.find(n));
}



// int main(){
//     llu n=getint();
//     vector<llu> a(n+1);
//     a[1]=1;
//     for (llu w=2;w<n+1;++w){
//         if (w%10000==0){
//             print(w);
//         }
//         a[w]=-1;
//         llu q=1;
//         while (w>=q*q){
//             a[w]=std::min(a[w-q*q]+1,a[w]);
//             q+=1;
//         }
//     }
//     print(a[n]);
// }