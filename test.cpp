#include "d"
#include "heap.h"
int LEN;
long*aa;

ima{
	// vector<refdecltype(aa[0])> a;
	// multiset<refdecltype(aa[0])> s;
	// int q;
	// while (1){
	// 	cin>>q;
	// 	ic(q)
	// 	if (q==1){
	// 		int w;
	// 		cin>>w;
	// 		ic(w)
	// 		s.insert(w);
	// 		a.push_back(w);
	// 		PushHeap(a.data(),a.data()+a.size());
	// 	}else
	// 	if (q == 0 and s.size()){
	// 		PopHeap(a.data(),a.data()+a.size());
	// 		auto l=s.end();
	// 		l--;
	// 		assert(*l==a.end()[-1]);
	// 		s.erase(l);
	// 		a.pop_back();
	// 	}else{
	// 		break;
	// 	}
	// 	ic(a)
	// 	ic(s)
	// }
	int n;
	cin>>n;
	vector <int> a(n);
	for (auto &w:a){
		cin>>w;
	}
	auto s=a;
	sort(a.data(),a.data()+a.size());
	sort(s.data(),s.data()+s.size());
	if (a!=s){
		print(a)
		print(s)
	}
	assert(a==s);
}
