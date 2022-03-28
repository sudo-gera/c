#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <assert.h>

template <typename T>
class treap{
private:
	struct el{
		T v;
		int64_t w;
		el* _z=nullptr;
		el* _x=nullptr;
		el* _p=nullptr;
		int64_t s=1;
		int64_t d=1;
		int r=0;
		template<typename...Y>
		el(const Y&..._v):v(_v...),w(rand()){}

		el*& z(){
			return _z;
		}
		template<typename y>
		void z(y&& q){
			_z=std::move(q);
			update();
		}

		el*& x(){
			return _x;
		}
		template<typename y>
		void x(y&& q){
			_x=std::move(q);
			update();
		}
		void make(){
			if (r){
				auto t=z();
				z(x());
				x(t);
				if (z()){
					z()->r=1;
				}
				if (x()){
					x()->r=1;
				}
				r=0;
			}
		}
		void update(){
			auto t=this;
			if (t->z()==nullptr and t->x()==nullptr){
				t->s=1;
				t->d=1;
			}
			else if (t->z()==nullptr){
				t->s=t->x()->s+1;
				t->x()->_p=t;
				t->d=t->x()->d+1;
			}
			else if (t->x()==nullptr){
				t->s=t->z()->s+1;
				t->z()->_p=t;
				t->d=t->z()->d+1;
			}else{
				t->s=t->z()->s+t->x()->s+1;
				t->x()->_p=t;
				t->z()->_p=t;
				t->d=(t->z()->d>t->x()->d?t->z()->d:t->x()->d)+1;
			}
			if (t->d>256){
				std::cerr<<"bamboo!! "<<t->d<<std::endl;
				exit(0);
			}
		}
		int64_t nz_find_index(){
			auto q=this;
			auto w=q->_p;
			if (w==nullptr){
				return el_size(q->z());
			}else if (w->z()==q){
				return w->nz_find_index()-el_size(q->x())-1;
			}else if (w->x()==q){
				return w->nz_find_index()+el_size(q->z())+1;
			}
			assert(0);
			return 0;
		}
	};

	static int64_t el_size(el*&s){
		return s?s->s:0;
	}

	static int64_t find_index(el*const&s){
		return s?s->nz_find_index():0;
	}

