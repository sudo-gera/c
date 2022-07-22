#include <bits/stdc++.h>
using namespace std;

struct comm{
  int64_t a[2]={0,0};
};

long getint(){
  long l;
  cin>>l;
  return l;
}

int main(){
  int64_t n=getint(),m=getint();
  auto a=new long[n+2]();
  auto h=new comm[m]();
  long hl=0;
  for (int64_t w=0;w<n;++w){
    auto q=getint();
    auto l=getint();
    auto r=getint()+1;
    auto t=q;
    if (q==1){
      t=getint();
      a[l+1]+=t;
      a[r+1]-=t;
    }else{
      h[hl++]={l,r};
    }
  }
  long t=0;
  for (long w=0;w<n+2;++w){
    t+=a[w];
    a[w]=t;
  }
  t=0;
  for (long w=0;w<n+2;++w){
    t+=a[w];
    a[w]=t;
  }
  for (long w=0;w<hl;++w){
    std::cout<<a[h[w].a[1]]-a[h[w].a[1]]<<'\n';
  }
}