#include "d"
#undef ic
#define ic(...)
#include "/Users/gera/Downloads/sort.h"
int LEN;
long*aa;

// struct item{
// 	size_t q;
// 	item(size_t w=0){
// 		q=w;
// 	}
// };

// bool operator<(const item&q,const item&w){
// 	return q.q<w.q;
// }

// bool operator==(const item&q,const item&w){
// 	return q.q==w.q;
// }

ima{
	vector <long>a={6,3,1,2};
	LEN=a.size();
	aa=a.data();
	// Sort(&(a[0]),LEN+&(a[0]));
	// sort(s.begin(),s.end());
	// if (itervect(a+0,a+LEN)!=s){
	// 	print(itervect(a+0,a+LEN))
	// 	print(s)
	// }
	// int n;
	// cin>>n;
	// vector<size_t>a(n);
	// for (auto&w:a){
	// 	cin>>w;
	// 	// w=rand();
	// }
	Sort(&(a[0]),a.size()+&(a[0]));
	vector<refdecltype(a[0])> s(a.begin(),a.end());
	sort(s.begin(),s.end());
	if (a!=s){
		print(a)
		print(s)
		return 1;
	}
}
