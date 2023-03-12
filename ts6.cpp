#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <cassert>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <cstring>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <queue>
#include <stack>

using namespace std;

#define none 9000000000000000000

#define bisect(b, e, ...)                                                       \
    ({                                                                          \
        int64_t __begin = b;                                                    \
        int64_t __end = e;                                                      \
        assert(__begin <= __end);                                               \
        while (__begin + 1 < __end) {                                           \
            int64_t __center = (__begin + __end) / 2;                           \
            if (__VA_ARGS__) {                                                  \
                __end = __center;                                               \
            } else {                                                            \
                __begin = __center;                                             \
            }                                                                   \
        }                                                                       \
        int64_t __center = __begin;                                             \
        if (__begin != __end and (__VA_ARGS__)) {                               \
            __end = __center;                                                   \
        }                                                                       \
        __end;                                                                  \
    })

struct item{
    size_t _0;
    size_t _1;
    size_t _2;
};

int main(){
    size_t n=0,s_=0;
    cin>>n>>s_;
    vector<size_t> l(n),r(n);
    for (size_t q=0;q<n;++q){
        cin>>l[q]>>r[q];
    }
    vector<size_t> ls(n+1);
    for (size_t q=0;q<n;++q){
        ls[q+1]=ls[q]+l[q];
    }
    vector<size_t> s(n);
    cout<<bisect(0,20,({
        size_t m=__center;
        ic(m)
        size_t res=1;
        iota(s.begin(),s.end(),0);
        sort(s.begin(),s.end(),[&](auto&q,auto&w){
            size_t qs=(l[q]>m)-(r[q]<m);
            size_t ws=(l[w]>m)-(r[w]<m);
            if (qs!=ws){
                return qs<ws;
            }
            return l[q]<l[w];
        });
        ic(s)
        if (l[s[n/2]]>m){
            res=0;
        }else
        if (r[s[n/2]]<m){
            res=1;
        }else{
            size_t sum=0;
            for (size_t q=0;q<n/2;++q){
                sum+=l[s[q]];
            }
            ic(sum)
            for (size_t q=n/2;q<n;++q){
                sum+=max(m,l[s[q]]);
            }
            ic(sum)
            res=(sum>s_);
        }
        ic(res)
        res;
    }))-1<<endl;
}
