#include <bits/stdc++.h>
using namespace std;

int main(){
	long n;
	cin>>n;
	vector<long> a(n);
	vector<long> b(n);
	vector<long> c(n);
	for (auto&w:a){
		cin>>w;
	}
	for (auto&w:b){
		cin>>w;
	}
	for (auto&w:c){
		cin>>w;
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());
	vector<long> s(n);
	for (long w=0,q=0;w<n;++w){
		while (q < n and a[q]<b[w]){
			++q;
		}
		s[w]=q;
	}
	for (long w=1;w<n;++w){
		s[w]+=s[w-1];
	}
	long res=0;
	for (long w=0,q=0;w<n;++w){
		while (q < n and b[q]<c[w]){
			++q;
		}
		if (q>=1){
			res+=s[q-1];
		}
	}
	cout<<res<<endl;	
}
