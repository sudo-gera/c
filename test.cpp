#include <bits/stdc++.h>
using namespace std;

#define pline_ std::cout<<"\x1b[32m"<<__LINE__<<"\x1b[0m";
#define pline pline_ std::cout<<std::endl;

#define print(...) pline_;cout<<": ";print_f(__VA_ARGS__);cout<<endl;
template <typename t>
int print_ff(t a){cout<<a<<' ';return 1;}
template <typename...t>
void print_f(t...a){int s[]={1,print_ff(a)...};}

#include"pointer.cpp"


int main(){
}