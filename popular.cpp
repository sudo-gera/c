#include <bits/stdc++.h>
using namespace std;
int main(){
    long n;
    cin>>n;
    vector<string> a(n);
    for (auto&w:a){
        cin>>w;
        for (auto&e:w){
            e=tolower(e);
        }
    }
    sort(a.begin(),a.end());
    long max_i=0;
    auto max_v=a[0];
    long i;
    for (auto&w :a){
        if ((i=count(a.begin(),a.end(),w))>max_i){
            max_i=i;
            max_v=w;
        }
    }
    cout<<max_v<<' '<<max_i<<endl;
}