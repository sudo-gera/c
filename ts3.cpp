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

int main(){
    size_t n=0;
    cin>>n;
    string s;
    cin>>s;
    n=s.size();
    vector<size_t> z(n),x(n),c(n),v(n),b(n),m(n);
    iota(z.begin(),z.end(),0);
    iota(x.begin(),x.end(),0);
    iota(c.begin(),c.end(),0);
    iota(v.begin(),v.end(),0);
    iota(b.begin(),b.end(),0);
    iota(m.begin(),m.end(),0);
    if (s[0]!='a'){
        z[0]=-1;
    }
    if (s[0]!='b'){
        x[0]=-1;
    }
    if (s[0]!='c'){
        c[0]=-1;
    }
    if (s[0]!='d'){
        v[0]=-1;
    }
    b[0]=-1;
    m[0]=-1;
    for (size_t q=1;q<n;++q){
        if (s[q]!='a'){
            z[q]=z[q-1];
        }
        if (s[q]!='b'){
            x[q]=x[q-1];
        }
        if (s[q]!='c'){
            c[q]=c[q-1];
        }
        if (s[q]!='d'){
            v[q]=v[q-1];
        }
        b[q]=min({z[q]+1,x[q]+1,c[q]+1,v[q]+1})-1;
        m[q]=b[q]==-1?-1:q-b[q]+1;
    }
    auto _m=m[0];
    for (size_t q=0;q<n;++q){
        _m=min(_m,m[q]);
    }
    cout<<(ssize_t)_m<<endl;
}
