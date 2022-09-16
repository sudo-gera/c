#include <bits/stdc++.h>
using namespace std;
int main(){
    long n;
    cin>>n;
    vector<string> a(n);
    for (long w=0;w<n;++w){
        cin>>a[w];
        for (auto&e:a[w]){
            e=tolower(e);
        }
    }
    sort(a.rbegin(),a.rend());
    a.resize(unique(a.begin(),a.end())-a.begin());
    for (auto&w:a){
        cout<<w<<' ';
    }
    cout<<endl;
}