#include <bits/stdc++.h>
using namespace std;


template<typename T>
constexpr int print_type_f(){
    int unused=0;
    return 1;
}

template<typename T>
using print_type=conditional_t<print_type_f<T>(),T,void>;

int main(){
    array<print_type<long>,20> a;
    array<print_type<string>,20> s;
}
