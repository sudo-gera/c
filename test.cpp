#include <bits/stdc++.h>
using namespace std;

template<size_t n>
using sized_int=tuple_element_t<8/n%5/!(16%n),tuple<__int128_t,int64_t,int32_t,int8_t,int16_t>>;

// static_assert(is_same_v<sized_int< 1>,  __int8_t>);
// static_assert(is_same_v<sized_int< 2>, __int16_t>);
// static_assert(is_same_v<sized_int< 4>, __int32_t>);
// static_assert(is_same_v<sized_int< 8>, __int64_t>);
// static_assert(is_same_v<sized_int<16>,__int128_t>);





