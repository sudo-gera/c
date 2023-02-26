#include <bits/stdc++.h>
using namespace std;
template<size_t n,typename...T>
union ct{
    tuple<T...> t;
    char a[n+1];
};

template<size_t q,size_t w,typename...T>
constexpr auto check_offset(){
    ct<w,T...> u={tuple<T...>()};
    void* a=&get<q>(u.t);
    void* s=u.a+w;
    return a==s;
}


template<size_t q,size_t w,typename...T>
constexpr auto get_offset_(){
    if constexpr(check_offset<q,w,T...>()){
        return w;
    }else{
        return get_offset_<q,w+1,T...>();
    }
}

template<size_t q,typename...T>
constexpr auto get_offset(){
    return get_offset_<q,0,T...>();
}

// static_assert(get_offset<3,char,int,long,char>()==16);

template<size_t n>
struct sized{
    char a[n];
};

template<size_t n,typename T>
struct with_offset:sized<n>{
    T _;
    operator T&(){
        return _;
    }
    operator const T&()const{
        return _;
    }
};

template<size_t q,typename...T>
auto t_type_f(){
    if constexpr(q<tuple_size_v<tuple<T...>>){
        return declval<with_offset<get_offset<q,T...>(),tuple_element_t<q,tuple<T...>>>>();
    }else{
        return sized<1>();
    }
}

template<size_t q,typename...T>
using t_type=decltype(t_type_f<q,T...>());

template<typename...T>
union t{
    tuple<T...> t;
    t_type<0,T...> _0;
    t_type<1,T...> _1;
    t_type<2,T...> _2;
    t_type<3,T...> _3;
    t_type<4,T...> _4;
    t_type<5,T...> _5;
    t_type<6,T...> _6;
    t_type<7,T...> _7;
    t_type<8,T...> _8;
    t_type<9,T...> _9;
};

constexpr char _assert(bool v){
    return ""[1-v];
}

constexpr int test(){
    t<char,int,char,long> y({{48,49,50,51}});
    _assert(y._0==48);
    return 1;
}

static_assert(test());

int main(){

}


