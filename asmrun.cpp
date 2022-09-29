#include <bits/stdc++.h>
using namespace std;


extern "C"
int solve(int64_t A, int B, int C, int D)
asm ("solve");

int main(){
    while (1){
        int a=rand()%2?rand():-1*(int)rand();
        int b=rand()%2?rand():-1*(int)rand();
        int c=rand()%2?rand():-1*(int)rand();
        int x=rand()%2?rand():-1*(int)rand();
        int d=-(a*x*x*x+b*x*x+c*x);
        x=solve(a,b,c,d);
        assert(d==-(a*x*x*x+b*x*x+c*x));
        for (int w=0;w<x;++w){
            assert(!(d==-(a*w*w*w+b*w*w+c*w)));
        }
    }
    // cout<<solve(1,1,0,-27-9)<<endl;
}