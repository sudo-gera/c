#include <tuple>
#include <array>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

constexpr void f(int){};

template<int y>
concept a = f(y);

int main(){
    // int n = 7;
    // int a[n];
    // cout << strtype<decltype(a)*>() << endl;
    // static_assert(requires{
    //     (decltype(a)*){}
    // ;});
}
