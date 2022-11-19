#include <bits/stdc++.h>
using namespace std;

template <auto n>
concept and1  = bool(n &  1LLU);

                template <auto n>
                concept and2  = bool(n &  2LLU);

                                template <auto n>
                                concept and4  = bool(n &  4LLU);

                                                template <auto n>
                                                concept and8  = bool(n &  8LLU);

        template<auto n>
        concept and3  = and1<n>  and and2<n>;

                        template<auto n>
                        concept and6  = and2<n>  and and4<n>;

                                        template<auto n>
                                        concept and12 = and4<n>  and and8<n>;

                        template<auto n>
                        concept and15 = and3<n>  and and12<n>;



template<auto n>
requires and15<n>
auto f(){
    cout<<15<<endl;
}

template<auto n>
requires and6 <n>
auto f(){
    cout<<6 <<endl;
}


int main(){
    f<15>();
}
