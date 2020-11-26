#include <bits/stdc++.h>
using namespace std;
auto slice__(auto d,auto f=0,auto g=0){
	auto s=d.size();
	if (f<0){
		f+=s;
	}
	if (g>0){
		g-=s;
	}
	return decltype(d)(d.begin()+f,d.end()+g);
}
int main(){
	cout<<<<endl;
}