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
    size_t n=0;
    cin>>n;
    vector<size_t> a(n);
    for (auto&w:a){
        cin>>w;
    }
    set<pair<size_t,size_t>> cou_val;
    map<size_t,decltype(cou_val.begin())> val_cou;
    for (size_t q=0;q<n;++q){
        val_cou[a[q]]=cou_val.insert({0,a[q]}).first;
    }
    size_t l=-1;
    for (size_t q=0;q<n;++q){
        auto nh=cou_val.extract(val_cou[a[q]]);
        nh.value().first++;
        val_cou[a[q]]=cou_val.insert(move(nh)).position;
        if (cou_val.begin()->first==next(cou_val.end(),-2)->first and cou_val.begin()->first+1==next(cou_val.end(),-1)->first){
            l=q+1;
        }
    }
    cout<<l<<endl;
}
