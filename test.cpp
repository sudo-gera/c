// int LEN;
// int*aa;
#include "d"
#include "sort.h"

struct item{
	size_t q;
	item(size_t w=0){
		q=w;
	}
};

bool operator<(const item&q,const item&w){
	return q.q<w.q;
}

// bool operator==(const item&q,const item&w){
// 	return q.q==w.q;
// }

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
	vector<item>a(n);
	for (auto&w:a){
		w=rand();
	}
	Sort(&(a[0]),a.size()+&(a[0]));
	vector<refdecltype(a[0])> s(a.begin(),a.end());
	sort(s.begin(),s.end());
	// if (a!=s){
	// 	print(time())
	// }
}
