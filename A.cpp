#include <bits/stdc++.h>
using namespace std;

#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message XSTR(__cplusplus)

template<typename T=void>
struct Scan{
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
    template<typename Y=T>
    operator Y(){
        Y val;
        cin>>val;
        return val;
    }
};

int main(){
    size_t n=Scan();
    vector<string> a(n);
    generate_n(a.begin(),n,Scan<string>());
    for (auto&q:a){
        for (auto&w:q){
            w=tolower(w);
        }
    }
    sort(a.rbegin(),a.rend());
    a.resize(unique(a.begin(),a.end())-a.begin());
    for (auto&q:a){
        cout<<q<<" ";
    }
    cout<<endl;
}
