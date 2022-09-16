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
	long n=getint(),k=getint();
	vector<long> a(n);
	for (auto&w:a){
		cin>>w;
	}
	long z=0;
	long x=a[z]%n;
	while (z!=x){
		z+=a[z];
		z%=n;
		x+=a[x];
		x%=n;
		x+=a[x];
		x%=n;
	}
	long l=1;
	x+=a[z];
	x%=n;
	while (x!=z){
		x+=a[x];
		x%=n;
		l++;
	}
	long s=0;
	long w=0;
	long c=0;
	for (;w<k and c!=z;++w){
		s+=a[c];
		c=s%n;
	}
	long e=w;
	long ls=0;
	c=s%n;
	for (;e<k and e-w<l;++e){
		ls+=a[c];
		c=(s+ls)%n;
	}
	s+=(k-w)/l*ls;
	w+=(k-w)/l*l;
	c=s%n;
	for (;w<k;++w){
		s+=a[c];
		c=s%n;
	}
	print(s);
}
