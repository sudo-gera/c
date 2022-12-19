#include <bits/stdc++.h>
using namespace std;
using llu = long long unsigned;

template<llu q,llu w,__int128_t s>
concept cond=((s>>(8*(q-1)))&0xff)==w;

template<llu q>
concept _1=(bool)(q&1);

template<llu q>
concept _2=(bool)(q&2);

template<llu q>
concept _3=_1<q> and _2<q>;

template<llu q>
concept _4=(bool)(q&4);

template<llu q>
concept _8=(bool)(q&8);

template<llu q>
concept _12=_4<q> and _8<q>;

template<llu q>
requires _3<q>
auto f()->enable_if_t<_12<q>,int>{
    cout<<__LINE__<<endl;
}

template<llu q>
requires _1<q>
auto f()->enable_if_t<_4<q>,int>{
    cout<<__LINE__<<endl;
}


int main(){
    f<3+4>();
}