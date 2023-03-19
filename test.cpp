#include <bits/stdc++.h>
using namespace std;
int main(){
    std::deque<size_t> a(1);
    cout<<a.size()<<endl;
    a=std::move(a);
    cout<<a.size()<<endl;
}
