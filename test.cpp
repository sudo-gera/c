#include <bits/stdc++.h>
using namespace std;

struct BaseA
{
    operator uint16_t&();
    operator const uint16_t() const;
};

auto f(const uint16_t&t){
    return 0;
}

int main(){
    sizeof(f(declval<const BaseA&&>()));
}
