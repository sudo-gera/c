#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<size_t> a(20);
    while (a.capacity()==a.size()){
        a.push_back(1);
    }
    cout<<a.data()[a.size()]<<endl;
}

