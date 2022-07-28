#include "heap.h"
#define customsort heapsort

#include "d"
int main(){
	int n;
	cin>>n;
	vector<__uint64_t> a(n);
	for (auto&w:a){
		cin>>w;
	}
	auto s=a;
	sort(s.begin(),s.end());
	// customsort(&a[0],a.size());
	customsort(a.data(),a.size()+a.data());
	if (a!=s){
		print(a)
		print(s)
		assert(0);
	}
}
