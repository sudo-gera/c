#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <assert.h>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <string.h>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::reduce, std::move, std::swap, std::generate, std::generate_n;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::string_view;

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

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }

///////////////////////////////////////////////////end of lib

#define bisect(b, e, ...)														\
	({																			\
		int64_t __begin = b;													\
		int64_t __end = e;														\
		assert(__begin <= __end);												\
		while (__begin + 1 < __end) {											\
			int64_t __center = (__begin + __end) / 2;							\
			if (__VA_ARGS__) {													\
				__end = __center;												\
			} else {															\
				__begin = __center;												\
			}																	\
		}																		\
		int64_t __center = __begin;												\
		if (__begin != __end and (__VA_ARGS__)) {								\
			__end = __center;													\
		}																		\
		__end;																	\
	})

struct MCS{
    llu base=8589803521;
    llu inv=8590065665;
    vector<llu> powers;
    vector<llu> d,f;

    MCS():
        powers(32768),
        d(32768),f(32768){}

    llu h(vector<llu>&v,llu b,llu e){
        return v[e]-v[b]*powers[e-b];
    }

    string find(const string&a,const string&s){
        powers[0]=1;
        for (llu w=1;w<32768;++w){
            powers[w]=powers[w-1]*base;
        }
        assert(a.size()<30000);
        assert(s.size()<30000);
        for (llu w=0;w<a.size();++w){
            d[w+1]=d[w]*base+a[w];
        }
        for (llu w=0;w<s.size();++w){
            f[w+1]=f[w]*base+s[w];
        }
        llu maxlen=bisect(0,min(a.size(),s.size()),({
            map<llu,vector<llu>> q,w;
            set<llu> e,r;
            for (llu z=__center;z<a.size();++z){
                llu t=h(d,z-__center,z);
                e.insert(t);
                q[t].push_back(z-__center);
            }
            for (llu z=__center;z<s.size();++z){
                llu t=h(f,z-__center,z);
                r.insert(t);
                w[t].push_back(z-__center);
            }
            vector<llu> t;
            set_intersection(e.begin(),e.end(),r.begin(),r.end(),back_inserter(t));
            llu res=1;
            for (auto&z:t){
                for (auto&x:q[z]){
                    for (auto&c:w[z]){
                        if (memcmp(a.data()+x,s.data()+c,__center)==0){
                            res=0;
                            break;
                        }
                    }
                    if (res==0){
                        break;
                    }
                }
                if (res==0){
                    break;
                }
            }
            res;
        }));
        if (maxlen==0){
            return 0;
        }
        llu __center=maxlen-1;
        map<llu,vector<llu>> q,w;
        set<llu> e,r;
        for (llu z=__center;z<a.size();++z){
            llu t=h(d,z-__center,z);
            e.insert(t);
            q[t].push_back(z-__center);
        }
        for (llu z=__center;z<s.size();++z){
            llu t=h(f,z-__center,z);
            r.insert(t);
            w[t].push_back(z-__center);
        }
        vector<llu> t;
        set_intersection(e.begin(),e.end(),r.begin(),r.end(),back_inserter(t));
        vector<string_view> res;
        for (auto&z:t){
            for (auto&x:q[z]){
                for (auto&c:w[z]){
                    if (memcmp(a.data()+x,s.data()+c,__center)==0){
                        res.emplace_back(a.data()+x,__center);                    
                    }
                }
            }
        }
        sort(res.begin(),res.end());
        return string(res[0]);
    }
};

int main(){
    string a,s;
    cin>>a>>s;
    cout<<MCS().find(a,s)<<endl;
}