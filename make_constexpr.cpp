#include <assert.h>
#include <type_traits>

namespace make_constexpr{

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

    struct start{
        llu n=0;
    };

    auto operator*(start c,llu n){
        c.n=n;
        return c;
    }

    template<typename T>
    decltype(auto) operator/(start c,T&&f){
        return call(f,c.n);
    }
};

#define make_constexpr(var) make_constexpr::start()*(var)/[&](auto var)

#include <iostream>
#include <array>

int main(){
    int m;
    std::cin>>m;
    make_constexpr(m){
        std::array<int,m> f;
        std::cout<<f.size()<<std::endl;
    };
}
