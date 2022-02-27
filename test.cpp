// int LEN;
// int*aa;
#include "d"
#include "sort.h"

ima{
	// int a[]={2,3,0,3,2,7,4,7,5,4,7,4,7,4,8,9,4,2,7,0,4,6,8,8};
	// LEN=sizeof(a)/sizeof(a[0]);
	// vector<int> s(a,a+LEN);
	// aa=a;
	// Sort(&(a[0]),LEN+&(a[0]));
	// sort(s.begin(),s.end());
	// if (itervect(a+0,a+LEN)!=s){
	// 	print(itervect(a+0,a+LEN))
	// 	print(s)
	// }
	int n;
	cin>>n;
	vector<size_t>a(n);
	for (auto&w:a){
		cin>>w;
	}
	Sort(&(a[0]),a.size()+&(a[0]));
	vector<size_t> s(a.begin(),a.end());
	sort(s.begin(),s.end());
	if (a!=s){
		print(time())
	}
}
