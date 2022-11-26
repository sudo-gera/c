#include <bits/stdc++.h>
using namespace std;

template<size_t n>
using sized_int=tuple_element_t<min("-\x00\x01-\x02---\x03-"[n]+0,4),tuple<int8_t,int16_t,int32_t,int64_t,void>>;

static_assert(is_same_v<sized_int<0>, void>);
static_assert(is_same_v<sized_int<1>, int8_t>);
static_assert(is_same_v<sized_int<2>, int16_t>);
static_assert(is_same_v<sized_int<3>, void>);
static_assert(is_same_v<sized_int<4>, int32_t>);
static_assert(is_same_v<sized_int<5>, void>);
static_assert(is_same_v<sized_int<6>, void>);
static_assert(is_same_v<sized_int<7>, void>);
static_assert(is_same_v<sized_int<8>, int64_t>);
static_assert(is_same_v<sized_int<9>, void>);
static_assert(is_same_v<sized_int<10>,int8_t>);
static_assert(is_same_v<sized_int<11>,void>);

int main(){

}
