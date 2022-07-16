#include <bits/stdc++.h>
using namespace std;

unsigned int a,b,c=0;

unsigned int nextrand(){
	c=c*a+b;
	return c>>8;
}

int main(){
	long m,q;
	cin>>m>>q;
	cin>>a>>b;
	auto t=new long[(1ULL<<24)+1];
	for (long w=0;w<m;++w){
		long a=nextrand();
		long l=nextrand();
		long r=nextrand();
		if (l>r){
			swap(l,r);
		}
		++r;
		t[l]+=a;
		t[r]-=a;
	}
	long h=t[0];
	t[0]=0;
	for (long w=1;w<(1ULL<<24)+1;++w){
		h+=t[w];
		t[w]=t[w-1]+h-t[w];
	}
	long s=0;
	for (long w=0;w<m;++w){
		long l=nextrand();
		long r=nextrand();
		if (l>r){
			swap(l,r);
		}
		++r;
		s+=t[l];
		s-=t[r];
	}
	cout<<s<<endl;
}
