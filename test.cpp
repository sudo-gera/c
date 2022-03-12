#include <iostream>
#include <iterator>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;
#include <bits/stdc++.h>
using namespace std;
#include "pointer.hpp"


int qq=0;
class test{
public:
	int q;
	test(){
		q=++qq;
		cout<<"constructor "<<q<<endl;
	}
	template<typename T>
	test(T w){
		q=++qq;
		cout<<"constructor "<<q<<" with "<<w<<endl;
	}
	test(const test&w){
		q=++qq;
		cout<<"constructor "<<q<<" from "<<w.q<<endl;
	}
	template<typename T>
	void operator=(T w){
		cout<<"assign "<<q<<" with "<<w<<endl;
	}
	void operator=(const test&w){
		cout<<"assign "<<q<<" from "<<w.q<<endl;
	}
	~test(){
		cout<<"destructor "<<q<<endl;		
	}
};

template <typename Y>
void ___mergesort(Y qb,Y qe,pointer<vector<typename Y::value_type>> _a=nullptr){
	using T=typename Y::value_type;
	// using T=vector<decltype(qb[0])>;
	// T*a=(T*)_a;
	if (qe-qb<2){
		return;
	}
	bool outs=0;
	if (!_a){
		// a=new T[qe-qb];
		_a=vector<T>(qe-qb);
		outs=1;
	}
	vector<T>&a=*_a;
	___mergesort(qb,qb+(qe-qb)/2,_a);
	___mergesort(qb+(qe-qb)/2,qe,_a);
	size_t asize=0;
	size_t lp=0;
	size_t rp=(qe-qb)/2;
	while (lp<(qe-qb)/2 or rp<(qe-qb)){
		if (lp==(qe-qb)/2){
			a[asize++]=qb[rp++];
		}else
		if (rp==(qe-qb)){
			a[asize++]=qb[lp++];
		}else
		if (qb[lp]>qb[rp]){
			a[asize++]=qb[rp++];
		}else{
			a[asize++]=qb[lp++];
		}
	}
	for (size_t w=0;w<asize;++w){
		qb[w]=a[w];
	}
	if (outs){
		// delete a;
	}
}


// #include <bits/stdc++.h>
// #include "pointer.hpp"
using namespace std;

template <typename t>
struct el{
	t v;
	int64_t w;
	pointer<el> _z=nullptr;
	pointer<el> _x=nullptr;
	int64_t s=1;
	el(t _v){
		v=_v;
		w=rand();
	}

	pointer<el> z(){
		return _z;
	}
	template<typename y>
	void z(y q){
		_z=q;
		update(this);
	}

	pointer<el> x(){
		return _x;
	}
	template<typename y>
	void x(y q){
		_x=q;
		update(this);
	}
};

template<typename T>
pointer<el<T>> get_by_index(pointer<el<T>> s,int64_t n){
	if (!s){
		cout<<__LINE__<<" ValueError"<<endl;
		return (pointer<el<T>>)(nullptr);
	}
	if (!(s->z())){
		if (n==0){
			return s;
		}
		else{
			return get_by_index(s->x(),n-1);
		}
	}
	else{
		if (n==s->z()->s){
			return s;
		}
		if (n<s->z()->s){
			return get_by_index(s->z(),n);
		}
		if (n>s->z()->s){
			return get_by_index(s->x(),n-s->z()->s-1);
		}
	}
	cout<<__LINE__<<" unexpected exit"<<endl;
	return (pointer<el<T>>)(nullptr);
}


template <typename T>
void update(el<T>*t){
	if (!(t->z()) and !(t->x())){
		t->s=1;
	}
	else if (!(t->z())){
		t->s=t->x()->s+1;
	}
	else if (!(t->x())){
		t->s=t->z()->s+1;
	}else{
		t->s=t->z()->s+t->x()->s+1;
	}
}

template<typename T>
vector<T> to_list(pointer<el<T>> q){
	if (!q){
		return vector<T>();
	}
	auto r=to_list(q->z());
	auto t=vector({q->v});
	r.insert(r.end(),t.begin(),t.end());
	t=to_list(q->x());
	r.insert(r.end(),t.begin(),t.end());
	return r;
}

// template<typename T>
// void print(pointer<el<T>> q){
// 	auto w=to_list(q);
// 	for (auto w:w){
// 		cout<<w<<" ";
// 	}
// 	cout<<endl;
// }

template<typename T>
pointer<el<T>> merge(pointer<el<T>> t1,pointer<el<T>> t2){

	if (!t1){
		return t2;
	}
	if (!t2){
		return t1;
	}
	if (t1->w<t2->w){
		t2->z(merge(t1,t2->z()));
		return t2;
	}else{
		t1->x(merge(t1->x(),t2));
		return t1;
	}
}

