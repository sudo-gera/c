#include <bits/stdc++.h>
using llu = long long unsigned;

template<llu q,llu w>
struct sum_s{
    constexpr static llu value = q+w;
};

template<typename T,T v>
struct i_con{
    constexpr static T value = v;

    constexpr operator T(){
        return value;
    }
}

int main(){
    std::array<char,sum_s<2,3>::value> f;
    std::cout<<sizeof(f)<<std::endl;
}






