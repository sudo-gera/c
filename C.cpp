#include <bits/stdc++.h>
using namespace std;

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
    size_t n=Scan<size_t>();
    vector<long> a(n);
    generate_n(a.begin(),n,Scan<long>());
    sort(a.begin(),a.end());
    a.resize(unique(a.begin(),a.end())-a.begin());
    cout<<a.size()<<endl;
}

