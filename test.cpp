#include <bits/stdc++.h>
using namespace std;

#pragma clang diagnostic ignored "-Wall"


template<size_t b=0,size_t e=16,typename F,typename N,typename...A>
constexpr decltype(auto) call(F&&f,N&&n,A&&...a){
    if (b>n or n>=e){
        assert(((void)"wrong value",0));
    }else if constexpr (b+1==e){
        return f(integral_constant<N,b>(),forward<A>(a)...);
    }else if (n<(b+e)/2){
        return call<b,(b+e)/2>(forward<F>(f),forward<N>(n),forward<A>(a)...);
    }else{
        return call<(b+e)/2,e>(forward<F>(f),forward<N>(n),forward<A>(a)...);
    }
}



int main(){
    auto f=[](auto n)->decltype(auto){
        array<int,n> r;
    };
    call(f,9);
}