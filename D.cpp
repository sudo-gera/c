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
    map<string,size_t> a;
    for (size_t q=0;q<n;++q){
        string s=Scan<string>();
        for (auto&w:s){
            w=tolower(w);
        }
        a[s]++;
    }
    vector<pair<size_t,string>> s;
    for (auto&q:a){
        s.push_back({q.second,q.first});
    }
    sort(s.rbegin(),s.rend());
    cout<<s[0].second<<" "<<s[0].first<<endl;
}


