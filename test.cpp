#include <bits/stdc++.h>
struct leak{
    std::vector<leak> v;
};




int main(){
    leak l;
    l.v.emplace_back();
    l.v.back()=std::move(l);
    assert(l.v.empty());

}

