#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define len(q) ((q).size())
decltype(0) main(){
	int n;
	cin>>n;
	vector<int> a;
	for(int w=0;w<n;++w){
		a.push_back(0);
		cin>>a[a.size()-1];
	}
	if (len(a)>0){
		cout<<0<<" ";
	}
	if (len(a)>1){
		cout<<0<<" ";
	}
	int min_index,max_index,global_max_index;
	if (len(a)>2){
		min_index=2;
		max_index=0;
		global_max_index=0;
		cout<<(0>a[max_index]-a[min_index]?0:a[max_index]-a[min_index])<<" ";
	}
	for(int w=3;w<len(a);++w){
		if (a[w-2]>a[global_max_index]){
			global_max_index=w-2;
		}
		if (a[w]<=a[min_index]){
			min_index=w;
		}
		if (a[w-2]-a[w]>=a[max_index]-a[min_index]){
			min_index=w;
			max_index=w-2;}
		if (a[max_index]-a[min_index]<=a[global_max_index]-a[w]){
			max_index=global_max_index;
			min_index=w;}
		cout<<(0>a[max_index]-a[min_index]?0:a[max_index]-a[min_index])<<" ";
	}
	cout<<endl;
}