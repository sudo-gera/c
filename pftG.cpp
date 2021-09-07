#include <bits/stdc++.h>
using namespace std;
#define int int64_t
	int p=1000000000+9;
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
	int t;
	cin>>t;
	for(int w=0;w<t;w++){
		int r;
		cin>>r;
		cout<<inv(r)<<endl;
	}

// [print(inv(int(input()))) for w in range(int(input()))]




}