	static el* get_by_index(el*const&s,int64_t n){
		if (!s){
			return nullptr;
		}
		if (s->z()==nullptr){
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
		return (el*)(nullptr);
	}

	static void to_list(el* q,std::vector<T>&a){
		if (!q){
			return;
		}
		to_list(q->z(),a);
		a.push_back(q->v);
		to_list(q->x(),a);
		return;
	}

	static auto pr(el* q,int64_t n=0){
		if (!q){
			return;
		}
		pr(q->z(),n+1);
		for (auto w=0;w<n;++w){
			putchar('|');
		}
		std::cout<<q<<' '<<q->v<<' '<<q->w<<std::endl;
		pr(q->x(),n+1);
	}

	static auto pri(el* q,std::vector<int64_t>*p=0){
		if (!q){
			return;
		}
		int c=0;
		if (!p){
			p=new std::vector<int64_t>();
			c=1;
		}
		auto&l=*p;
		int64_t s=0;
		if (l.size()){
			s=l[l.size()-1];
			if (s==2){
				l[l.size()-1]=0;
			}
		}
		l.push_back(2);
		pri(q->z(),p);
		l.pop_back();
		if (l.size()){
			l[l.size()-1]=s;
		}
		//┓┛┏┗┃━
		//━┃┏┓┗┛┣┫┳┻╋
		//┫
		for (auto w=0;w<l.size();++w){
			if (l[w]==1){
				if (w==l.size()-1){
					std::cout<<"┗";
				}else{
					std::cout<<"┃";
				}
			}else
			if (l[w]==2){
				if (w==l.size()-1){
					std::cout<<"┏";
				}else{
					std::cout<<"┃";
				}
			}else{
				std::cout<<" ";
			}
		}
		if (q->z()==nullptr and q->x()==nullptr){
			std::cout<<"━";
		}else
		if (q->z()==nullptr){
			std::cout<<"┳";
		}else
		if (q->x()==nullptr){
			std::cout<<"┻";
		}else{
			std::cout<<"╋";
		}
		std::cout<<"► ";
		std::cout<<q->v<<std::endl;
		s=0;
		if (l.size()){
			s=l[l.size()-1];
			if (s==1){
				l[l.size()-1]=0;
			}
		}
		l.push_back(1);
		pri(q->x(),p);
		l.pop_back();
		if (l.size()){
			l[l.size()-1]=s;
		}
		if (c){
			delete p;
		}
	}

	static el* copy(el* q){
		if (!q){
			return nullptr;
		}
		el*w=new el(q->v);
		w=merge(copy(q->z()),w);
		w=merge(w,copy(q->x()));
		return w;
	}

	static void del(el* q){
		if (!q){
			return;
		}
		del(q->z());
		del(q->x());
		delete q;
	}

	static el* merge(el* t1,el* t2){
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

	static std::pair<el*,el*> split(el* t,int64_t n){
		if (!t){
			return {(el*)(nullptr),(el*)(nullptr)};
		}else if (t->z()==nullptr){
			if (n<1){
				return {(el*)(nullptr),t};
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
			t->z((el*)(nullptr));
			if (t1){
				t1->_p=nullptr;
			}
			return {t1,t};
		}else if (t->z()->s+1==n){
			auto t2=t->x();
			t->x((el*)(nullptr));
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
		return {(el*)(0),(el*)(0)};
	}

	static el* add(el*q,int64_t n){
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
		return (el*)(0);
	}

	el* e=nullptr;
public:
	void out(){
		pri(e);
	}
	template <typename y=std::initializer_list<T>>
	treap(const y&l=std::initializer_list<T>(),
		std::enable_if_t<
			std::is_same_v<
				typename y::value_type,T
			> and std::is_copy_constructible_v<T>
			and std::is_same_v<decltype(l.begin()!=l.end()),bool>
			,int> =0){
		for (auto&w:l){
			e=merge(e,new auto (el(w)));
		}
	}
	template <typename y=int>
	treap(y=0,
		std::enable_if_t<!std::is_copy_constructible_v<T>
			,y> =0){
	}
	template<typename y=int64_t>
	treap(std::enable_if_t<
			std::is_trivially_constructible_v<T>
		,y> l){
		for (int64_t w=0;w<l;++w){
			e=merge(e,new auto (el(T())));
		}
	}
	treap(const treap&l){
		e=copy(l.e);
	}
	treap(treap&&l){
		std::swap(e,l.e);
	}
	auto&operator=(treap&&l){
		std::swap(e,l.e);
		return *this;
	}
	auto&operator=(const treap&l){
		if (e!=l.e){
			del(e);
			e=copy(l.e);
		}
		return *this;
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
private:
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
public:
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
	treap<T> cut(int64_t l,int64_t r){
		assert(0<=l and l<=r and  r<=size());
		auto q=cut_left(l);
		auto w=cut_left(r-l);
		add_left(q);
		return w;
	}
	void push_back(const T&a){
		e=merge(e,new auto(el(a)));
	}
	void push_front(const T&a){
		e=merge(new auto(el(a)),e);
	}
	template<typename...Y>
	void emplace_back(const Y&...a){
		e=merge(e,new auto(el(a...)));
	}
	template<typename...Y>
	void emplace_front(const Y&...a){
		e=merge(new auto(el(a...)),e);
	}
	T pop_back(){
		auto q=cut_right(1);
		return q[0];
	}
	T pop_front(){
		auto q=cut_left(1);
		return q[0];
	}
	operator std::vector<T>()const{
		auto q=std::vector<T>();
		to_list(e,q);
		return q;
	}
	friend std::ostream&operator<<(std::ostream&q,const treap&w){
		auto r=std::vector<T>(w);
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
	struct iter {
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;
		template<typename Y>
		using is_iterator=Y;
		using original_type=treap<T>;
		el*e=nullptr;
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
		auto operator--(int){
			auto q=*this;
			*this-=1;
			return q;
		}
		auto operator++(int){
			auto q=*this;
			*this+=1;
			return q;
		}
		auto&operator+=(long w){
			w*=d;
			w+=o;
			if (!e){
				return *this;
			}
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
		if (!e){
			return iter{e,0};
		}
		auto q=e;
		while (q->z()){
			q=q->z();
		}
		return iter{q,0};
	}
	auto end(){
		if (!e){
			return iter{e,0};
		}
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
	auto insert(int64_t n,treap<T>&q){
		auto w=cut_left(n);
		add_left(q);
		add_left(w);
		return n;
	}
	template<typename TT>
	auto insert(TT n,treap<T>&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(find_index(n.e),q);
	}
	void resize(int64_t n){
		for (size_t w=size();w<n;++w){
			push_back(T());
		}
		cut_right(size()-n);
	}
	template <typename Y>
	friend bool operator< (const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend bool operator> (const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend bool operator==(const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend bool operator<=(const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend bool operator>=(const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend bool operator!=(const treap<Y>&q,const treap<Y>&w);
	template <typename Y>
	friend void swap(treap&q,treap&e);
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
	return ((q.e)->nz_find_index()-(w.e)->nz_find_index()+q.o-w.o)*q.d;
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
	q+=0;
	w+=0;
	return q.e==w.e and q.o==w.o;
}

template<typename TT>
auto operator!=(TT q,TT w)->typename TT::template is_iterator<bool>{
	q+=0;
	w+=0;
	return q.e!=w.e or q.o!=w.o;
}
