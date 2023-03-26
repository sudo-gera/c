#include <bits/stdc++.h>
using namespace std;
int main(){
    deque<int> d({1,2,3});
    d=std::move(d);
    cout<<d.size()<<endl;
}