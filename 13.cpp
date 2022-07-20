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
	multiset<long> a;
	long n=getint();
	for (size_t w=0;w<n;++w){
		long k,q=getint(),x=getint();
		if (q==1){
			a.insert(x);
		}
		if (q==2){
			k=getint();
			auto q=a.upper_bound(x);
			for (size_t i=0;i<k;i++){
				if (q==a.begin()){
					print(-1);
					goto _1;
				}
				--q;
			}
			print(*q);
		}
		_1:
		if (q==3){
			k=getint();
			--k;
			auto q=a.lower_bound(x);
			for (size_t i=0;i<k;i++){
				++q;
				if (q==a.end()){
					print(-1);
					goto _2;
				}
			}
			print(*q);
		}
		_2:
		{}
	}
}
