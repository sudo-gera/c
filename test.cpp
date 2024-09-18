#include <tuple>
#include <array>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

int l(){
    std::ifstream in("");
}

constexpr int c(int x){
    assert(x);
    return x;
    // return x < 10 ? x : x * l();
}

static_assert(c(1));

int main(){
    array<int, 1> a;
    cout << get<0>(a) << endl;;
}
