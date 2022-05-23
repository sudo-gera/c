#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#ifndef assert
#include <assert.h>
#endif
#include <algorithm>

#ifdef assert_m
#define assert assert_m
#endif

#define bisect(b, e, ...)														\
	({																			\
		int64_t __begin = b;													\
		int64_t __end = e;														\
		assert(__begin <= __end);												\
		while (__begin + 1 < __end) {											\
			int64_t __center = (__begin + __end) / 2;							\
			if (__VA_ARGS__) {													\
				__end = __center;												\
			} else {															\
				__begin = __center;												\
			}																	\
		}																		\
		int64_t __center = __begin;												\
		if (__begin != __end and (__VA_ARGS__)) {								\
			__end = __center;													\
		}																		\
		__end;																	\
	})

#define get(a) auto a##_z=a?a->z_get():0;auto a##_x=a?a->x_get():0;

template <typename T>
class treap{
private:
	struct el{
		T v;
		int64_t w;
		el const*const z=nullptr;
		el const*const x=nullptr;
		el const*const p=nullptr;
		long const s=1;
		long const d=1;
		long const rev=0;
		T const first=0;
		T const last=0;
		T const sum=0;
		long const to_add=0;
		long const to_mul=1;
		long const is_forward=false;
		long const is_backward=false;
		template<typename...Y>
		el(const Y&..._v):v(_v...),w(rand()){update();}

		template<typename y>
		void z_put(y q)const{
			make();
			// if (z){
			// 	const_cast<const el*&>(z->p)=nullptr;
			// }
			const_cast<const el*&>(z)=q;
			update();
		}

		template<typename y>
		void x_put(y q)const{
			make();
			// if (x){
			// 	const_cast<const el*&>(x->p)=nullptr;
			// }
			const_cast<const el*&>(x)=q;
			update();
		}

		auto z_get()const{
			make();
			return z;
		}

		auto x_get()const{
			make();
			return x;
		}

		void setroot()const{
			const_cast<const el*&>(p)=nullptr;
		}

