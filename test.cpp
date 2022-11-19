#include <bits/stdc++.h>
using namespace std;

int main(){
    set<long> s;
    for (long w=0;w<20;++w){
        s.insert(rand());
    }
    vector<decltype(s.begin())> a;
    for (auto w=s.begin();w!=s.end();++w){
        a.push_back(w);
    }
    long start=(long&)(a[0]);
    cout<<"digraph G {"<<endl;
    for (auto&w:a){
        auto y=((long*&)(w));
        for (auto&q:a){
            auto t=((long*&)(q));
            // cout<<((y[0]==(long)(t))?"\x1b[33m#\x1b[0m":"\x1b[31m#\x1b[0m")<<" ";
            if (y[0]==(long)(t)){
                cout<<"    "<<(long)(y)<<" -> "<<(long)(t)<<" [color=red]\n";
            }
        }
        // cout<<"\t";
        for (auto&q:a){
            auto t=((long*&)(q));
            // cout<<((y[1]==(long)(t))?"\x1b[33m#\x1b[0m":"\x1b[31m#\x1b[0m")<<" ";
            if (y[1]==(long)(t)){
                cout<<"    "<<(long)(y)<<" -> "<<(long)(t)<<" [color=green]\n";
            }
        }
        // cout<<"\t";
        for (auto&q:a){
            auto t=((long*&)(q));
            // cout<<((y[2]==(long)(t))?"\x1b[33m#\x1b[0m":"\x1b[31m#\x1b[0m")<<" ";
            if (y[2]==(long)(t)){
                cout<<"    "<<(long)(y)<<" -> "<<(long)(t)<<" [color=blue]\n";
            }
        }
        // cout<<"\t";
        for (auto&q:a){
            auto t=((long*&)(q));
            // cout<<((y[3]==(long)(t))?"\x1b[33m#\x1b[0m":"\x1b[31m#\x1b[0m")<<" ";
            if (y[3]==(long)(t)){
                cout<<"    "<<(long)(y)<<" -> "<<(long)(t)<<" []\n";
            }
        }
        // cout<<endl;
    }
    cout<<"}"<<endl;
}















