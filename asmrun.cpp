#include <bits/stdc++.h>
using namespace std;


extern "C"
uint64_t _c(uint64_t A,uint64_t B,uint64_t C,uint64_t D)
asm ("_c");

int main(){
    cout<<_c(4,6,3,8)<<endl;
}
