#include <bits/stdc++.h>
using namespace std;


template<typename T>
constexpr int print_value(){
    int unused=0;
    return 1;
}


int main(){
    array<conditional_t<print_value<long>(),int,void>,20> a;
}
