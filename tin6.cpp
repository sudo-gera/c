#include <bits/stdc++.h>
using namespace std;

int main(){
	long n;
	cin>>n;
	vector<long> a(n);
	for (auto&w: a){
		cin>>w;
	}
	sort(a.begin(),a.end());
	auto t=unique(a.begin(),a.end());
	auto res=a.end()-t;
	res+=res%2;
	cout<<n-res<<endl;
	// long q=2;
	// for (long w=2;w<a.size();w++){
	// 	if (a[q-2]!=a[w]){
	// 		a[q]=a[w];
	// 		q++;
	// 	}
	// }
	// long res=n-q;
	// a.resize(q);
	// long c=0;
	// for (long w=1;w<a.size();w++){
	// 	if (a[w-1]==a[w]){
	// 		c++;
	// 	}
	// }
	// c+=c%2;
	// res+=a.size()-c;
	// cout<<res<<endl;
}
