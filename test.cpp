<<<<<<< HEAD
#include <bits/stdc++.h>
struct leak{
    std::vector<leak> v;
};




int main(){
    leak l;
    l.v.emplace_back();
    l.v.back()=std::move(l);
    assert(l.v.empty());

=======

auto f(const int n){
    n = 1; //mistake
}

int main(){
    f(0);
>>>>>>> 409b23bb6e0aba34433d9b534b13fbc7cca76958
}

