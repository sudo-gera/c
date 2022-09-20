#include <bits/stdc++.h>
using namespace std;
int main(){
    long n;
    cin>>n;
    vector<long> a(n);
    for (auto&w:a){
        cin>>w;
    }
    sort(a.begin(),a.end());
    a.resize(unique(a.begin(),a.end())-a.begin());
    cout<<a.size()<<endl;
}