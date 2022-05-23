#ifdef assert_m
#undef assert
#define assert assert_m
#endif
#include "treap.hpp"
// #include <bits/stdc++.h>
#include <vector>
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
	long sr=1653272014;
	sr=time(0);
	std::cout<<"seed = "<<sr<<std::endl;
	srand(sr);
	treap<long> e({1,2,3,4,5});
	auto y=e;

	auto q=treap<long>({1,2,3});
	auto w=q;
	assert(q==w);
	assert(vector<long>(q)==vector<long>({1,2,3}));
	assert(q.pop_back()==3);
	assert(vector<long>(q)==vector<long>({1,2}));
	assert(q.pop_front()==1);
	assert(vector<long>(q)==vector<long>({2}));
	assert(q.pop_front()==2);
	assert(vector<long>(q)==vector<long>({}));
	q.push_back(2);
	assert(vector<long>(q)==vector<long>({2}));
	w.push_back(4);
	assert(vector<long>(w)==vector<long>({1,2,3,4}));
	w.push_front(0);
	assert(vector<long>(w)==vector<long>({0,1,2,3,4}));
	assert(w<q);
	assert(treap<long>(long(12))>treap<long>(long(1)));
	w.insert(0,-1);
	assert(vector<long>(w)==vector<long>({-1,0,1,2,3,4}));
	w.insert(w.size(),6);
	assert(vector<long>(w)==vector<long>({-1,0,1,2,3,4,6}));
	w.insert(w.size()-1,5);
	assert(vector<long>(w)==vector<long>({-1,0,1,2,3,4,5,6}));
	assert(vector<long>(w)==vector<long>({-1,0,1,2,3,4,5,6}));
	q.erase(0);
	assert(q.empty());
	swap(q,w);
	assert(w.empty());
	assert(vector<long>(q)==vector<long>({-1,0,1,2,3,4,5,6}));
	swap(q,w);
	q.insert(0,1);
	q.insert(0,0);
	q.insert(2,2);
	swap(q,w);
	assert(vector<long>(q)==vector<long>({-1,0,1,2,3,4,5,6}));
	assert(vector<long>(w)==vector<long>({0,1,2}));

	check(e.begin(),e.end());
	assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	e.rev();
	assert(vector<long>(e)==vector<long>({5,4,3,2,1}));
	e.rev();
	assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	check(e.begin()-20,e.end()+20);
	check(e.rbegin()-20,e.rend()+20);
	e.rev();
	assert(vector<long>(e)==vector<long>({5,4,3,2,1}));
	e.rev();
	assert(vector<long>(e)==vector<long>({1,2,3,4,5}));
	check(e.rbegin()-20,e.rend()+20);
	y=e;
	for (size_t w=0;w<e.size();w++){
		auto t=e.cut_left(1);
		e.add_left(t);
		assert(e.size()==y.size());
	}
	assert(y==e);
	for (size_t w=0;w<e.size();w++){
		auto t=e.cut_right(1);
		e.add_right(t);
		assert(e.size()==y.size());
	}
	assert(y==e);
	for (size_t w=0;w<e.size();w++){
		auto t=e.cut_right(1);
		e.add_left(t);
		assert(e.size()==y.size());
	}
	assert(y==e);
	for (size_t w=0;w<e.size();w++){
		auto t=e.cut_left(1);
		e.add_right(t);
		assert(e.size()==y.size());
	}
	assert(y==e);
	e.clear();
	y=e;
	assert(e==y);
	auto z=e.begin();
	auto x=e.end();
	assert(z==x);


	for (size_t w=1;w<509;++w){
		size_t r=1;
		size_t t=w; 
		for (size_t y=1;y<509;y*=2){
			if (y&(509-2)){
				r*=t;
				r%=509;
			}
			t*=t;
			t%=509;
		}
		e.push_back(r);
	}
	for (uint64_t w=0;w<e.size();++w){
		assert(e[w]*(w+1)%509==1);
	}

	for (uint64_t w=0;w<e.size();++w){
		auto p=lower_bound(e.begin(),e.begin()+w,e[w])-e.begin();
		auto z=e.cut_left(w+1);
		auto x=z.cut_left(p);
		z.rev();
		x.add_right(z);
		z=x.cut_left(p+1);
		x.rev();
		x.add_left(z);
		e.add_left(x);
	}
	e.push_front(0);
	for (uint64_t w=0;w<e.size();++w){
		assert(e[w]==w);
	}

	e.clear();
	for (size_t w=1;w<509;++w){
		size_t r=1;
		size_t t=w; 
		for (size_t y=1;y<509;y*=2){
			if (y&(509-2)){
				r*=t;
				r%=509;
			}
			t*=t;
			t%=509;
		}
		e.push_back(r);
	}

	y=e;

	for (uint64_t w=0;w<e.size();++w){
		auto a=e.cut_left(w);
		auto p=a.lower_bound(e[0])-a.begin();
		e.add_left(a);
		auto z=e.cut_left(w+1);
		auto x=z.cut_left(p);
		z.rev();
		x.add_right(z);
		z=x.cut_left(p+1);
		x.rev();
		x.add_left(z);
		e.add_left(x);
	}
	e.push_front(0);
	for (uint64_t w=0;w<e.size();++w){
		assert(e[w]==w);
	}

	e=y;

	for (uint64_t w=0;w<e.size();++w){
		auto s=e.cut_left(w);
		e.add(-e[0]);
		e.add_left(s);
	}

	for (uint64_t w=0;w<e.size();++w){
		assert(e[w]==0);
	}

	for (uint64_t w=0;w<e.size();++w){
		auto s=e.cut_left(w);
		e.add(1);
		e.add_left(s);
	}

	for (uint64_t w=0;w<e.size();++w){
		assert(e[w]==w+1);
	}

	e.mul(0);

	// py_func(r,{
	// def r():
	// 	return '-'*9999
	// })
	// ic(r())

	// e=y;

	y=e;
	// ic(e,y)

	auto g=vector<long>(e.begin(), e.end());
	for (uint64_t w=0;w<50;++w){
		assert(e.next_permutation()==next_permutation(g.begin(),g.end()));
		assert(vector<long>(e)==g);
	}
	for (uint64_t w=0;w<50;++w){
		assert(e.prev_permutation()==prev_permutation(g.begin(),g.end()));
		assert(vector<long>(e)==g);
	}
	assert(g==vector<long>(y));
	assert(e==y);



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
	// 	e.insert(w*2509+1,w);
	// }
	// assert(vector<long>(z,x)==vector<long>(e));
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
	// assert(vector<long>(q)==vector<long>({-1,0,1,2,0,1,2,3,4,5,6}));
	// q=q;
	// assert(vector<long>(q)==vector<long>({-1,0,1,2,0,1,2,3,4,5,6}));

	// treap<B> r;
	// r.emplace_back(1);
	// assert(r[0].d==1);
	// r.emplace_front(2);
	// assert(r[0].d==2);
	// assert(r[1].d==1);
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
	// assert(vector<long>(q)==vector<long>({-1,0,1,2,3,4,5,6}));
	// assert(vector<long>(w)==vector<long>({0,1,2}));
	// sort(w.rbegin(),w.rend());
	// assert(vector<long>(w)==vector<long>({2,1,0}));
	// q.insert(q.begin(),w);
	// assert(vector<long>(q)==vector<long>({2,1,0,-1,0,1,2,3,4,5,6}));
	// assert(vector<long>(w)==vector<long>({}));
	// q.rev();
	// w=q.cut_right(3);
	// w.rev();
	// assert(vector<long>(w)==vector<long>({2,1,0}));
	// q.rev();
	// assert(vector<long>(q)==vector<long>({-1,0,1,2,3,4,5,6}));
	// q.add_left(w);
	// assert(vector<long>(q)==vector<long>({2,1,0,-1,0,1,2,3,4,5,6}));
	// for (uint64_t t=0;t<q.size();++t){
	// 	q.rev();
	// 	w=q.cut_left(5);
	// 	q.rev();
	// 	w.rev();
	// 	q.add_left(w);
	// }	
	// assert(vector<long>(q)==vector<long>({2,1,0,-1,0,1,2,3,4,5,6}));
	// q.rev();
	// w=q;
	// q.rev();
	// w.rev();
	// assert(q==w);
	// w.rev();
	// for (uint64_t t=0;t<q.size();++t){
	// 	assert(q[t*5%q.size()]==w[w.size()-1-t*5%w.size()]);
	// }
	// assert(vector<long>(q)==vector<long>({2,1,0,-1,0,1,2,3,4,5,6}));

	// e.resize(102001);
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
	// for (uint64_t t=0;t<e.size();++t){
	// 	e.rev();
	// 	y=e.cut_left(51001);
	// 	e.rev();
	// 	y.rev();
	// 	e.add_left(y);
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
	// sort(e.begin(),e.end());
	// y=e;
	// sort(e.rbegin(),e.rend());
	// e.rev();	
	// y.rev();
	// sort(y.begin(),y.end());
	// assert(y==e);

	// e.clear();
	// y.clear();
	// assert(e.is_forward());
	// assert(y.is_forward());
	// assert(e.is_backward());
	// assert(y.is_backward());
	// e.push_back(0);
	// assert(e.is_forward());
	// assert(e.is_backward());
	// e.push_back(1);
	// assert(e.is_forward());
	// assert(!e.is_backward());
	// e.push_back(2);
	// assert(e.is_forward());
	// assert(!e.is_backward());
	

	// e.clear();
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
	// 	e.push_back(r);
	// }
	// assert(!e.is_forward());
	// assert(!e.is_backward());
	// y=e;
	// for (size_t w=0;w<y.size();++w){
	// 	y.insert(lower_bound(y.begin(),y.begin()+w,y[w]),y[w]);
	// 	y.erase(w+1);
	// }
	// assert(y.is_forward());
	// assert(!y.is_backward());
	// y.resize(20);
	// assert(y.is_forward());
	// assert(!y.is_backward());
	// y.rev();
	// assert(!y.is_forward());
	// assert(y.is_backward());

	// e.clear();
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
	// 	e.push_back(r);
	// }
	// y=e;
	// for (size_t w=0;w<y.size();++w){
	// 	auto d=y.cut_left(w);
	// 	long p=0;
	// 	p=d.lower_bound(y[0])-d.begin();
	// 	y.add_left(d);
	// 	auto s=y.cut_left(w+1);
	// 	auto a=s.cut_left(p);
	// 	assert(a.is_forward());
	// 	s.rev();
	// 	a.add_right(s);
	// 	s=a.cut_left(p+1);
	// 	assert(s.is_forward());
	// 	assert(a.is_backward());
	// 	a.rev();
	// 	assert(a.is_forward());
	// 	a.add_left(s);
	// 	y.add_left(a);
	// }
	// assert(y.is_forward());
	// assert(vector<long>(q)==vector<long>({2,1,0,-1,0,1,2,3,4,5,6}));
	// w=q.cut_left(6);
	// bool f=1;
	// vector<long> g(w.begin(),w.end());
	// while (f){
		// f=next_permutation(g.begin(),g.end());
		// assert(f==w.next_permutation());
		// assert(g==vector<long>(w));
	// }
	// assert(w.is_forward());
	// q.add_left(w);
	// w=q.cut_left(8);
	// while(w.next_permutation()){}
	// assert(w.is_forward());
	// q.add_left(w);
	// e.clear();
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
	// 	e.push_back(r);
	// }
	// for (uint64_t w=0;w<e.size();++w){
	// 	e.next_permutation();
	// }
	// vector<long> h(e.begin(),e.end());
	// for (uint64_t w=0;w<9;++w){
	// 	assert(next_permutation(h.begin(),h.end())==e.next_permutation());
	// 	assert(h==vector<long>(e));
	// }
	// q.next_permutation();
	// q.next_permutation();
	// q.next_permutation();
	// q.next_permutation();
	// w=q;
	// q.next_permutation();
	// q.prev_permutation();
	// assert(w==q);
	// w=q.cut_left(6);
	// w.prev_permutation();
	// g=vector<long>(w.begin(),w.end());
	// while (f){
		// f=prev_permutation(g.begin(),g.end());
		// assert(f==w.prev_permutation());
		// assert(g==vector<long>(w));
	// }
	// assert(w.is_backward());
	// h=vector<long> (e.begin(),e.end());
	// for (uint64_t w=0;w<9;++w){
	// 	assert(prev_permutation(h.begin(),h.end())==e.prev_permutation());
	// 	assert(h==vector<long>(e));
	// }
	// for (uint64_t w=0;w<e.size();++w){
	// 	e.prev_permutation();
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
	// 	assert(e[w-1]==r);
	// }
	// assert(e.sum()==5202051000);
	// e.mul(2);
	// assert(e.sum()==5202051000*2);
	// e.add(3);
	// assert(e.sum()==e.size()*3+5202051000*2);


	// for (uint64_t w=0;w<e.size();++w){
	// 	e.insert(lower_bound(e.begin(),e.begin()+w,e[w]),e[w]);
	// 	e.erase(w+1);
	// }
	// assert(e.is_forward());

	// e.resize(0);
	// for (uint64_t w=0;w<12;++w){
	// 	e.push_back(w);
	// }

	// for (uint64_t w=0;w<9;++w){
	// 	auto z=e.cut_left(rand()%e.size());
	// 	auto x=e.cut_left(rand()%e.size());
	// 	x.mul(-1);
	// 	x.rev();
	// 	if (x.size()){
	// 		x.add(-x[x.size()-1]-x[0]);
	// 	}
	// 	e.add_left(x);
	// 	e.add_left(z);
	// 	assert(e.is_forward());
	// }



	// e.resize(1'234'567);
	// e.out();
	// cout<<e.e->d<<endl;
}
