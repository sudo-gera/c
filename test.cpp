#include <bits/stdc++.h>
using namespace std;


int main(){
    set<vector<int>> s;
    for (long w=0;w<20;++w){
        s.insert({rand()});
    }
    vector<decltype(s.begin())> a;
    for (auto w=s.begin();w!=s.end();++w){
        a.push_back(w);
    }
    long start=(long&)(a[0]);
    for (auto&w:a){
        long z=(long&)(w)-start;
        long x=(long)(&*w)-start;
        cout<<z<<" "<<x<<" "<<z-x<<endl;
    }

}















