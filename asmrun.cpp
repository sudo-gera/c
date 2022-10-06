#include <bits/stdc++.h>
using namespace std;


extern "C"
uint64_t _c(uint64_t A,uint64_t B,uint64_t C,uint64_t D)
asm ("_c");

int main(){
    // while (1){
    //     int a=rand()%2?rand():-1*(int)rand();
    //     int b=rand()%2?rand():-1*(int)rand();
    //     int c=rand()%2?rand():-1*(int)rand();
    //     int x=rand()%2?rand():-1*(int)rand();
    //     int d=-(a*x*x*x+b*x*x+c*x);
    //     x=solve(a,b,c,d);
    //     assert(d==-(a*x*x*x+b*x*x+c*x));
    //     for (int w=0;w<x;++w){
    //         assert(!(d==-(a*w*w*w+b*w*w+c*w)));
    //     }
    // }
    // cout<<solve(1,1,0,-27-9)<<endl;
    // cout<<_c(1,2,3,4)<<endl;
    _c(1,2,3,4);
}