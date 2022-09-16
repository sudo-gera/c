#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<long> a;
    while(1){
        long n;
        cin>>n;
        if (n==0){
            break;
        }
        if (n>0){
            a.push_back(n);
        }
        if (n<0 and a.size()){
            a.back()+=n;
            if (a.back()<=0){
                a.pop_back();
            }
        }
    }
    cout<<a.size()<<' '<<(a.size()?a.back():-1)<<endl;
}