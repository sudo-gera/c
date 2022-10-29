#include <bits/stdc++.h>
using namespace std;

using llu = long long unsigned;

template<llu n>
struct fib_s{
    static constexpr llu value=fib_s<n-1>::value+fib_s<n-2>::value;
};

template<>
struct fib_s<0>{
    static constexpr llu value=0;
};

template<>
struct fib_s<1>{
    static constexpr llu value=1;
};

constexpr llu fib_f(llu n){
    if (n<2){
        return n;
    }
    return fib_f(n-1)+fib_f(n-2);
}

// static_assert(fib_f(50)       ==12586269025);
static_assert(fib_s<50>::value==12586269025);

int main(){

}