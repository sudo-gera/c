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
    map<size_t,pair<size_t,size_t>> a;
    for (size_t q=0;q<n;++q){
        size_t w=Scan<size_t>(), e=Scan<size_t>(), r=Scan<size_t>();
        a[w].first++;
        a[w].second+=r;
    }
    for (auto&q:a){
        cout<<q.first<<" "<<q.second.first<<" "<<q.second.second<<endl;
    }
}


