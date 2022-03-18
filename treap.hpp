#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename t>
struct el{
	t v;
	int64_t w;
	el* _z=nullptr;
	el* _x=nullptr;
	el* _p=nullptr;
	int64_t s=1;
	template<typename...Y>
	el(const Y&..._v):v(_v...){
		w=rand();
	}

	el* z(){
		return _z;
	}
	template<typename y>
	void z(y q){
		_z=q;
		update(this);
	}

	el* x(){
		return _x;
	}
	template<typename y>
	void x(y q){
		_x=q;
		update(this);
	}
};

template<typename T>
int64_t el_size(el<T>* s){
	return s?s->s:0;
}

template<typename T>
el<T>* get_by_index(el<T>* s,int64_t n){
	if (!s){
		return nullptr;
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
	assert(0);
	return (el<T>*)(nullptr);
}


template <typename T>
void update(el<T>*t){
	if (t->z()==nullptr and t->x()==nullptr){
		t->s=1;
	}
	else if (t->z()==nullptr){
		t->s=t->x()->s+1;
		t->x()->_p=t;
	}
	else if (t->x()==nullptr){
		t->s=t->z()->s+1;
		t->z()->_p=t;
	}else{
		t->s=t->z()->s+t->x()->s+1;
		t->x()->_p=t;
		t->z()->_p=t;
	}
}

template<typename T>
void to_list(el<T>* q,vector<T>&a){
	if (!q){
		return;
	}
	to_list(q->z(),a);
	a.push_back(q->v);
	to_list(q->x(),a);
	return;
}

// template<typename T>
// auto to_str(el<T>* q){
// 	vector<T> a;
// 	to_list(q,a);
// 	return a;
// }

template<typename T>
auto pr(el<T>* q,int64_t n=0){
	if (!q){
		return;
	}
	pr(q->z(),n+1);
	for (auto w=0;w<n;++w){
		putchar('\t');
	}
	print(q,q->v);
	pr(q->x(),n+1);
}

template<typename T>
el<T>* copy(el<T>* q){
	if (!q){
		return nullptr;
	}
	el<T>*w=new el<T>(q->v);
	w->z(copy(q->z()));
	w->x(copy(q->x()));
	return w;
}

template<typename T>
void del(el<T>* q){
	if (!q){
		return;
	}
	del(q->z());
	del(q->x());
	delete q;
}

template<typename T>
el<T>* merge(el<T>* t1,el<T>* t2){
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
pair<el<T>*,el<T>*> split(el<T>* t,int64_t n){
	if (!t){
		return {(el<T>*)(nullptr),(el<T>*)(nullptr)};
	}else if (!(t->z())){
		if (n<1){
			return {(el<T>*)(nullptr),t};
		}else{
			auto tmp=split(t->x(),n-1);
			t->x(tmp.first);
			auto t2=tmp.second;
			if(t2){
				t2->_p=nullptr;
			}
			return {t,t2};
		}
	}else if (t->z()->s==n){
		auto t1=t->z();
		t->z((el<T>*)(nullptr));
		if (t1){
			t1->_p=nullptr;
		}
		return {t1,t};
	}else if (t->z()->s+1==n){
		auto t2=t->x();
		t->x((el<T>*)(nullptr));
		if (t2){
			t2->_p=nullptr;
		}
		return {t,t2};
	}else if (t->z()->s+1<n){
		auto tmp=split(t->x(),n-t->z()->s-1);
		t->x(tmp.first);
		auto t2=tmp.second;
		if (t2){
			t2->_p=nullptr;
		}
		return {t,t2};
	}else if (t->z()->s>n){
		auto tmp=split(t->z(),n);
		auto t1=tmp.first;
		t->z(tmp.second);
		if (t1){
			t1->_p=nullptr;
		}
		return {t1,t};
	}
	assert(0);
	return {(el<T>*)(0),(el<T>*)(0)};
}

template <typename T>
int64_t find_index(el<T>*q){
	auto w=q->_p;
	if (w==nullptr){
		return el_size(q->z());
	}else if (w->z()==q){
		return find_index(w)-el_size(q->x())-1;
	}else if (w->x()==q){
		return find_index(w)+el_size(q->z())+1;
	}
	assert(0);
}

// template <typename T>
// el<T>* next(el<T>*q){
// 	if (!q){
// 		return nullptr;
// 	}
// 	if (q->x()){
// 		q=q->x();
// 		while (q->z()){
// 			q=q->z();
// 		}
// 		return q;
// 	}else{
// 		while (1){
// 			auto w=q->_p;
// 			if(w==nullptr){
// 				return nullptr;
// 			}
// 			if (q==w->z()){
// 				return w;
// 			}
// 			q=w;
// 		}
// 	}
// }

template <typename T>
el<T>* add(el<T>*q,int64_t n){
	if (!q){
		return nullptr;
	}
	if (n==0){
		return q;
	}
	if (n>0){
		if (el_size(q->x())>=n){
			return get_by_index(q->x(),n-1);
		}else{
			auto w=q->_p;
			if (w==nullptr){
				return nullptr;
			}else if (w->z()==q){
				return add(q->_p,-el_size(q->x())-1+n);
			}else if (w->x()==q){
				return add(q->_p,el_size(q->z())+1+n);
			}
			assert(0);
		}
	}else if (n<0){
		if (-el_size(q->z())<=n){
			return get_by_index(q->z(),el_size(q->z())+n);
		}else{
			auto w=q->_p;
			if (w==nullptr){
				return nullptr;
			}else if (w->z()==q){
				return add(q->_p,-el_size(q->x())-1+n);
			}else if (w->x()==q){
				return add(q->_p,el_size(q->z())+1+n);
			}
			assert(0);
		}
	}
	assert(0);
	return (el<T>*)(0);
}

template <typename T>
struct treap{
	el<T>* e=nullptr;
	template <typename y=vector<T>>
	treap(const y&l=initializer_list<T>(),enable_if_t<is_same_v<typename decltype(declval<y&>().begin())::value_type,T>,int> =0){
		for (auto w:l){
			e=merge(e,new auto (el<T>(w)));
		}
	}
	treap(int64_t l){
		for (int64_t w=0;w<l;++w){
			e=merge(e,new auto (el(T())));
		}
	}
	treap(const treap&l){
		e=copy(l.e);
	}
	void operator=(const treap&l){
		del(e);
		e=copy(l.e);
	}
	~treap(){
		del(e);
	}
	int64_t size()const{
		return e?e->s:0;
	}

	T&operator[](int64_t n){
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e,n)->v;
	}

	const T&operator[](int64_t n)const{
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e,n)->v;
	}

	int64_t __cmp__(const treap&d)const{
		auto&s=*this;
		int64_t min_len=d.size()<s.size()?d.size():s.size();
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
	void add_left(treap<T>&q){
		e=merge(q.e,e);
		q.e=nullptr;
	}
	void add_right(treap<T>&q){
		e=merge(e,q.e);
		q.e=nullptr;
	}
	treap<T> cut_left(int64_t n){
		assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e,n);
		assert(el_size(tmp.first)+el_size(tmp.second)==s);
		e=tmp.second;
		auto r=treap<T>();
		r.e=tmp.first;
		return r;
	}
	treap<T> cut_right(int64_t n){
		assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e,size()-n);
		assert(el_size(tmp.first)+el_size(tmp.second)==s);
		e=tmp.first;
		auto r=treap<T>();
		r.e=tmp.second;
		return r;
	}
	void push_back(const T&a){
		e=merge(e,new auto(el<T>(a)));
	}
	void push_front(const T&a){
		e=merge(new auto(el<T>(a)),e);
	}
	template<typename...Y>
	void emplace_back(const Y&...a){
		e=merge(e,new auto(el<T>(a...)));
	}
	template<typename...Y>
	void emplace_front(const Y&...a){
		e=merge(new auto(el<T>(a...)),e);
	}
	T pop_back(){
		auto q=cut_right(1);
		return q[0];
	}
	T pop_front(){
		auto q=cut_left(1);
		return q[0];
	}
	operator vector<T>()const{
		auto q=vector<T>();
		to_list(e,q);
		return q;
	}
	friend ostream&operator<<(ostream&q,const treap&w){
		vector<T> r;
		to_list(w.e,r);
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
	void clear(){
		del(e);
		e=nullptr;
	}
	bool empty(){
		return !e;
	}
	T&front(){
		return (*this)[0];
	}
	const T&front()const{
		return (*this)[0];
	}
	T&back(){
		return (*this)[this->size()-1];
	}
	const T&back()const{
		return (*this)[this->size()-1];
	}
	class iter {
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;
		template<typename Y>
		using is_iterator=Y;
		el<T>*e=nullptr;
		int64_t o=0;
		int64_t d=1;
		T&operator*(){
			return e->v;
		}
		auto&operator--(){
			return *this-=1;
		}
		auto&operator++(){
			return *this+=1;
		}
		auto&operator+=(long w){
			w*=d;
			w+=o;
			assert(e);
			while (1){
				auto s=w*2;
				auto q=e;
				q=nullptr;
				while (!q){
					s/=2;
					q=add(e,s);
				}
				if (q==e){
					break;
				}
				e=q;
				w-=s;
			}
			o=w;
			return *this;
		}
		auto&operator-=(long w){
			return *this+=(-w);
		}
		auto&operator[](long q){
			return *(*this+q);
		}
		auto& operator=(const iter&q){
			e=q.e;
			o=q.o;
			d=q.d;
			return *this;
		}
	};
	auto begin(){
		auto q=e;
		while (q->z()){
			q=q->z();
		}
		return iter{q,0};
	}
	auto end(){
		auto q=e;
		while (q->x()){
			q=q->x();
		}
		return iter{q,1};
	}
	auto rbegin(){
		auto q=end()-1;
		q.d=-1;
		return q;
	}
	auto rend(){
		auto q=begin()-1;
		q.d=-1;
		return q;
	}
	using iterator=iter;
	using value_type=T;
	auto insert(int64_t n,const T&q){
		auto w=cut_left(n);
		w.push_back(q);
		add_left(w);
		return n;
	}
	auto erase(int64_t n){
		auto w=cut_left(n);
		pop_front();
		add_left(w);
		return n;
	}
	template<typename TT>
	auto insert(TT n,const T&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(find_index(n.e),q);
	}
	template<typename TT>
	auto erase(TT n,const T&q)->typename TT::template is_iterator<iter>{
		return begin()+erase(find_index(n.e),q);
	}
	void resize(int64_t n){
		for (size_t w=size();w<n;++w){
			push_back(T());
		}
		cut_right(size()-n);
	}
};

