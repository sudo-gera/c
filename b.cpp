#include <bits/stdc++.h>
using namespace std;

template<typename T=void>
struct Scan{
    template <typename Y = T>
    auto operator()() {
        Y val;
        cin >> val;
        return val;
    }
    template<typename Y=T>
    operator Y(){
        Y val;
        cin>>val;
        return val;
    }
};

int main(){
    vector<long> a;
    long c=0;
    while ((c=Scan<long>())){
        if (c>0){
            a.push_back(c);
        }else if (a.size()){
            if (-c<a.back()){
                a.back()+=c;
            }else{
                a.pop_back();
            }
        }
    }
    cout<<a.size()<<" "<<(a.empty()?-1:a.back())<<endl;
}

