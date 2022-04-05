#include "treap.hpp"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void check(T q,T e){
	vector<T> a;
	for (auto w=q;w!=e;++w){
		a.push_back(w);
	}
	a.push_back(e);
	for (size_t w=0;w<a.size();++w){
		for (size_t e=0;e<a.size();++e){
			long d=long(w)-long(e);
			assert(a[w]-a[e]==d);
			assert(w>=e or  a[w]<a[e]);
			assert(w<=e or  a[w]>a[e]);
			assert(w==e or a[w]!=a[e]);
			assert(w>e  or a[w]<=a[e]);
			assert(w<e  or a[w]>=a[e]);
			assert(w!=e or a[w]==a[e]);
			assert(a[w]+(-d)==a[e]);
			assert(a[w]-(d)==a[e]);
		}
	}
	auto s=a;
	s.clear();
	for (auto w=e;w!=q;--w){
		s.push_back(w);
	}
	s.push_back(q);
	reverse(s.begin(),s.end());
	assert(a==s);
}

struct B {int d=0; B(B&&){} explicit B(int f):d(f){} };

int main(){
	treap<long> e({1,2,3,4,5});
	// auto q=treap<string>({"1","2","3"});
	// auto w=q;
	// assert(q==w);
	// assert(vector<string>(q)==vector<string>({"1","2","3"}));
	// assert(q.pop_back()=="3");
	// assert(vector<string>(q)==vector<string>({"1","2"}));
	// assert(q.pop_front()=="1");
	// assert(vector<string>(q)==vector<string>({"2"}));
	// assert(q.pop_front()=="2");
	// assert(vector<string>(q)==vector<string>({}));
	// q.push_back("2");
	// assert(vector<string>(q)==vector<string>({"2"}));
	// w.push_back("4");
	// assert(vector<string>(w)==vector<string>({"1","2","3","4"}));
	// w.push_front("0");
	// assert(vector<string>(w)==vector<string>({"0","1","2","3","4"}));
	// assert(w<q);
	// assert(treap<char>(string("12"))>treap<char>(string("1")));
	// w.insert(0,"-1");
	// assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4"}));
	// w.insert(w.size(),"6");
	// assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","6"}));
	// w.insert(w.size()-1,"5");
	// assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	// assert(vector<string>(w)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	// q.erase(0);
	// assert(q.empty());
	// swap(q,w);
	// assert(w.empty());
	// assert(vector<string>(q)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	// swap(q,w);
	// q.insert(0,"1");
	// q.insert(0,"0");
	// q.insert(2,"2");
	// swap(q,w);
	// assert(vector<string>(q)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	// assert(vector<string>(w)==vector<string>({"0","1","2"}));
	// check(e.begin(),e.end());
<<<<<<< HEAD
	// assert(vector<int>(e)==vector<int>({1,2,3,4,5}));
	// reverse(e.begin(),e.end());
	// assert(vector<int>(e)==vector<int>({5,4,3,2,1}));
	// sort(e.begin(),e.end());
	// assert(vector<int>(e)==vector<int>({1,2,3,4,5}));
	// check(e.begin()-20,e.end()+20);
	// check(e.rbegin(),e.rend());
	// sort(e.rbegin(),e.rend());
	// assert(vector<int>(e)==vector<int>({5,4,3,2,1}));
	// reverse(e.begin(),e.end());
	// assert(vector<int>(e)==vector<int>({1,2,3,4,5}));
	// check(e.rbegin()-20,e.rend()+20);
	// e.clear();
	auto y=e;
=======
	// assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	// reverse(e.begin(),e.end());
	// assert(vector<long>(e)==vector<long>({5,4,3,2,1}));
	// sort(e.begin(),e.end());
	// assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	// check(e.begin()-20,e.end()+20);
	// check(e.rbegin(),e.rend());
	// sort(e.rbegin(),e.rend());
	// assert(vector<long>(e)==vector<long>({5,4,3,2,1}));
	// reverse(e.begin(),e.end());
	// assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	// check(e.rbegin()-20,e.rend()+20);
	// e.clear();
	// auto y=e;
>>>>>>> 69f6a62d480aff0e3345fa4a630df86baa905aeb
	// auto z=e.begin();
	// auto x=e.end();
	// assert(z==x);
	// for (size_t w=0;w<102400;++w){
	// 	e.push_back(w);
	// }
	// for (size_t w=0;w<e.size();++w){
	// 	assert(w==e[w]);
	// }
	// for (size_t w=0;w<102400;++w){
	// 	assert(w==e.pop_front());
	// }
	// assert(e.empty());
	// for (size_t w=0;w<102400;++w){
	// 	e.push_front(w);
	// }
	// reverse(e.begin(),e.end());
	// for (size_t w=0;w<e.size();++w){
	// 	assert(w==e[w]);
	// }
	// reverse(e.rbegin(),e.rend());
	// for (size_t w=0;w<102400;++w){
	// 	assert(w==e.pop_back());
	// }
	// e.resize(102400);
	// assert(e.size()==102400);
	// e.resize(102001);
	// assert(e.size()==102001);
	// for (size_t w=1;w<102001;++w){
	// 	size_t r=1;
	// 	size_t t=w; 
	// 	for (size_t y=1;y<102001;y*=2){
	// 		if (y&(102001-2)){
	// 			r*=t;
	// 			r%=102001;
	// 		}
	// 		t*=t;
	// 		t%=102001;
	// 	}
	// 	e[r]=w;
	// }
	// for (size_t w=1;w<102001;++w){
	// 	size_t r=1;
	// 	size_t t=w; 
	// 	for (size_t y=1;y<102001;y*=2){
	// 		if (y&(102001-2)){
	// 			r*=t;
	// 			r%=102001;
	// 		}
	// 		t*=t;
	// 		t%=102001;
	// 	}
	// 	assert(e[w]==r);
	// }
	// for (size_t w=1;w<102001;++w){
	// 	assert(w*e[w]%102001==1);
	// }
	// z=e.begin();
	// x=e.end();
	// for (size_t w=0;w<102400-102001;++w){
	// 	e.insert(w*250+1,w);
	// }
<<<<<<< HEAD
	// assert(vector<int>(z,x)==vector<int>(e));
=======
	// assert(vector<long>(z,x)==vector<long>(e));
>>>>>>> 69f6a62d480aff0e3345fa4a630df86baa905aeb
	// y=e;
	// for (size_t w=0;w<102400;++w){
	// 	swap(y,e);
	// }
	// swap(y,y);
	// assert(y==e);
	// e.resize(102001);
	// y.resize(e.size());
	// assert(y==e);
	// copy(w.begin(),w.end(),inserter(q,q.begin()+4));
	// assert(vector<string>(q)==vector<string>({"-1","0","1","2","0","1","2","3","4","5","6"}));
	// q=q;
	// assert(vector<string>(q)==vector<string>({"-1","0","1","2","0","1","2","3","4","5","6"}));
	// treap<B> r;
	// r.emplace_back(1);
	// r.emplace_front(2);
	// auto t=r.cut_left(1);
	// assert(t[0].d==2);
	// assert(r[0].d==1);
	// r.clear();
	// t.clear();
	// for (size_t w=0;w<102001;++w){
	// 	r.emplace_back(w);
	// 	t.emplace_back(w);
	// }
	// for (size_t w=0;w<102001;++w){
	// 	assert(r[w].d==t[w].d);
	// 	assert(r[w].d==w);
	// }
	// for (size_t w=0;w<y.size();++w){
	// 	auto q=r.cut_right(51001);
	// 	r.add_left(q);
	// 	assert(r.size()==t.size());
	// 	assert(q.empty());
	// }
	// for (size_t w=0;w<y.size();++w){
	// 	auto q=t.cut_left(51001);
	// 	t.add_right(q);
	// 	assert(t.size()==r.size());
	// 	assert(q.empty());
	// }
	// for (size_t w=0;w<102001;++w){
	// 	assert(r[w].d==t[w].d);
	// 	assert(r[w].d==w);
	// }
	// e.resize(102400);
	// e.resize(102001);
	// y=e;
	// for (size_t w=0;w<y.size();++w){
	// 	auto q=y.cut_right(51001);
	// 	y.add_left(q);
	// 	assert(y.size()==e.size());
	// 	assert(q.empty());
	// }
	// assert(e==y);
	// for (size_t w=0;w<y.size();++w){
	// 	auto q=e.cut_left(51001);
	// 	e.add_right(q);
	// 	assert(e.size()==y.size());
	// 	assert(q.empty());
	// }
	// assert(e==y);
	// for (size_t w=0;w<y.size();++w){
	// 	y.insert(lower_bound(y.begin(),y.begin()+w,y[w]),y[w]);
	// 	y.erase(w+1);
	// }
	// sort(e.begin(),e.end());
	// assert(e==y);
	// assert(q.cut(4,7)==w);
	// assert(vector<string>(q)==vector<string>({"-1","0","1","2","3","4","5","6"}));
	// assert(vector<string>(w)==vector<string>({"0","1","2"}));
	// sort(w.rbegin(),w.rend());
	// assert(vector<string>(w)==vector<string>({"2","1","0"}));
	// q.insert(q.begin(),w);
	// assert(vector<string>(q)==vector<string>({"2","1","0","-1","0","1","2","3","4","5","6"}));
	// assert(vector<string>(w)==vector<string>({}));
<<<<<<< HEAD
	ic(CLOCKS_PER_SEC)
	e.resize(10240);
	for (size_t w=0;w<e.size();++w){
		e[w]=w;
	}
	e.pr(e.e);
	print()
	print()
	print()
	print()
	print()
	print()
	vector<pair<size_t,treap<long>>> a(e.size());
	for (size_t w=0;w<e.size();++w){
		auto t=clock();
		auto q=e.cut_left(w);
		a[w].first=clock()-t;
		e.add_left(q);
		e[w]=a[w].first;
	}
	for (size_t w=0;e.size();++w){
		auto q=e.cut_left(1);
		a[w].second=move(q);
	}
	assert(e.empty());
	sort(a.begin(),a.end());
	for (size_t w=0;w<a.size();++w){
		e.add_right(a[w].second);
	}
	e.pr(e.e);
	print()
	print()
	print()
	print()
	print()
	print()
	for (size_t w=0;w<20;++w){
		// y=e;
		for (size_t w=0;w<e.size();++w){
			auto q=e.cut_left(w);
			auto s=e.cut_left(1);
			e.add_left(q);
			e.add_right(s);
			auto t=clock();
			s=e.cut_right(1);
			a[w].first=clock()-t;
			q=e.cut_left(w);
			e.add_left(s);
			e.add_left(q);
			e[w]=a[w].first;
		}
		// assert(y==e);
		for (size_t w=0;e.size();++w){
			auto q=e.cut_left(1);
			a[w].second=move(q);
		}
		assert(e.empty());
		sort(a.begin(),a.end());
		for (size_t w=0;w<a.size();++w){
			e.add_right(a[w].second);
		}
		e.pr(e.e);
		print()
		print()
		print()
		print()
		print()
	}
=======
	e.resize(20);
	e.out();
>>>>>>> 69f6a62d480aff0e3345fa4a630df86baa905aeb
}
