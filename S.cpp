#include <bits/stdc++.h>
using namespace std;

unsigned int a,b,c=0;

unsigned int nextrand(){
	c=c*a+b;
	return c>>8;
}

int main(){
	unsigned l=(1ULL<<24)+1;
	unsigned m,q;
	cin>>m>>q;
	cin>>a>>b;
	auto t=new unsigned[l]();
	for (unsigned w=0;w<m;++w){
		unsigned a=nextrand();
		unsigned l=nextrand();
		unsigned r=nextrand();
		if (l>r){
			swap(l,r);
		}
		++r;
		t[l]+=a;
		t[r]-=a;
	}
	unsigned h=t[0];
	t[0]=0;
	for (unsigned w=1;w<l;++w){
		h+=t[w];
		t[w]=t[w-1]+h-t[w];
	}
	unsigned s=0;
	for (unsigned w=0;w<m;++w){
		unsigned l=nextrand();
		unsigned r=nextrand();
		if (l>r){
			swap(l,r);
		}
		++r;
		s-=t[l];
		s+=t[r];
	}
	cout<<s<<endl;
}