template <typename T>
bool operator<(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)<0;
}

template <typename T>
bool operator>(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)>0;
}

template <typename T>
bool operator==(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)==0;
}

template <typename T>
bool operator<=(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)<=0;
}

template <typename T>
bool operator>=(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)>=0;
}

template <typename T>
bool operator!=(const treap<T>&q,const treap<T>&w){
	return q.__cmp__(w)!=0;
}

template <typename T>
void swap(treap<T>&q,treap<T>&e){
	auto w=q.cut_left(q.size());
	q.add_left(e);
	e.add_left(w);
}

template<typename TT>
auto operator-(TT q,TT w)->typename TT::template is_iterator<ptrdiff_t>{
	assert(q.d==w.d);
	return (find_index(q.e)-find_index(w.e)+q.o-w.o)*q.d;
}

template<typename TT>
auto operator+(TT q,long w)->typename TT::template is_iterator<TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator-(TT q,long w)->typename TT::template is_iterator<TT>{
	auto e=q;
	e-=w;
	return e;
}

template<typename TT>
auto operator+(long w,TT q)->typename TT::template is_iterator<TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator>=(TT q,TT w)->typename TT::template is_iterator<bool>{
	return q-w>=0;
}

template<typename TT>
auto operator<=(TT q,TT w)->typename TT::template is_iterator<bool>{
	return q-w<=0;
}

template<typename TT>
auto operator<(TT q,TT w)->typename TT::template is_iterator<bool>{
	return q-w<0;
}

template<typename TT>
auto operator>(TT q,TT w)->typename TT::template is_iterator<bool>{
	return q-w>0;
}

template<typename TT>
auto operator==(TT q,TT w)->typename TT::template is_iterator<bool>{
	// if (q.o==w.o){
	// 	return q.e==w.e;
	// }
	// q+=q.o;
	// w+=w.o;
	// return q.e==w.e and q.o==e.o;
	return ++q-++w==0;
}

template<typename TT>
auto operator!=(TT q,TT w)->typename TT::template is_iterator<bool>{
	// if (q.o==w.o){
	// 	return q.e!=w.e;
	// }
	// q+=q.o;
	// w+=w.o;
	// return q.e!=w.e;
	return ++q-++w!=0;
}
