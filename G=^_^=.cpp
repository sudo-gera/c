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
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::unique, std::decay_t, std::is_convertible_v, std::array;

template <typename T>
struct StaticCast {};

template <typename T, typename Y>
auto operator->*(T v, StaticCast<Y>) {
    return static_cast<Y>(v);
}

StaticCast<ssize_t> si;
StaticCast<size_t> ui;

int64_t GetInt() {
    int sign = 1;
    int c = 0;
    size_t res = 0;
    while (c = getchar_unlocked(), isspace(c)) {
    }
    if (c == '-') {
        sign = -1;
    } else {
        res = c - '0';
    }
    while (c = getchar_unlocked(), isdigit(c)) {
        res *= 10;
        res += c - '0';
    }
    return static_cast<int64_t>(res) * sign;
}

template <typename T>
ssize_t Len(T&& q) {
    return static_cast<ssize_t>(q.size());
}

using llu=long long unsigned;
using lli=long long;

#define cache(rt,...)\
    static map<decltype(make_tuple(__VA_ARGS__)),rt> cache;\
    if ((cache).count({__VA_ARGS__})){\
        return (cache)[{__VA_ARGS__}];\
    }

#define none 9000000000000000000

template<llu n>
struct sized{
    char a[n];
};

template<
    typename t0=sized<0>,
    typename t1=sized<0>,
    typename t2=sized<0>,
    typename t3=sized<0>,
    typename t4=sized<0>,
    typename t5=sized<0>,
    typename t6=sized<0>,
    typename t7=sized<0>
>
// better than tuple
struct t{
    t0 v0;
    t1 v1;
    t2 v2;
    t3 v3;
    t4 v4;
    t5 v5;
    t6 v6;
    t7 v7;
};

template<llu n=0,typename T,typename R>
requires(tuple_size_v<R><=n or  is_same_v<sized<0>*,tuple_element_t<n,R>>)
auto clear_tuple(T t=tuple<>(),R r=tuple<>()){
    return t;
}

template<llu n=0,typename T,typename R>
requires(n<tuple_size_v<R> and !is_same_v<sized<0>*,tuple_element_t<n,R>>)
auto clear_tuple(T t=tuple<>(),R r=tuple<>()){
    return clear_tuple<n+1>(tuple_cat(t,make_tuple(get<n>(r))),r);
}

template<typename...T>
auto t2tuple(t<T...>r){
    return apply([&](auto...a){return tuple(*(a)...);},clear_tuple(tuple<>(),tuple{&r.v0,&r.v1,&r.v2,&r.v3,&r.v4,&r.v5,&r.v6,&r.v7}));
}

template<typename...T>
auto to_str(t<T...>r){
    return t2tuple(r);
}

template<typename...R,typename...Y>bool operator< (t<R...>r,t<Y...>y){return t2tuple(r)< t2tuple(y);}
template<typename...R,typename...Y>bool operator> (t<R...>r,t<Y...>y){return t2tuple(r)> t2tuple(y);}
template<typename...R,typename...Y>bool operator<=(t<R...>r,t<Y...>y){return t2tuple(r)<=t2tuple(y);}
template<typename...R,typename...Y>bool operator>=(t<R...>r,t<Y...>y){return t2tuple(r)>=t2tuple(y);}
template<typename...R,typename...Y>bool operator!=(t<R...>r,t<Y...>y){return t2tuple(r)!=t2tuple(y);}
template<typename...R,typename...Y>bool operator==(t<R...>r,t<Y...>y){return t2tuple(r)==t2tuple(y);}


#ifndef ic
#define ic(...)
#endif

#ifndef eic
#define eic
#endif

/*

a | assign(min) | b;
-- instead of
a = min(a, b);

*/

template<typename T>
struct assign_s{
    T f;
};

template<typename T>
assign_s(T f)->assign_s<T>;

template<typename T,typename Y>
auto operator|(T&&q,assign_s<Y> w){
    return t<remove_reference_t<T>*,assign_s<Y>>{&q,w};
}

template<typename R,typename T,typename Y>
auto operator|(t<R*,assign_s<T>> q,Y&&w){
    q.v0[0]=q.v1.f(q.v0[0],w);
}

#define assign(f) assign_s{[&](auto q,auto w){return (f)(q,w);}}

template<typename T=void>
struct Scan{
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
    template<typename Y=T>
    operator Y(){
        Y val;
        cin>>val;
        return val;
    }
};

///////////////////////////////////////////////////end of lib

template <typename T>
auto PrefixFun(T&& s) {
    vector<size_t> p(s.size());
    for (size_t q = 1; q < s.size(); ++q) {
        size_t k = p[q - 1];
        while (k > 0 and s[q] != s[k]) {
            k = p[k - 1];
        }
        if (s[q] == s[k]) {
            k++;
        }
        p[q] = k;
    }
    return p;
}

int main() {
    string p = Scan<string>()();
    string f = Scan<string>()();
    auto p_f = p + " " + f;
    auto f_p = f + " " + p;
    reverse(f_p.begin(), f_p.end());
    auto pfl = PrefixFun(p_f);
    auto pfr = PrefixFun(f_p);
    vector<size_t> ans;
    ic(pfl)
    ic(pfr)
    for (size_t q = p.size(); q <= f.size(); ++q) {
        ic(q)
        ic(pfl[q + p.size()])
        ic(pfr[2 * p.size() + f.size() - q])
        if (pfl[q + p.size()] + pfr[2 * p.size() + f.size() - q] == p.size() or pfl[q + p.size()] == p.size() or
            pfr[2 * p.size() + f.size() - q] == p.size()) {
            ans.push_back(q - p.size());
        }
    }
    for (auto q : ans) {
        cout << q << " ";
    }
    cout << endl;
}
