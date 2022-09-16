#include <bits/stdc++.h>
using namespace std;

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

vector<long> a;

long run(long e,long x){
	ic(e,x)
	if (e>2){
		long tmp=(x%a[e-1]+a[e-1])%a[e-1];
		long res=(x-tmp)/a[e-1];
		auto z=run(e-1,x-(res+0)*a[e-1]);
		auto c=run(e-1,x-(res+1)*a[e-1]);
		if (x<0){
			res=abs(res)+min(z+1,c);
		}else{
			res=abs(res)+min(z,c+1);
		}
		ic(res)
		return res;
	}else{
		return abs(x);
	}
}

int main(){
	long n,x;
	cin>>n>>x;
	a.resize(n);
	for (auto &w: a){
		cin>>w;
	}
	cout<<run(a.size(),x)<<endl;
}