template <typename T>
pair<pointer<el<T>>,pointer<el<T>>> split(pointer<el<T>> t,int64_t n){
	if (!t){
		return {(pointer<el<T>>)(nullptr),(pointer<el<T>>)(nullptr)};
	}
	else if (!(t->z())){
		if (n<1){
			return {(pointer<el<T>>)(nullptr),t};
		}
		else{
			auto tmp=split(t->x(),n-1);
			t->x(tmp.first);
			auto t2=tmp.second;
			return {t,t2};
		}
	}else if (t->z()->s==n){
		auto t1=t->z();
		t->z((pointer<el<T>>)(0));
		return {t1,t};
	}else if (t->z()->s+1==n){
		auto t2=t->x();
		t->x((pointer<el<T>>)(nullptr));
		return {t,t2};
	}else if (t->z()->s+1<n){
		auto tmp=split(t->x(),n-t->z()->s-1);
		t->x(tmp.first);
		auto t2=tmp.second;
		return {t,t2};
	}else if (t->z()->s>n){
		auto tmp=split(t->z(),n);
		auto t1=tmp.first;
		t->z(tmp.second);
		return {t1,t};
	}
	cout<<__LINE__<<" unexpected exit"<<endl;
	return {(pointer<el<T>>)(0),(pointer<el<T>>)(0)};
}


template <typename T>
struct treap{
	pointer<el<T>> e=nullptr;
	treap(vector<T> l=vector<T>()){
		for (auto w:l){
			e=merge(e,pointer(el(w)));
		}
	}
	treap(int64_t l){
		for (int64_t w=0;w<l;++w){
			e=merge(e,pointerel(T()));
		}
	}
	treap(const treap&l){
		for (int64_t w=0;w<l.size();++w){
			e=merge(e,pointer(el(l[w])));
		}
	}
	void operator=(const treap&l){
		e=nullptr;
		for (int64_t w=0;w<l.size();++w){
			e=merge(e,pointer(el(l[w])));
		}
	}
	
	uint64_t size()const{
		return e?e->s:0;
	}

	T&operator[](uint64_t n){
		return get_by_index(e,n)->v;
	}

	T&operator[](uint64_t n)const{
		return get_by_index(e,n)->v;
	}

	friend int64_t __cmp__(treap s,treap d){
		int64_t min_len=s.size()>d.size()?d.size():s.size();
		for (int64_t w=0;w<min_len;++w){
			if (s[w]<d[w]){
				return -1;
			}
			if (s[w]>d[w]){
				return -1;
			}
		}
		if (s.size()>d.size()){
			return 1;
		}
		if (s.size()<d.size()){
			return -1;
		}
		return 0;
	}

	bool operator<(const treap o)const{
		return __cmp__(*this,o)<0;
	}

	void operator+=(treap o){
		e=merge(e,o.e);
	}

	void clear(){
		e->clear();
	}

	void push_back(T a){
		e=merge(e,pointer(el(a)));
	}

	template<typename...Y>
	void emplace_back(const Y&...a){
		push_back(T(a...));
	}

	treap<T> cut(int64_t n){
		auto tmp=split(this->e,n);
		e=tmp.second;
		treap<T> res;
		res.e=tmp.first;
		return res;
	}

	friend ostream&operator<<(ostream&q,treap w){
		auto r=to_list(w.e);
		q<<'[';
		int64_t c=0;
		for (auto w:r){
			if (c){
				q<<", "<<w;
			}else{
				q<<w;
				c=1;
			}
		}
		q<<']';
		return q;
	}
	class iter {
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;
		long a=0;
		treap<T>*base;
		iter(treap<T>*b):base(b){}
		T&operator*(){
			return base[0][a];
		}
		auto&operator--(){
			--a;
			return *this;
		}
		auto&operator++(){
			++a;
			return *this;
		}
		auto&operator+=(long w){
			a+=w;
			return *this;
		}
		auto&operator-=(long w){
			a-=w;
			return *this;
		}
		auto&operator[](long q){
			return base[0][a+q];
		}
		auto&operator=(const iter&e){
			a=e.a;
			base=e.base;
			return *this;
		}
	};
	auto begin(){
		return iter(this);
	}
	auto end(){
		return iter(this)+this->size();
	}
};

template<typename TT>
auto operator-(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,ptrdiff_t>{
	return q.a-w.a;
}

template<typename TT>
auto operator+(TT q,long w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator-(TT q,long w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,TT>{
	auto e=q;
	e-=w;
	return e;
}

template<typename TT>
auto operator+(long w,TT q)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator==(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a==w.a;
}

template<typename TT>
auto operator>=(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a>=w.a;
}

template<typename TT>
auto operator<=(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a<=w.a;
}

template<typename TT>
auto operator<(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a<w.a;
}

template<typename TT>
auto operator>(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a>w.a;
}

template<typename TT>
auto operator!=(TT q,TT w)->enable_if_t<is_same_v<typename treap<typename TT::value_type>::iter,TT>,bool>{
	return q.a!=w.a;
}

treap<long> aa({9,8,7,6,5,4,3,2,1});


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


int main(){
	// ic(aa)
	// for (auto w=a.begin();w!=a.begin()+(a.end()-a.begin())/2;++w){
	// 	auto e=a.end()-1-(w-a.begin());
	// 	swap(*w,*e);
	// }
	// assert(a.begin()<a.begin()+1);
	sort(aa.begin(),aa.end());
	// ic(aa)
}
