#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stddef.h>

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

struct array_s {
	size_t mem_size;
	size_t el_count;
	char data[0];
};

static inline size_t len(void *a) {
	if (a == NULL) {
		return 0;
	}
	return ((struct array_s *)(a))[-1].el_count;
}

static inline void del(void *a) {
	if (a != NULL) {
		free(((struct array_s *)(a)) - 1);
	}
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
	if (*vp == NULL) {
		*vp = (struct array_s *)calloc(1, sizeof(struct array_s));
		*vp += 1;
	}
	struct array_s *a = *vp - 1;
	assert(a->data == *(char **)vp);
	if (a->mem_size < n + 1) {
		size_t cur_size = a->mem_size * el_size;
		size_t new_size;
		if (a->mem_size * 2 > n) {
			new_size = a->mem_size * 2 * el_size;
		} else {
			new_size = (n + 1) * el_size;
		}
		a = (struct array_s *)realloc(a, sizeof(struct array_s) + new_size);
		memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
		a->mem_size = new_size / el_size;
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
// #define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
// #define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
// #define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
// #define back(a) ((a)[len(a)-1])

static inline int64_t getint() {
	int sign = 1;
	int c;
	size_t res = 0;
	while (c = getchar_unlocked(), isspace(c))
		;
	if (c == '-') {
		sign = -1;
	} else {
		res = c - '0';
	}
	while (c = getchar_unlocked(), isdigit(c)) {
		res *= 10;
		res += c - '0';
	}
	return (int64_t)(res)*sign;
}

static inline void putint(uint64_t out) {
	if (out > (1LLU << 63) - 1) {
		putchar_unlocked('-');
		out = 1 + ~out;
	}
	char data[44];
	char *dend = data;
	while (out) {
		*++dend = (unsigned)('0') + out % 10;
		out /= 10;
	}
	if (dend == data) {
		putchar_unlocked('0');
	}
	for (; dend != data; --dend) {
		putchar_unlocked(*dend);
	}
}

static inline void print(uint64_t out) {
	putint(out);
	putchar('\n');
}

static inline void write(uint64_t out) {
	putint(out);
	putchar(' ');
}

// #define min(a,s) ((a)<(s)?(a):(s))
// #define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

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
		const T v;
		const int64_t w;
		const el* const z_get=nullptr;
		const el* const x_get=nullptr;
		const el* const p=nullptr;
		const int64_t s=1;
		const int64_t d=1;
		const uint64_t sum=0;
		const int r=0;
		template<typename...Y>
		el(const Y&..._v):v(_v...),w(rand()){update();}
		el(const el&t)=delete;

		template<typename y>
		void z_put(y q)const{
			const_cast<const el*&>(z_get)=q;
			// z_get=q;
			update();
		}

		template<typename y>
		void x_put(y q)const{
			const_cast<const el*&>(x_get)=q;
			// x_get=q;
			update();
		}
		// void make(){
		// 	if (r){
		// 		auto t=z_put();
		// 		z_put(x_put());
		// 		x_put(t);
		// 		if (z_put()){
		// 			z_put()->r=1;
		// 		}
		// 		if (x_put()){
		// 			x_put()->r=1;
		// 		}
		// 		r=0;
		// 	}
		// }
		void update()const{
			auto t=this;
			if (t->z_get==nullptr and t->x_get==nullptr){
				const_cast<int64_t&>(t->s)=1;
				const_cast<int64_t&>(t->d)=1;
				const_cast<uint64_t&>(t->sum) = t->v*t->v;
			}
			else if (t->z_get==nullptr){
				const_cast<int64_t&>(t->s)=t->x_get->s+1;
				const_cast<const el*&>(t->x_get->p)=t;
				const_cast<int64_t&>(t->d)=t->x_get->d+1;
				const_cast<uint64_t&>(t->sum) = t->v*t->v + t->x_get->sum;
			}
			else if (t->x_get==nullptr){
				const_cast<int64_t&>(t->s)=t->z_get->s+1;
				const_cast<const el*&>(t->z_get->p)=t;
				const_cast<int64_t&>(t->d)=t->z_get->d+1;
				const_cast<uint64_t&>(t->sum) = t->v*t->v + t->z_get->sum;
			}else{
				const_cast<int64_t&>(t->s)=t->z_get->s+t->x_get->s+1;
				const_cast<const el*&>(t->x_get->p)=t;
				const_cast<const el*&>(t->z_get->p)=t;
				const_cast<int64_t&>(t->d)=(t->z_get->d>t->x_get->d?t->z_get->d:t->x_get->d)+1;
				const_cast<uint64_t&>(t->sum) = t->v*t->v + t->x_get->sum + t->z_get->sum;
			}
			if (t->d>128){
				std::cerr<<"bamboo!! "<<t->d<<std::endl;
				exit(0);
			}
		}
		void set_root()const{
			const_cast<const el*&>(p)=nullptr;
		}
		int64_t nz_find_index(){
			auto q=this;
			auto w=q->p;
			if (w==nullptr){
				return el_size(q->z_get);
			}else if (w->z_get==q){
				return w->nz_find_index()-el_size(q->x_get)-1;
			}else if (w->x_get==q){
				return w->nz_find_index()+el_size(q->z_get)+1;
			}
			assert(0);
			return 0;
		}
		int64_t elsize(){
			return el_size(this);
		}
	};

	static int64_t el_size(const el*s){
		return s?s->s:0;
	}

	static int64_t find_index(el*s){
		return s?s->nz_find_index():0;
	}

	static const el* get_by_index(const el*s,int64_t n){
		if (!s){
			return nullptr;
		}
		if (s->z_get==nullptr){
			if (n==0){
				return s;
			}
			else{
				return get_by_index(s->x_get,n-1);
			}
		}
		else{
			if (n==s->z_get->s){
				return s;
			}
			if (n<s->z_get->s){
				return get_by_index(s->z_get,n);
			}
			if (n>s->z_get->s){
				return get_by_index(s->x_get,n-s->z_get->s-1);
			}
		}
		assert(0);
		return (el*)(nullptr);
	}

	static void to_list(el* q,std::vector<T>&a){
		if (!q){
			return;
		}
		to_list(q->z_get,a);
		a.push_back(q->v);
		to_list(q->x_get,a);
		return;
	}

	static auto pr(el* q,int64_t n=0){
		if (!q){
			return;
		}
		pr(q->z_get,n+1);
		for (auto w=0;w<n;++w){
			putchar('|');
		}
		std::cout<<q<<' '<<q->v<<' '<<q->w<<std::endl;
		pr(q->x_get,n+1);
	}

	static auto pri(const el* root,size_t*prev_node=0){
		if (!root){
			return;
		}
		const el*left=(root)->z_get;
		const el*right=(root)->x_get;

		size_t node[3];
		node[2]=(size_t)NULL;
		node[0]=(size_t)prev_node;
		if (prev_node){
			prev_node[2]=(size_t)node;
		}

		size_t save=0;
		if (prev_node and prev_node[1]==2){
			save=prev_node[1];
			prev_node[1]=0;
		}
		node[1]=2;
		pri(left,node);
		if (save){
			prev_node[1]=save;
		}

		size_t*d=node;
		while(d[0]){
			d=(size_t*)d[0];
		}

		for (;d!=node;d=(size_t*)d[2]){
			if (d[1]==1){
				if (d==prev_node){
					std::cout<<("┗");
				}else{
					std::cout<<("┃");
				}
			}else
			if (d[1]==2){
				if (d==prev_node){
					std::cout<<("┏");
				}else{
					std::cout<<("┃");
				}
			}else{
				std::cout<<(" ");
			}
		}

		if (left==NULL and right==NULL){
			std::cout<<("━");
		}else
		if (left==NULL){
			std::cout<<("┳");
		}else
		if (right==NULL){
			std::cout<<("┻");
		}else{
			std::cout<<("╋");
		}
		std::cout<<("► ");
		std::cout<<root->v<<" "<<root->sum<<std::endl;

		save=0;
		if (prev_node and prev_node[1]==1){
			save=prev_node[1];
			prev_node[1]=0;
		}
		node[1]=1;
		pri(right,node);
		if (save){
			prev_node[1]=save;
		}
	}

	static el* copy(el* q){
		if (!q){
			return nullptr;
		}
		el*w=new el(q->v);
		w=merge(copy(q->z_get),w);
		w=merge(w,copy(q->x_get));
		return w;
	}

	static void del(const el* q){
		if (!q){
			return;
		}
		del(q->z_get);
		del(q->x_get);
		delete q;
	}

	static const el* merge(const el* t1,const el* t2){
		if (!t1){
			return t2;
		}
		if (!t2){
			return t1;
		}
		if (t1->w<t2->w){
			t2->z_put(merge(t1,t2->z_get));
			return t2;
		}else{
			t1->x_put(merge(t1->x_get,t2));
			return t1;
		}
	}

	static std::pair<const el*,const el*> split(const el* t,int64_t n){
		if (!t){
			return {nullptr,nullptr};
		}else if (t->z_get==nullptr){
			if (n<1){
				return {(el*)(nullptr),t};
			}else{
				auto tmp=split(t->x_get,n-1);
				t->x_put(tmp.first);
				auto t2=tmp.second;
				if(t2){
					t2->set_root();
					// t2->p=nullptr;
				}
				return {t,t2};
			}
		}else if (t->z_get->s==n){
			auto t1=t->z_get;
			t->z_put((el*)(nullptr));
			if (t1){
				t1->set_root();
				// t1->p=nullptr;
			}
			return {t1,t};
		}else if (t->z_get->s+1==n){
			auto t2=t->x_get;
			t->x_put((el*)(nullptr));
			if (t2){
				t2->set_root();
				// t2->p=nullptr;
			}
			return {t,t2};
		}else if (t->z_get->s+1<n){
			auto tmp=split(t->x_get,n-t->z_get->s-1);
			t->x_put(tmp.first);
			auto t2=tmp.second;
			if (t2){
				t2->set_root();
				// t2->p=nullptr;
			}
			return {t,t2};
		}else if (t->z_get->s>n){
			auto tmp=split(t->z_get,n);
			auto t1=tmp.first;
			t->z_put(tmp.second);
			if (t1){
				t1->set_root();
				// t1->p=nullptr;
			}
			return {t1,t};
			// return {nullptr,nullptr};
		}
		assert(0);
		return {nullptr,nullptr};
		// if (!t){
		// 	return {nullptr,nullptr};
		// }
		// int64_t ls=t->z_get?t->z_get->s:0;
		// if (n>ls){
		// 	auto tmp=split(t->x_get,n-ls-1);
		// 	t->x_put(tmp.first);
		// 	return {t,tmp.second};
		// }else{
		// 	auto tmp=split(t->z_get,n);
		// 	t->z_put(tmp.second);
		// 	return {tmp.first,t};
		// }		
		// assert(0);
		// return {nullptr,nullptr};
	}

	static el* add(el*q,int64_t n){
		if (!q){
			return nullptr;
		}
		if (n==0){
			return q;
		}
		if (n>0){
			if (el_size(q->x_get)>=n){
				return get_by_index(q->x_get,n-1);
			}else{
				auto w=q->p;
				if (w==nullptr){
					return nullptr;
				}else if (w->z_get==q){
					return add(q->p,-el_size(q->x_get)-1+n);
				}else if (w->x_get==q){
					return add(q->p,el_size(q->z_get)+1+n);
				}
				assert(0);
			}
		}else if (n<0){
			if (-el_size(q->z_get)<=n){
				return get_by_index(q->z_get,el_size(q->z_get)+n);
			}else{
				auto w=q->p;
				if (w==nullptr){
					return nullptr;
				}else if (w->z_get==q){
					return add(q->p,-el_size(q->x_get)-1+n);
				}else if (w->x_get==q){
					return add(q->p,el_size(q->z_get)+1+n);
				}
				assert(0);
			}
		}
		assert(0);
		return (el*)(0);
	}

	const el* e=nullptr;
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
	uint64_t sum()const{
		return e?e->sum:0;
	}

	const T&operator[](int64_t n){
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
		const el*e=nullptr;
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
		const el* q=e;
		while (q->z_get){
			q=q->z_get;
		}
		return iter{q,0};
	}
	auto end(){
		if (!e){
			return iter{e,0};
		}
		const el* q=e;
		while (q->x_get){
			q=q->x_get;
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

int main(){
	uint64_t n=getint();
	getint();
	treap<uint64_t> a;
	for (uint64_t w=0;w<n;++w){
		a.push_back(getint());
	}
	uint64_t k=getint();
	// a.out();
	print(a.sum());
	for (uint64_t w=0;w<k;++w){
		uint64_t q=getint(),p=getint()-1;
		if (q==1){
			if (p==0){
				auto x=a[p];
				auto c=a[p+1];
				a.erase(p);
				a.erase(p);
				a.insert(p,c+x);
				// auto c=a.cut_left(1);
				// auto v=a.cut_left(1);
				// v[0]+=c[0];
				// a.add_left(v);
			}else
			if (p==a.size()-1){
				auto z=a[p-1];
				auto x=a[p];
				a.erase(p-1);
				a.erase(p-1);
				a.insert(p-1,z+x);
				// auto s=a.cut_left(p);
				// auto z=s.cut_right(1);
				// auto c=a.cut_left(1);
				// z[0]+=c[0];
				// s.add_right(z);
				// a.add_left(s);
			}else{
				// auto s=a.cut_left(p);
				// auto z=s.cut_right(1);
				// auto c=a.cut_left(1);
				// auto v=a.cut_left(1);
				// z[0]+=c[0]/2;
				// v[0]+=(c[0]+1)/2;
				// s.add_right(z);
				// a.add_left(v);
				// a.add_left(s);
				auto z=a[p-1];
				auto x=a[p];
				auto c=a[p+1];
				a.erase(p-1);
				a.erase(p-1);
				a.erase(p-1);
				a.insert(p-1,z+x/2);
				a.insert(p,c+(x+1)/2);
			}
		}
		if (q==2){
			// auto s=a.cut_left(p);
			// auto d=a.cut_left(1);
			// auto f=d;
			// d[0]/=2;
			// f[0]+=1;
			// f[0]/=2;
			// a.add_left(f);
			// a.add_left(d);
			// a.add_left(s);
			auto z=a[p];
			a.erase(p);
			a.insert(p,(z+1)/2);
			a.insert(p,z/2);
		}
		// a.out();
		print(a.sum());
	}
}
