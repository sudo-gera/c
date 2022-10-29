#include <bits/stdc++.h>
using namespace std;

using llu = long long unsigned;

struct a{
    llu t=0;
    constexpr a(){};
    constexpr llu get(){return t;}
    constexpr void set(llu r){t=r;}
};


constexpr a s(llu n){
    a g;
    g.set(g.get()+1);
    return g;
}

static_assert(s(0).get()==1);

int main(){}