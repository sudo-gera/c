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
#include <memory>
#include <queue>
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::back_inserter, std::list, std::hash, std::reverse;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::queue;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::tuple_element, std::tuple_size, std::is_same, std::make_shared;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::unique, std::unique_ptr, std::shared_ptr, std::make_unique;

using namespace std::literals;

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


///////////////////////////////////////////////////end of lib

struct item{
    // size_t count=0;
    vector<const string*> values;
    unordered_map<int,item*> next;
    item* prev=0;
    item* suff=0;
    item* term=0;
    item* t=this;
    operator item*(){
        return this;
    }
    auto operator->(){
        return this;
    }
    // unordered_map<int,item> next;
};

template<typename item>
struct bohr{
    deque<item> a=deque<item>(1);
    item&root=a.front();
    auto add(const auto&s){
        item*ptr=root;
        for (auto w:s){
            if (ptr->next.count(w)==0){
                a.emplace_back();
                ptr->next[w]=a.back();
            }
            ptr->next[w]->prev=ptr;
            ptr=ptr->next[w];
        }
        // ptr->count+=1;
        ptr->values.push_back(&s);
    }
    auto make_links(){
        root->suff=root;
        auto q=queue<item*>();
        q.push(root);
        while (q.size()){
            auto t=q.front();
            q.pop();
            for (auto&w:t->next){
                auto c=w.first;
                auto y=t->suff;
                while (y!=root and y->next.count(c)==0){
                    y=y->suff;
                }
                if (y->next.count(c) and y->next[c]!=w.second){
                    w.second->suff=y->next[c];
                }else{
                    w.second->suff=y;
                }
                q.push(w.second);
            }
        }
        root->term=root;
        q.push(root);
        while (q.size()){
            auto t=q.front();
            q.pop();
            for (auto&w:t->next){
                item*e=w.second;
                if (e->suff->values.size()){
                    e->term=e->suff;
                }else{
                    e->term=e->suff->term;
                }
                q.push(w.second);
            }
        }
    }
    auto next(item*&ptr,auto c,vector<const string*>&res){
        while (ptr!=root and ptr->next.count(c)==0){
            ptr=ptr->suff;
        }
        if (ptr->next.count(c)){
            ptr=ptr->next[c];
        }
        auto t=ptr;
        while (t!=root){
            for (auto&w:t->values){
                res.push_back(w);
            }
            t=t->term;
        }
        return res;
    }
};



int main(){
    bohr<item> b;
    vector<string> s({
        "1",
        "121",
        "212",
        "21",
        "12"        
    });
    for (auto&w:s){
        b.add(w);
    }
    b.make_links();
    item* tmp=b.root;
    vector<const string*>res;
    for (auto w:"12121"s){
        b.next(tmp,w,res);
        res.push_back(0);
    }
    for (auto w:res){
        if (w){
            cout<<*w<<" ";
        }else{
            cout<<"\n";
        }
    }
    // ic(b.a)
    // for (auto&w:b.a){
    //     cout<<"    "<<(long)(w.t)<<" -> "<<(long)(w.prev)<<"[label=\"prev\"]"<<endl;
    //     cout<<"    "<<(long)(w.t)<<" -> "<<(long)(w.suff)<<"[label=\"suff\"]"<<endl;
    //     cout<<"    "<<(long)(w.t)<<" -> "<<(long)(w.term)<<"[label=\"term\"]"<<endl;
    //     for (auto&e:w.next){
    //         cout<<"    "<<(long)(w.t)<<" -> "<<(long)(e.second)<<"[label=\"next_"<<e.first<<"\"]"<<endl;
    //     }
    // }
}
