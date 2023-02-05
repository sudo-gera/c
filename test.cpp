#include <bits/stdc++.h>
using namespace std;

template<size_t n>
using sized_int=std::tuple_element_t<"-01-2---3-------4"[n]-48,tuple<int8_t,int16_t,int32_t,int64_t,__int128_t>>;

static_assert(is_same_v<sized_int<1> ,int8_t  >);
static_assert(is_same_v<sized_int<2> ,int16_t >);
static_assert(is_same_v<sized_int<4> ,int32_t >);
static_assert(is_same_v<sized_int<8> ,int64_t >);
static_assert(is_same_v<sized_int<16>,__int128_t>);


int main(){

}
