#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<long> a;
    while (a.capacity()==a.size()){
        a.push_back(0);
    }
    cout<<a.end()[0]<<endl;
}
