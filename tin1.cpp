#include <bits/stdc++.h>
using namespace std;

int main(){
	string al;
	cin>>al;
	string rev(256,0);
	for (long w=0;w<al.size();w++){
		rev[al[w]]=w;
	}
	long n ;
	cin>>n ;
	vector<string> a(n);
	for (auto &w:a){
		cin>>w;
		for (auto&e:w){
			e=rev[e];
		}
	}
	sort(a.begin(),a.end());
	for (auto &w:a){
		for (auto&e:w){
			e=al[e];
		}
		cout<<w<<'\n';
	}
}
