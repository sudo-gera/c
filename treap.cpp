#include <bits/stdc++.h>
#include "pointer.hpp"
using namespace std;
#define elif else if
#define int int64_t

template <typename t>
struct el{
	t v;
	int w;
	pointer<el> _z=nullptr;
	pointer<el> _x=nullptr;
	int s=1;
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
pointer<el<T>> get_by_index(pointer<el<T>> s,int n){
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
	elif (!(t->z())){
		t->s=t->x()->s+1;
	}
	elif (!(t->x())){
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
pair<pointer<el<T>>,pointer<el<T>>> split(pointer<el<T>> t,int n){
	if (!t){
		return {(pointer<el<T>>)(nullptr),(pointer<el<T>>)(nullptr)};
	}
	elif (!(t->z())){
		if (n<1){
			return {(pointer<el<T>>)(nullptr),t};
		}
		else{
			auto tmp=split(t->x(),n-1);
			t->x(tmp.first);
			auto t2=tmp.second;
			return {t,t2};
		}
	}elif (t->z()->s==n){
		auto t1=t->z();
		t->z((pointer<el<T>>)(0));
		return {t1,t};
	}elif (t->z()->s+1==n){
		auto t2=t->x();
		t->x((pointer<el<T>>)(nullptr));
		return {t,t2};
	}elif (t->z()->s+1<n){
		auto tmp=split(t->x(),n-t->z()->s-1);
		t->x(tmp.first);
		auto t2=tmp.second;
		return {t,t2};
	}elif (t->z()->s>n){
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
	template <typename y=vector<T>>
	treap(y l=vector<T>()){
		for (auto w:l){
			e=merge(e,pointer(el(w)));
		}
	}
	treap(int l){
		for (int w=0;w<l;++w){
			e=merge(e,pointerel(T()));
		}
	}
	treap(const treap&l){
		for (int w=0;w<l.size();++w){
			e=merge(e,pointer(el(l[w])));
		}
	}
	void operator=(const treap&l){
		e=nullptr;
		for (int w=0;w<l.size();++w){
			e=merge(e,pointer(el(l[w])));
		}
	}
	// def __init__(s,l=[],f=[]):
	// 	if isinstance(l,el):
	// 		s.e=l
	// 	elif l==None:
	// 		s.e=l
	// 	else:
	// 		s.f=dict([[w,None] for w in f])
	// 		l=list(l)
	// 		s.e=init(l,0,len(l),f[:])
	// 		# s.e=balance(l,ff=f[:])

	int size()const{
		return e?e->s:0;
	}

	T&operator[](int n){
		if (n<0){
			n+=this->size();
		}
		return get_by_index(e,n)->v;
	}

	T&operator[](int n)const{
		if (n<0){
			n+=this->size();
		}
		return get_by_index(e,n)->v;
	}

	friend int __cmp__(treap s,treap d){
		int min_len=s.size()>d.size()?d.size():s.size();
		for (int w=0;w<min_len;++w){
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


	treap<T> cut(int n){
		auto tmp=split(this->e,n);
		e=tmp.second;
		treap<T> res;
		res.e=tmp.first;
		return res;
	}

	friend ostream&operator<<(ostream&q,treap w){
		auto r=to_list(w.e);
		q<<'[';
		int c=0;
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
};


signed main(){
	cout<<__LINE__<<endl;
	auto q=treap<int>();
	cout<<__LINE__<<endl;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	auto w=q;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	cout<<w<<endl;
	cout<<endl;
}