#include <bits/stdc++.h>
using namespace std;

struct test{
    int v=48;
    char t=49;
    operator decltype(make_tuple(v,t))(){
        return make_tuple(v,t);
    }
};

int main(){
    test u;
    tuple<int,char> t(u);
}

