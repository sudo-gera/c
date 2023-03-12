#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <cassert>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <cstring>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <queue>
#include <stack>

using namespace std;

#define none 9000000000000000000

int main(){
    size_t n=0;
    cin>>n;
    vector<ssize_t> a(n);
    for (size_t q=0;q<n;++q){
        cin>>a[q];
    }
    // ic(a)
    vector<ssize_t> s(n+1);
    vector<pair<ssize_t,size_t>> d(n+1);
    d[0]={0,0};
    for (size_t q=0;q<n;++q){
        s[q+1]=s[q]+a[q];
        d[q+1]={s[q+1],q+1};
    }
    // ic(s)
    sort(d.begin(),d.end());
    // ic(d)
    vector<size_t> f(n,none);
    for (size_t q=0;q<n;++q){
        pair tmp=pair{s[q+1],q+1};
        auto ptr=lower_bound(d.begin(),d.end(),tmp)-d.begin();
        assert(ptr!=n+1);
        ptr-=1;
        if (ptr!=-1 and d[ptr].first==tmp.first){
            f[q]=q+1-d[ptr].second;
        }
    }
    // ic(f)
    vector<size_t> g(n,none);
    if (a[0]==0){
        g[0]=0;
    }
    for (size_t q=1;q<n;++q){
        if (g[q-1]!=none){
            g[q]=g[q-1]+1;
        }
        g[q]=min(g[q],f[q]);
    }
    // ic(g)
    for (size_t q=0;q<n;++q){
        if (g[q]!=none){
            g[q]=q+2-g[q];
        }else{
            g[q]=0;
        }
    }
    // ic(g)
    size_t sum=0;
    for (size_t q=0;q<n;++q){
        sum+=g[q];
    }
    cout<<sum<<endl;
}
