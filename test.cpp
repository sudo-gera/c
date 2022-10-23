#include <bits/stdc++.h>
using namespace std;

using llu=long long unsigned;

// struct Any;


struct visitable_any{
    template<typename T>
    llu vis(any a,any f){
        if (typeid(T)==a.type()){
            any_cast<function<void(T&&)>&&>(f)(any_cast<T&&>(a));
            return 1;
        }
        return 0;
    }
    template<typename T>
    visitable_any


};



int main(){
    auto a=[&](auto q){return q;};
    function<int(int)>f=a;
    function<char(char)>g=a;
}