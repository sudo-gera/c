#include <bits/stdc++.h>


using llu=long long unsigned;

template<llu b=0,llu e=1024>
decltype(auto) call(auto&&f, llu n){
    assert(b<=n and n<e);
    if constexpr(b+1==e){
        return f(std::integral_constant<llu,b>());
    }else if (n<(b+e)/2){
        return call<b,(b+e)/2>(f,n);
    }else{
        return call<(b+e)/2,e>(f,n);
    }
}


int main(){
    auto f=[](auto n){
        std::array<char,n> a;
        std::cout<<sizeof(a)<<std::endl;
    };
    llu n=0;
    std::cin>>n;
    call(f,n);
}





