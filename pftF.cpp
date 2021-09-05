#include <bits/stdc++.h>
using namespace std;
#define int int64_t

template<typename T>
int __print(T q){cout<<q<<" ";return 0;}
template<typename...T>
void cprint(T...q){int w[]={__print(q)...};cout<<endl;}
#define print(...) cout<<"\x1b[92m"<<__LINE__<<"\x1b[0m: ";cprint(__VA_ARGS__);

	int p=1000000007;


int inv(int q){
	int _p=p-2;
	int r=1;
	while (_p){
		if (_p%2){
			r*=q;
			r%=p;}
		_p/=2;
		q*=q;
		q%=p;
		r%=p;}
	return r;}

decltype(0) main(){
	int n,m,l;
	cin>>n>>m>>l;
	vector<int> c({1});
	for (int k=1;k<n+4;k+=1){
		c.push_back(c[c.size()-1]*(n-k+1)%p*inv(k)%p);
	}
	int r=0;
	for(int mk=m;mk<l+m+1;mk+=m){
		if (mk<n+4){
			r+=c[mk];
		}
		r%=p;
	}
	cout<<r<<endl;
}