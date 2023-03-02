#include <bits/stdc++.h>
using namespace std;

struct a{virtual void f(){}};

struct s:a{virtual void f(){}};

int main(){
    s d;
    ic(sizeof(d))
    ic((void*&)(d))
}