		void make()const{
			if (to_mul!=1){
				const_cast<long&>(sum)*=to_mul;
				const_cast<long&>(first)*=to_mul;
				const_cast<long&>(last)*=to_mul;
				const_cast<long&>(v)*=to_mul;
				if (z){
					const_cast<long&>(z->to_mul)*=to_mul;
					const_cast<long&>(z->to_add)*=to_mul;
				}
				if (x){
					const_cast<long&>(x->to_mul)*=to_mul;
					const_cast<long&>(x->to_add)*=to_mul;
				}
				if (to_mul<0){
					std::swap(const_cast<long&>(is_forward),const_cast<long&>(is_backward));
					std::swap(const_cast<long&>(first),const_cast<long&>(last));
				}
				if (to_mul==0){
					const_cast<long&>(is_forward)=1;
					const_cast<long&>(is_backward)=1;
				}
				const_cast<long&>(to_mul)=1;
			}

			if (to_add!=0){
				const_cast<long&>(sum)+=to_add*s;
				const_cast<long&>(first)+=to_add;
				const_cast<long&>(last)+=to_add;
				const_cast<long&>(v)+=to_add;
				if (z){
					const_cast<long&>(z->to_add)+=to_add;
				}
				if (x){
					const_cast<long&>(x->to_add)+=to_add;
				}
				const_cast<long&>(to_add)=0;
			}

			if (rev){
				std::swap(const_cast<const el*&>(z),const_cast<const el*&>(x));
				std::swap(const_cast<long&>(is_forward),const_cast<long&>(is_backward));
				std::swap(const_cast<long&>(first),const_cast<long&>(last));
				if (z){
					const_cast<long&>(z->rev)^=1;
				}
				if (x){
					const_cast<long&>(x->rev)^=1;
				}
				const_cast<long&>(rev)=0;
			}
		}
		void update()const{
			auto t=this;
			auto s=this;
			if (s->z){
				const_cast<const el*&>(s->z->p)=s;
				if (s->z->rev){
					const_cast<long&>(s->first)=s->z->last*s->z->to_mul+s->z->to_add;
				}else{
					const_cast<long&>(s->first)=s->z->first*s->z->to_mul+s->z->to_add;
				}
			}else{
				const_cast<long&>(s->first)=s->v;
			}
			if (s->x){
				const_cast<const el*&>(s->x->p)=s;
				if (s->x->rev){
					const_cast<long&>(s->last)=s->x->first*s->x->to_mul+s->x->to_add;
				}else{
					const_cast<long&>(s->last)=s->x->last*s->x->to_mul+s->x->to_add;
				}
			}else{
				const_cast<long&>(s->last)=s->v;
			}
			if (s->z and s->x){
				const_cast<long&>(s->s)=s->z->s+s->x->s+1;
				const_cast<long&>(s->d)=1+std::max(s->z->d,s->x->d);
				const_cast<long&>(s->sum)=s->v + s->z->sum*s->z->to_mul+s->z->to_add*s->z->s + s->x->sum*s->x->to_mul+s->x->to_add*s->x->s;
				const_cast<long&>(s->is_forward)=((s->z->to_mul==0 or (s->z->rev?s->z->is_backward:s->z->is_forward)) and (s->x->to_mul==0 or (s->x->rev?s->x->is_backward:s->x->is_forward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add<=s->v and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add>=s->v);
				const_cast<long&>(s->is_backward)=((s->z->to_mul==0 or (s->z->rev?s->z->is_forward:s->z->is_backward)) and (s->x->to_mul==0 or (s->x->rev?s->x->is_forward:s->x->is_backward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add>=s->v and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add<=s->v);
			}else
			if (s->z){
				const_cast<long&>(s->s)=s->z->s+1;
				const_cast<long&>(s->d)=s->z->d+1;
				const_cast<long&>(s->sum)=s->v + s->z->sum*s->z->to_mul+s->z->to_add*s->z->s;
				const_cast<long&>(s->is_forward)=((s->z->to_mul==0 or (s->z->rev?s->z->is_backward:s->z->is_forward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add<=s->v);
				const_cast<long&>(s->is_backward)=((s->z->to_mul==0 or (s->z->rev?s->z->is_forward:s->z->is_backward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add>=s->v);
			}else
			if (s->x){
				const_cast<long&>(s->s)=s->x->s+1;
				const_cast<long&>(s->d)=s->x->d+1;
				const_cast<long&>(s->sum)=s->v + s->x->sum*s->x->to_mul+s->x->to_add*s->x->s;
				const_cast<long&>(s->is_forward)=((s->x->to_mul==0 or (s->x->rev?s->x->is_backward:s->x->is_forward)) and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add>=s->v);
				const_cast<long&>(s->is_backward)=((s->x->to_mul==0 or (s->x->rev?s->x->is_forward:s->x->is_backward)) and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add<=s->v);
			}else{
				const_cast<long&>(s->s)=1;
				const_cast<long&>(s->d)=1;
				const_cast<long&>(s->sum)=s->v;
				const_cast<long&>(s->is_forward)=1;
				const_cast<long&>(s->is_backward)=1;
			}
			if (t->d>128){
				std::cerr<<"bamboo!! "<<t->d<<std::endl;
				exit(0);
			}
		}
		int64_t nz_find_index()const{
			auto q=this;
			auto w=q->p;
			if (w==nullptr){
				return el_size(q->z_get());
			}else if (w->z_get()==q){
				return w->nz_find_index()-el_size(q->x_get())-1;
			}else if (w->x_get()==q){
				return w->nz_find_index()+el_size(q->z_get())+1;
			}
			assert(0);
			return 0;
		}
		int64_t elsize(){
			return el_size(this);
		}
	};

	static void check(const el*s){
		return;
		if (!s){
			return;
		}
		check(s->z);
		check(s->x);
		assert(s->rev<2);
		if (s->z){
			assert(s->z->p==s);
			assert(s->z->w<=s->w);
			if (s->z->rev){
				assert(s->first==s->z->last*s->z->to_mul+s->z->to_add);
			}else{
				assert(s->first==s->z->first*s->z->to_mul+s->z->to_add);
			}
		}else{
			assert(s->first==s->v);
		}
		if (s->x){
			assert(s->x->p==s);
			assert(s->x->w<=s->w);
			if (s->x->rev){
				assert(s->last==s->x->first*s->x->to_mul+s->x->to_add);
			}else{
				assert(s->last==s->x->last*s->x->to_mul+s->x->to_add);
			}
		}else{
			assert(s->last==s->v);
		}
		if (s->z and s->x){
			assert(s->z->s+s->x->s+1==s->s);
			assert(s->d==1+std::max(s->z->d,s->x->d));
			assert(s->sum==s->v + s->z->sum*s->z->to_mul+s->z->to_add*s->z->s + s->x->sum*s->x->to_mul+s->x->to_add*s->x->s);
			assert((s->is_forward)==((s->z->to_mul==0 or (s->z->rev?s->z->is_backward:s->z->is_forward)) and (s->x->to_mul==0 or (s->x->rev?s->x->is_backward:s->x->is_forward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add<=s->v and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add>=s->v));
			assert((s->is_backward)==((s->z->to_mul==0 or (s->z->rev?s->z->is_forward:s->z->is_backward)) and (s->x->to_mul==0 or (s->x->rev?s->x->is_forward:s->x->is_backward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add>=s->v and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add<=s->v));
		}else
		if (s->z){
			assert(s->z->s+1==s->s);
			assert(s->z->d+1==s->d);
			assert(s->sum==s->v + s->z->sum*s->z->to_mul+s->z->to_add*s->z->s);
			assert((s->is_forward)==((s->z->to_mul==0 or (s->z->rev?s->z->is_backward:s->z->is_forward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add<=s->v));
			assert((s->is_backward)==((s->z->to_mul==0 or (s->z->rev?s->z->is_forward:s->z->is_backward)) and (s->z->rev?s->z->first:s->z->last)*s->z->to_mul+s->z->to_add>=s->v));
		}else
		if (s->x){
			assert(s->x->s+1==s->s);
			assert(s->x->d+1==s->d);
			assert(s->sum==s->v + s->x->sum*s->x->to_mul+s->x->to_add*s->x->s);
			assert((s->is_forward)==((s->x->to_mul==0 or (s->x->rev?s->x->is_backward:s->x->is_forward)) and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add>=s->v));
			assert((s->is_backward)==((s->x->to_mul==0 or (s->x->rev?s->x->is_forward:s->x->is_backward)) and (s->x->rev?s->x->last:s->x->first)*s->x->to_mul+s->x->to_add<=s->v));
		}else{
			assert(1==s->s);
			assert(1==s->d);
			assert(s->sum==s->v);
			assert(s->is_forward==1);
			assert(s->is_backward==1);
		}

	}

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
		get(s);
		if (s_z==nullptr){
			if (n==0){
				return s;
			}
			else{
				return get_by_index(s_x,n-1);
			}
		}
		else{
			if (n==s_z->s){
				return s;
			}
			if (n<s_z->s){
				return get_by_index(s_z,n);
			}
			if (n>s_z->s){
				return get_by_index(s_x,n-s_z->s-1);
			}
		}
		assert(0);
		return (el*)(nullptr);
	}

	static void to_list(const el* q,std::vector<T>&a){
		if (!q){
			return;
		}
		to_list(q->z_get(),a);
		a.push_back(q->v);
		to_list(q->x_get(),a);
		return;
	}

	static auto pr(el* q,int64_t n=0){
		if (!q){
			return;
		}
		pr(q->z_get(),n+1);
		for (auto w=0;w<n;++w){
			putchar('|');
		}
		std::cout<<q<<' '<<q->v<<' '<<q->w<<std::endl;
		pr(q->x_get(),n+1);
	}

	static auto pri(const el* root,size_t*prev_node=0){
		if (!root){
			return;
		}
		const el*left;
		const el*right;
		// if (root->rev){
			// left=root->x;
			// right=root->z;
		// }else{
			left=root->z;
			right=root->x;
		// }

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

		if (root->rev){
			std::cout<<"\x1b[34m";
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
		if (root->rev){
			std::cout<<"\x1b[0m";
		}

		std::cout<<("► ");

#define _put(s) std::cout<<#s<<" = "<<root->s<<' ';

		// std::cout<<

		// 	root->v<<' '<<
		// 	root->is_forward<<' '<<
		// 	root->is_backward<<' '<<
		// 	root->sum<<' '<<
		// 	root->to_add<<' '<<
		// 	root->to_mul<<' '<<
		// 	std::endl;

		_put(v)
		_put(sum)
		_put(to_mul)
		_put(to_add)
		_put(s)
		_put(d)
		_put(first)
		_put(last)
		_put(is_forward)
		_put(is_backward)
		std::cout<<std::endl;

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

	// static const el* copy(const el* q){
	// 	if (!q){
	// 		return nullptr;
	// 	}
	// 	const el*w=new el(q->v);
	// 	w=merge(copy(q->z_get()),w);
	// 	w=merge(w,copy(q->x_get()));
	// 	return w;
	// }

	static void del(const el* q){
		if (!q){
			return;
		}
		del(q->z);
		del(q->x);
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
			t2->z_put(merge(t1,t2->z_get()));
			return t2;
		}else{
			t1->x_put(merge(t1->x_get(),t2));
			return t1;
		}
	}

	static std::pair<const el*,const el*> split(const el* t,int64_t n){
		if (!t){
			return {nullptr,nullptr};
		}
		get(t);
		if (t_z==nullptr){
			if (n<1){
				return {(el*)(nullptr),t};
			}else{
				auto tmp=split(t_x,n-1);
				t->x_put(tmp.first);
				auto t2=tmp.second;
				if(t2){
					t2->setroot();
					// t2->p=nullptr;
				}
				return {t,t2};
			}
		}else if (t_z->s==n){
			auto t1=t_z;
			t->z_put((el*)(nullptr));
			if (t1){
				t1->setroot();
				// t1->p=nullptr;
			}
			return {t1,t};
		}else if (t_z->s+1==n){
			auto t2=t_x;
			t->x_put((el*)(nullptr));
			if (t2){
				t2->setroot();
				// t2->p=nullptr;
			}
			return {t,t2};
		}else if (t_z->s+1<n){
			auto tmp=split(t_x,n-t_z->s-1);
			t->x_put(tmp.first);
			auto t2=tmp.second;
			if (t2){
				t2->setroot();
				// t2->p=nullptr;
			}
			return {t,t2};
		}else if (t_z->s>n){
			auto tmp=split(t_z,n);
			auto t1=tmp.first;
			t->z_put(tmp.second);
			if (t1){
				t1->setroot();
				// t1->p=nullptr;
			}
			return {t1,t};
		}
		assert(0);
		return {nullptr,nullptr};
	}

	static const el* add(const el*q,int64_t n){
		if (!q){
			return nullptr;
		}
		if (n==0){
			return q;
		}
		get(q);
		if (n>0){
			if (el_size(q_x)>=n){
				return get_by_index(q_x,n-1);
			}else{
				auto w=q->p;
				get(w);
				if (w==nullptr){
					return nullptr;
				}else if (w_z==q){
					return add(q->p,-el_size(q_x)-1+n);
				}else if (w_x==q){
					return add(q->p,el_size(q_z)+1+n);
				}
				assert(0);
			}
		}else if (n<0){
			if (-el_size(q_z)<=n){
				return get_by_index(q_z,el_size(q_z)+n);
			}else{
				auto w=q->p;
				get(w);
				if (w==nullptr){
					return nullptr;
				}else if (w_z==q){
					return add(q->p,-el_size(q_x)-1+n);
				}else if (w_x==q){
					return add(q->p,el_size(q_z)+1+n);
				}
				assert(0);
			}
		}
		assert(0);
		return (el*)(0);
	}

	const el* _e=nullptr;
	const el* e_get()const{
		check(_e);
		if(_e){_e->make();};
		return _e;
	}
	template<typename Y>
	void e_put(const Y&v){
		if(_e){_e->make();};
		const_cast<const el*&>(_e)=v;
		if (_e){
			_e->update();
		}
	}
public:
	void out(){
		pri(_e);
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
			e_put(merge(e_get(),new auto (el(w))));
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
			e_put(merge(e_get(),new auto (el(T()))));
		}
	}
	treap(const treap&l){
		for (auto&w:l){
			e_put(merge(e_get(),new auto (el(w))));
		}
	}
	// treap(const treap&l){
	// 	e_put(copy(l.e_get()));
	// }
	treap(treap&&l){
		auto t=e_get();
		e_put(l.e_get());
		l.e_put(t);
	}
	auto&operator=(treap&&l){
		auto t=e_get();
		e_put(l.e_get());
		l.e_put(t);
		return *this;
	}
	auto&operator=(const treap&l){
		if (e_get()!=l.e_get()){
			del(_e);
			_e=nullptr;
			for (auto&w:l){
				e_put(merge(e_get(),new auto (el(w))));
			}

			// _e=copy(l.e_get());
		}
		return *this;
	}
	~treap(){
		del(_e);
	}
	int64_t size()const{
		return e_get()?e_get()->s:0;
	}

	void rev(){
		e_get()?const_cast<long&>(e_get()->rev)^=1:0;
	}

	bool is_forward(){
		if (e_get()){
			e_get()->make();
		}
		return e_get()?e_get()->is_forward:1;
	}

	bool is_backward(){
		if (e_get()){
			e_get()->make();
		}
		return e_get()?e_get()->is_backward:1;
	}

	const T&operator[](int64_t n){
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e_get(),n)->v;
	}

	const T&operator[](int64_t n)const{
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e_get(),n)->v;
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
		_e=(merge(q.e_get(),e_get()));
		q._e=(nullptr);
		if(_e){_e->make();};
		if(q._e){q._e->make();};
	}
	void add_right(treap<T>&q){
		_e=merge(e_get(),q.e_get());
		q._e=nullptr;
		if(_e){_e->make();};
		if(q._e){q._e->make();};
	}
	treap<T> cut_left(int64_t n){
		assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),n);
		assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=(tmp.second);
		auto r=treap<T>();
		r._e=(tmp.first);
		if(_e){_e->make();};
		if(r._e){r._e->make();};
		return r;
	}
	treap<T> cut_right(int64_t n){
		assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),size()-n);
		assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=tmp.first;
		auto r=treap<T>();
		r._e=(tmp.second);
		if(_e){_e->make();};
		if(r._e){r._e->make();};
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
		_e=(merge(e_get(),new auto(el(a))));
		if(_e){_e->make();};
	}
	void push_front(const T&a){
		_e=(merge(new auto(el(a)),e_get()));
		if(_e){_e->make();};
	}
	template<typename...Y>
	void emplace_back(const Y&...a){
		_e=(merge(e_get(),new auto(el(a...))));
		if(_e){_e->make();};
	}
	template<typename...Y>
	void emplace_front(const Y&...a){
		_e=(merge(new auto(el(a...)),e_get()));
		if(_e){_e->make();};
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
		to_list(e_get(),q);
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
		del(e_get());
		_e=nullptr;
	}
	bool empty(){
		return !e_get();
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
		const T&operator*(){
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
	auto begin()const{
		if (!e_get()){
			return iter{e_get(),0};
		}
		const el* q=e_get();
		while (q->z_get()){
			q=q->z_get();
		}
		return iter{q,0};
	}
	auto end()const{
		if (!e_get()){
			return iter{e_get(),0};
		}
		const el* q=e_get();
		while (q->x_get()){
			q=q->x_get();
		}
		return iter{q,1};
	}
	auto rbegin()const{
		auto q=end()-1;
		q.d=-1;
		return q;
	}
	auto rend()const{
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
		return begin()+insert(find_index(n.e_get()),q);
	}
	template<typename TT>
	auto erase(TT n)->typename TT::template is_iterator<iter>{
		return begin()+erase(find_index(n.e_get()));
	}
	auto insert(int64_t n,treap<T>&q){
		auto w=cut_left(n);
		add_left(q);
		add_left(w);
		return n;
	}
	template<typename TT>
	auto insert(TT n,treap<T>&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(find_index(n.e_get()),q);
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
	// template <typename Y>
	// friend void swap(treap&q,treap&e);
	iter lower_bound(const T&d){
		if (is_forward()){
			iter t;
			// auto q=e_get();
			// if (!q){
			// 	t=begin();
			// }else
			// if (d<=q->first){
			// 	t=begin();
			// }else
			// if (d>q->last){
			// 	t=end();
			// }else{
			// 	auto w=q;
			// 	w=q;
			// 	while(q){
			// 		if (q->v>=d){
			// 			w=q;
			// 			q=q->z_get();
			// 		}else{
			// 			w=q;
			// 			q=q->x_get();
			// 		}
			// 	}
			// 	t={w,0};
			// }
			// while(*t>=d){
			// 	--t;
			// }
			// while(*t<d){
			// 	++t;
			// }
			// iter y=std::lower_bound(begin(),end(),d);
			// assert(t==y);
			t=begin()+bisect(0,size(),(*this)[__center]>=d);
			// y=iter
			return t;
		// }else
		// if (is_backward()){
		// 	auto p=std::upper_bound(rbegin(),rend(),d);
		// 	--p;
		// 	p.d=1;
		// 	return p;
		}else{
			assert(0);
		}
		assert(0);
		return std::lower_bound(begin(),end(),d);
	}
	iter upper_bound(const T&d){
		if (is_forward()){
			// auto q=e_get();
			// auto w=q;
			// w=nullptr;
			// while(q){
			// 	if (q->v>d){
			// 		w=q;
			// 		q=q->z_get();
			// 	}else{
			// 		q=q->x_get();
			// 	}
			// }
			// return {w,0};
			return std::upper_bound(begin(),end(),d);
		// }else
		// if (is_backward()){
		// 	auto p=std::lower_bound(rbegin(),rend(),d);
		// 	--p;
		// 	p.d=1;
		// 	return p;
		}else{
			assert(0);
		}
		assert(0);
		return std::upper_bound(begin(),end(),d);
	}
	bool next_permutation(){
		// out();
		auto q=bisect(0,size(),({
			auto t=cut_left(__center);
			bool r=is_backward();
			// t.out();
			// out();
			// ic(__center,r)
			add_left(t);
			// out();
			r;
		}));
		auto t=cut_left(q);
		// ic(t,*this)
		if (t.size()){
			auto r=t.end()[-1];
			t.erase(t.size()-1);
			rev();
			auto p=upper_bound(r)-begin();
			assert(size()>p);
			insert(p,r);
			assert(size()+1>p);
			assert(r<(*this)[p+1]);
			r=(*this)[p+1];
			erase(p+1);
			t.push_back(r);
			add_left(t);
			return 1;
		}else{
			rev();
			return 0;
		}
	}
	bool prev_permutation(){
		auto q=bisect(0,size(),({
			auto t=cut_left(__center);
			bool r=is_forward();
			add_left(t);
			r;
		}));
		auto t=cut_left(q);
		if (t.size()){
			auto r=t.end()[-1];
			t.erase(t.size()-1);
			assert(is_forward());
			auto p=lower_bound(r)-begin();
			assert(r>(*this)[p-1]);
			insert(p,r);
			r=(*this)[p-1];
			erase(p-1);
			t.push_back(r);
			rev();
			add_left(t);
			return 1;
		}else{
			rev();
			return 0;
		}
		return 0;
	}
	T sum(){
		if (e_get()){
			return e_get()->sum;
		}else{
			return 0;
		}
	}
	void add(long v){
		if (e_get()){
			const_cast<long&>(e_get()->to_add)+=v;
		}
	}
	void mul(long v){
		if (e_get()){
			const_cast<long&>(e_get()->to_mul)*=v;
		}
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

// template <typename T>
// void swap(treap<T>&q,treap<T>&e){
// 	auto w=q.cut_left(q.size());
// 	q.add_left(e);
// 	e.add_left(w);
// }

template<typename TT>
auto operator-(TT q,TT w)->typename TT::template is_iterator<ptrdiff_t>{
	assert(q.d==w.d);
	if (q==w){
		return 0;
	}
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
#undef get
// #include "treap.hpp"

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
#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
#define back(a) ((a)[len(a)-1])

static inline int64_t getint() {
	int sign = 1;
	int c;
	size_t res = 0;
	while (c = getchar_unlocked(), isspace(c))
		;
	if (c==EOF){return -1;}
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

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

int main(){
	uint64_t n=getint();
	treap<long> a;
	for (uint64_t w=0;w<n;++w){
		a.push_back(getint());
	}
	while (1){
		uint64_t q=getint();
		if (q==-1){
			break;
		}
		if (q==1){
			uint64_t l=getint(),r=getint()+1;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			print(s.sum());
			s.add_left(d);
			a.add_left(s);
		}
		if (q==2){
			long x=getint();
			uint64_t u=getint();
			a.insert(u,x);
		}
		if (q==3){
			uint64_t u=getint();
			a.erase(u);
		}
		if (q==4){
			long x=getint();
			uint64_t l=getint(),r=getint()+1;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.mul(0);
			s.add(x);
			s.add_left(d);
			a.add_left(s);
		}
		if (q==5){
			long x=getint();
			uint64_t l=getint(),r=getint()+1;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.add(x);
			s.add_left(d);
			a.add_left(s);
		}
		if (q==6){
			uint64_t l=getint(),r=getint()+1;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.next_permutation();
			s.add_left(d);
			a.add_left(s);
		}
		if (q==7){
			uint64_t l=getint(),r=getint()+1;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.prev_permutation();
			s.add_left(d);
			a.add_left(s);
		}
	}
	for (uint64_t w=0;w<a.size();++w){
		write(a[w]);
	}
	putchar(10);
}
