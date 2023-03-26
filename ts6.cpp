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
    vector<pair<size_t,size_t>> sl(n);
    for (size_t q=0;q<n;++q){
        sl[q]={l[q],q};
    }
    sort(sl.begin(),sl.end());
    vector<pair<size_t,size_t>> s(n);
// #ifdef HOME
    // size_t _end=20;
// #else
    size_t _end=none;
// #endif
    cout<<bisect(0,_end,({
        size_t m=__center;
        // ic(m)
        size_t res=1;
        size_t ss=0;
        for (size_t q=0;q<n;++q){
            auto tmp=sl[q];
            if (r[tmp.second]<m){
                s[ss++]={tmp.second,tmp.first};
            }
        }
        for (size_t q=0;q<n;++q){
            auto tmp=sl[q];
            if (r[tmp.second]>=m){
                s[ss++]={tmp.second,tmp.first};
            }
        }
        // for (size_t q=0;q<n;++q){
        //     s[q]={q,l[q]};
        // }
        // sort(s.begin(),s.end(),[&](auto&q,auto&w){
        //     size_t qs=r[q.first]>=m;
        //     size_t ws=r[w.first]>=m;
        //     if (qs!=ws){
        //         return qs<ws;
        //     }
        //     return q.second<w.second;
        // });
        // ic(s)
        if (s[n/2].second>m){
            res=0;
        }else
        if (r[s[n/2].first]<m){
            res=1;
        }else{
            size_t sum=0;
            for (size_t q=0;q<n/2;++q){
                sum+=s[q].second;
            }
            // ic(sum)
            for (size_t q=n/2;q<n;++q){
                sum+=max(m,s[q].second);
            }
            // ic(sum)
            res=(sum>s_);
        }
        // ic(res)
        res;
    }))-1<<endl;
}
