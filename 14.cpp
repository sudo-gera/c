#include <bits/stdc++.h>
using namespace std;


int64_t getint() {
	long h;
	cin>>h;
	return h;
}

void print(int64_t out) {
	cout<<out<<'\n';
}

int main(){
	list<long> a({0});
	long n=getint();
	string s;
	cin>>s;
	auto p=a.end();
	for (long w=0;w<s.size();w++){
		auto q=s[w];
		if (q=='L'){
			--p;
			a.insert(p,w+1);
		}
		if (q=='R'){
			a.insert(p,w+1);
		}
	}
	for (auto w:a){
		cout<<w<<' ';
	}
	cout<<endl;
}
