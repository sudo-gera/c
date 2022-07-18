#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <iostream>

#ifdef assert_m
	#ifdef assert
		#undef assert
	#endif
	#define assert assert_m
#else
	#include <assert.h>
#endif

#define get(a) auto a##_z=a?a->z_get():0;auto a##_x=a?a->x_get():0;auto a##_z_s=a##_z?a##_z->s:0;auto a##_x_s=a##_x?a##_x->s:0;

class treap{
private:
	struct el{
		int64_t v;
		int64_t w;
		el const*const z=nullptr;
		el const*const x=nullptr;
		el const*const p=nullptr;
		int64_t const s=1;
		int64_t const d=1;
		int64_t const rev=0;
		int64_t const first=0;
		int64_t const last=0;
		int64_t const sum=0;
		int64_t const to_add=0;
		int64_t const to_mul=1;
		int64_t const is_forward=1;
		int64_t const is_backward=1;
		template<typename...Y>
		el(const Y&..._v):v(_v...),w(rand()){update();}

		template<typename y>
		void z_put(y q)const{
			const_cast<const el*&>(z)=q;
			update();
		}

		template<typename y>
		void x_put(y q)const{
			const_cast<const el*&>(x)=q;
			update();
		}

		auto z_get()const{
			if (z){
				z->make();
			}
			return z;
		}

		auto x_get()const{
			if (x){
				x->make();
			}
			return x;
		}

		void setroot()const{
			const_cast<const el*&>(p)=nullptr;
		}

		void make()const{
			if (to_mul!=1){
				const_cast<int64_t&>(sum)*=to_mul;
				const_cast<int64_t&>(first)*=to_mul;
				const_cast<int64_t&>(last)*=to_mul;
				const_cast<int64_t&>(v)*=to_mul;
				if (z){
					const_cast<int64_t&>(z->to_mul)*=to_mul;
					const_cast<int64_t&>(z->to_add)*=to_mul;
				}
				if (x){
					const_cast<int64_t&>(x->to_mul)*=to_mul;
					const_cast<int64_t&>(x->to_add)*=to_mul;
				}
				if (to_mul==0){
					const_cast<int64_t&>(is_forward)=1;
					const_cast<int64_t&>(is_backward)=1;
				}
				const_cast<int64_t&>(to_mul)=1;
			}

			if (to_add!=0){
				const_cast<int64_t&>(sum)+=to_add*s;
				const_cast<int64_t&>(first)+=to_add;
				const_cast<int64_t&>(last)+=to_add;
				const_cast<int64_t&>(v)+=to_add;
				if (z){
					const_cast<int64_t&>(z->to_add)+=to_add;
				}
				if (x){
					const_cast<int64_t&>(x->to_add)+=to_add;
				}
				const_cast<int64_t&>(to_add)=0;
			}

			if (rev){
				const el*te=const_cast<const el*&>(z);
				const_cast<const el*&>(z)=const_cast<const el*&>(x);
				const_cast<const el*&>(x)=te;
				int64_t tl=const_cast<int64_t&>(is_forward);
				const_cast<int64_t&>(is_forward)=const_cast<int64_t&>(is_backward);
				const_cast<int64_t&>(is_backward)=tl;
				tl=const_cast<int64_t&>(first);
				const_cast<int64_t&>(first)=const_cast<int64_t&>(last);
				const_cast<int64_t&>(last)=tl;
				if (z){
					const_cast<int64_t&>(z->rev)^=1;
				}
				if (x){
					const_cast<int64_t&>(x->rev)^=1;
				}
				const_cast<int64_t&>(rev)=0;
			}
		}
		void update()const{
			if (z){
				const_cast<const el*&>(z->p)=this;
				if (z->rev){
					const_cast<int64_t&>(first)=z->last*z->to_mul+z->to_add;
				}else{
					const_cast<int64_t&>(first)=z->first*z->to_mul+z->to_add;
				}
			}else{
				const_cast<int64_t&>(first)=v;
			}
			if (x){
				const_cast<const el*&>(x->p)=this;
				if (x->rev){
					const_cast<int64_t&>(last)=x->first*x->to_mul+x->to_add;
				}else{
					const_cast<int64_t&>(last)=x->last*x->to_mul+x->to_add;
				}
			}else{
				const_cast<int64_t&>(last)=v;
			}
			if (z and x){
				int64_t s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
				int64_t s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
				int64_t s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
				int64_t s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
				int64_t s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
				int64_t s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
				int64_t s_z_s=z->s;
				int64_t s_x_s=x->s;
				const_cast<int64_t&>(s)=z->s+x->s+1;
				const_cast<int64_t&>(d)=1+(z->d>x->d?z->d:x->d);
				const_cast<int64_t&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s + x->sum*x->to_mul+x->to_add*x->s;
				const_cast<int64_t&>(is_forward)=(s_z_forward and s_x_forward and s_z_last<=v and s_x_first>=v);
				const_cast<int64_t&>(is_backward)=(s_z_backward and s_x_backward and s_z_last>=v and s_x_first<=v);
			}else
			if (z){
				int64_t s_x_forward=1;
				int64_t s_x_backward=1;
				int64_t s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
				int64_t s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
				int64_t s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
				int64_t s_x_first=0;
				int64_t s_z_s=z->s;
				int64_t s_x_s=0;
				const_cast<int64_t&>(s)=z->s+1;
				const_cast<int64_t&>(d)=z->d+1;
				const_cast<int64_t&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s;
				const_cast<int64_t&>(is_forward)=(s_z_forward and s_z_last<=v);
				const_cast<int64_t&>(is_backward)=(s_z_backward and s_z_last>=v);
			}else
			if (x){
				int64_t s_z_forward=1;
				int64_t s_z_backward=1;
				int64_t s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
				int64_t s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
				int64_t s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
				int64_t s_z_last=0;
				int64_t s_z_s=0;
				int64_t s_x_s=x->s;
				const_cast<int64_t&>(s)=x->s+1;
				const_cast<int64_t&>(d)=x->d+1;
				const_cast<int64_t&>(sum)=v + x->sum*x->to_mul+x->to_add*x->s;
				const_cast<int64_t&>(is_forward)=(s_x_forward and s_x_first>=v);
				const_cast<int64_t&>(is_backward)=(s_x_backward and s_x_first<=v);
			}else{
				const_cast<int64_t&>(s)=1;
				const_cast<int64_t&>(d)=1;
				const_cast<int64_t&>(sum)=v;
				const_cast<int64_t&>(is_forward)=1;
				const_cast<int64_t&>(is_backward)=1;
			}
			if (d>128){
				std::cerr<<"bamboo!! "<<d<<std::endl;
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
		// int64_t elsize(){
		// 	return el_size(this);
		// }
	};

	static void check(const el*s){
		if (__FILE__[0]!='int64_t'){
			return;
		}
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
			if (n==s_z_s){
				return s;
			}
			if (n<s_z_s){
				return get_by_index(s_z,n);
			}
			if (n>s_z_s){
				return get_by_index(s_x,n-s_z_s-1);
			}
		}
		assert(0);
		return (el*)(nullptr);
	}

	static void to_list(const el* q,std::vector<int64_t>&a){
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

	static auto pri(const el* root,int64_t*prev_node=0){
		if (!root){
			return;
		}
		const el*left;
		const el*right;
		left=root->z;
		right=root->x;

		int64_t node[3];
		node[2]=(int64_t)NULL;
		node[0]=(int64_t)prev_node;
		if (prev_node){
			prev_node[2]=(int64_t)node;
		}

		int64_t save=0;
		if (prev_node and prev_node[1]==2){
			save=prev_node[1];
			prev_node[1]=0;
		}
		node[1]=2;
		pri(left,node);
		if (save){
			prev_node[1]=save;
		}

		int64_t*d=node;
		while(d[0]){
			d=(int64_t*)d[0];
		}

		for (;d!=node;d=(int64_t*)d[2]){
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

		_put(v)
		_put(to_mul)
		_put(to_add)
		_put(is_forward)
		_put(is_backward)
		_put(forward_prefix)
		_put(backward_prefix)
		_put(forward_suffix)
		_put(backward_suffix)
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

	static std::pair<const el*,const el*> split(const el* int64_t,int64_t n){
		if (!int64_t){
			return {nullptr,nullptr};
		}
		if (n==0){
			return {nullptr,int64_t};
		}
		if (n==int64_t->s){
			return {int64_t,nullptr};
		}
		get(int64_t);
		if (t_z_s<n){
			auto tmp=split(t_x,n-t_z_s-1);
			int64_t->x_put(tmp.first);
			auto t2=tmp.second;
			if (t2){
				const_cast<const el*&>(t2->p)=nullptr;
			}
			return {int64_t,t2};
		}else{
			auto tmp=split(t_z,n);
			auto t1=tmp.first;
			int64_t->z_put(tmp.second);
			if (t1){
				const_cast<const el*&>(t1->p)=nullptr;
			}
			return {t1,int64_t};
		}
	}

	static std::pair<const el*,int64_t> add(const el*q,int64_t n){
		int64_t o=0;
		get(q);
		while(n){
			auto w=q->p;
			get(w);
			if (n>0){
				if (q_x_s>=n){
					n=n-1;
					q=get_by_index(q_x,n);
					break;
				}else{
					if (w==nullptr){
						o+=n-q_x_s;
						n=q_x_s;
						continue;
					}else if (w_z==q){
						n=-q_x_s-1+n;
						q=w;
						q_x=w_x;
						q_z=w_z;
						continue;
					}else if (w_x==q){
						n=q_z_s+1+n;
						q=w;
						q_x=w_x;
						q_z=w_z;
						continue;
					}
					assert(0);
				}
			}else if (n<0){
				if (-q_z_s<=n){
					n=q_z_s+n;
					q=get_by_index(q_z,n);
					break;
				}else{
					if (w==nullptr){
						o+=n+q_z_s;
						n=-q_z_s;
						continue;
					}else if (w_z==q){
						n=-q_x_s-1+n;
						q=w;
						q_x=w_x;
						q_z=w_z;
						continue;
					}else if (w_x==q){
						n=q_z_s+1+n;
						q=w;
						q_x=w_x;
						q_z=w_z;
						continue;
					}
					assert(0);
				}
			}
		}
		return {q,o};
	}

	const el* _e=nullptr;
	const el* e_get()const{
		check(_e);
		if(_e){_e->make();};
		return _e;
	}
public:
	void out(){
		pri(_e);
	}
	template <typename y=std::initializer_list<int64_t>>
	treap(const y&l=std::initializer_list<int64_t>(),
		std::enable_if_t<
			std::is_same_v<
				typename y::value_type,int64_t
			> and std::is_copy_constructible_v<int64_t>
			and std::is_same_v<decltype(l.begin()!=l.end()),bool>
			,int> =0){
		for (auto&w:l){
			_e=(merge(e_get(),new auto (el(w))));
		}
	}
	template <typename y=int>
	treap(y=0,
		std::enable_if_t<!std::is_copy_constructible_v<int64_t>
			,y> =0){
	}
	template<typename y=int64_t>
	treap(std::enable_if_t<
			std::is_trivially_constructible_v<int64_t>
		,y> l){
		for (int64_t w=0;w<l;++w){
			_e=(merge(e_get(),new auto (el(int64_t()))));
		}
	}
	treap(const treap&l){
		for (auto&w:l){
			_e=(merge(e_get(),new auto (el(w))));
		}
	}
	treap(treap&&l){
		auto int64_t=e_get();
		_e=(l.e_get());
		l._e=(int64_t);
	}
	auto&operator=(treap&&l){
		auto int64_t=e_get();
		_e=(l.e_get());
		l._e=(int64_t);
		return *this;
	}
	auto&operator=(const treap&l){
		if (e_get()!=l.e_get()){
			del(_e);
			_e=nullptr;
			for (auto&w:l){
				_e=(merge(e_get(),new auto (el(w))));
			}
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
		e_get()?const_cast<int64_t&>(e_get()->rev)^=1:0;
	}

	bool is_forward(){
		return e_get()?e_get()->is_forward:1;
	}

	bool is_backward(){
		return e_get()?e_get()->is_backward:1;
	}

	const int64_t&operator[](int64_t n){
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e_get(),n)->v;
	}

	const int64_t&operator[](int64_t n)const{
		if (n<0){
			n+=this->size();
		}
		assert(n<size());
		assert(n>=0);
		return get_by_index(e_get(),n)->v;
	}
// private:
// 	int64_t __cmp__(const treap&d)const{
// 		auto&s=*this;
// 		int64_t min_len=d.size()<s.size()?d.size():s.size();
// 		for (int64_t w=0;w<min_len;++w){
// 			if (s[w]<d[w]){
// 				return -1;
// 			}
// 			if (s[w]>d[w]){
// 				return 1;
// 			}
// 		}
// 		if (s.size()>d.size()){
// 			return 1;
// 		}
// 		if (s.size()<d.size()){
// 			return -1;
// 		}
// 		return 0;
// 	}
public:
	void add_left(treap<int64_t>&q){
		_e=(merge(q.e_get(),e_get()));
		q._e=(nullptr);
	}
	void add_right(treap<int64_t>&q){
		_e=merge(e_get(),q.e_get());
		q._e=nullptr;
	}
	treap<int64_t> cut_left(int64_t n){
		// assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),n);
		// assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=(tmp.second);
		auto r=treap<int64_t>();
		r._e=(tmp.first);
		return r;
	}
	treap<int64_t> cut_right(int64_t n){
		// assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),size()-n);
		// assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=tmp.first;
		auto r=treap<int64_t>();
		r._e=(tmp.second);
		return r;
	}
	treap<int64_t> cut(int64_t l,int64_t r){
		assert(0<=l and l<=r and  r<=size());
		auto q=cut_left(l);
		auto w=cut_left(r-l);
		add_left(q);
		return w;
	}
	void push_back(const int64_t&a){
		_e=(merge(e_get(),new auto(el(a))));
		// if(_e){_e->make();};
	}
	void push_front(const int64_t&a){
		_e=(merge(new auto(el(a)),e_get()));
		// if(_e){_e->make();};
	}
	template<typename...Y>
	void emplace_back(const Y&...a){
		_e=(merge(e_get(),new auto(el(a...))));
		// if(_e){_e->make();};
	}
	template<typename...Y>
	void emplace_front(const Y&...a){
		_e=(merge(new auto(el(a...)),e_get()));
		// if(_e){_e->make();};
	}
	int64_t pop_back(){
		auto q=cut_right(1);
		return q[0];
	}
	int64_t pop_front(){
		auto q=cut_left(1);
		return q[0];
	}
	operator std::vector<int64_t>()const{
		auto q=std::vector<int64_t>();
		to_list(e_get(),q);
		return q;
	}
	friend std::ostream&operator<<(std::ostream&q,const treap&w){
		auto r=std::vector<int64_t>(w);
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
	int64_t&front(){
		return (*this)[0];
	}
	const int64_t&front()const{
		return (*this)[0];
	}
	int64_t&back(){
		return (*this)[this->size()-1];
	}
	const int64_t&back()const{
		return (*this)[this->size()-1];
	}
	struct iter {
		using difference_type = std::ptrdiff_t;
		using value_type = int64_t;
		using pointer = int64_t*;
		using reference = int64_t&;
		using iterator_category = std::random_access_iterator_tag;
		template<typename Y>
		using is_iterator=Y;
		using original_type=treap<int64_t>;
		const el*e=nullptr;
		int64_t o=0;
		int64_t d=1;
		const int64_t&operator*(){
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
		auto&operator+=(int64_t w){
			w*=d;
			w+=o;
			if (!e){
				return *this;
			}
			auto int64_t=add(e,w);
			e=int64_t.first;
			o=int64_t.second;
			return *this;
		}
		auto&operator-=(int64_t w){
			return *this+=(-w);
		}
		auto&operator[](int64_t q){
			return *(*this+q);
		}
		auto& operator=(const iter&q){
			e=q.e;
			o=q.o;
			d=q.d;
			return *this;
		}
		int64_t find_index(){
			return e->nz_find_index()+o;
		}
	};
	auto begin()const{
		if (!e_get()){
			return iter{e_get(),0};
		}
		const el* q=e_get();
		while (q->z_get()){
			q=q->z;
		}
		return iter{q,0};
	}
	auto end()const{
		if (!e_get()){
			return iter{e_get(),0};
		}
		const el* q=e_get();
		while (q->x_get()){
			q=q->x;
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
	using value_type=int64_t;
	auto insert(int64_t n,const int64_t&q){
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
	auto update(int64_t n,const int64_t&q){
		auto w=cut_left(n);
		auto r=cut_left(1);
		auto int64_t=r[0];
		push_front(q);
		add_left(w);
		return int64_t;
	}
	template<typename TT>
	auto insert(TT n,const int64_t&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(find_index(n.e_get()),q);
	}
	template<typename TT>
	auto update(TT n,const int64_t&q)->typename TT::template is_iterator<iter>{
		return update(find_index(n.e_get()),q);
	}
	template<typename TT>
	auto erase(TT n)->typename TT::template is_iterator<iter>{
		return begin()+erase(find_index(n.e_get()));
	}
	auto insert(int64_t n,treap<int64_t>&q){
		auto w=cut_left(n);
		add_left(q);
		add_left(w);
		return n;
	}
	template<typename TT>
	auto insert(TT n,treap<int64_t>&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(find_index(n.e_get()),q);
	}
	void resize(int64_t n){
		for (int64_t w=size();w<n;++w){
			push_back(int64_t());
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
	iter lower_bound(const int64_t&d){
		if (is_forward()){
			iter int64_t,y;
			auto q=e_get();
			if (!q){
				int64_t=begin();
			}else
			if (d<=q->first){
				int64_t=begin();
			}else
			if (d>q->last){
				int64_t=end();
			}else{
				assert(q);
				auto w=q;
				w=nullptr;
				while(q){
					if (q->v>=d){
						w=q;
						q=q->z_get();
					}else{
						q=q->x_get();
					}
				}
				int64_t={w,0};
			}
			return int64_t;
		}else{
			assert(0);
		}
		assert(0);
		return iter{};
	}
	iter upper_bound(const int64_t&d){
		if (is_forward()){
			iter int64_t;
			auto q=e_get();
			if (!q){
				int64_t=begin();
			}else
			if (d<q->first){
				int64_t=begin();
			}else
			if (d>=q->last){
				int64_t=end();
			}else{
				assert(q);
				auto w=q;
				w=nullptr;
				while(q){
					if (q->v>d){
						w=q;
						q=q->z_get();
					}else{
						q=q->x_get();
					}
				}
				int64_t=iter{w,0};
			}
			return int64_t;
		}else{
			assert(0);
		}
		assert(0);
		return iter{};
	}
	auto forward_prefix(){
		iter int64_t;
		auto q=e_get();
		auto w=q;
		w=nullptr;
		if (!q or q->is_forward){
			int64_t=end();
		}else{
			while (q){
				get(q);
				if (!q_z or q_z->is_forward){
					if (!q_z or q->v>=q_z->last){
						if (!w or w->v<=q->first){
							w=q;
						}else{
							int64_t={w,0};
							++int64_t;
							break;
						}
						q=q_x;
					}else{
						if (!w or w->v<=q->first){
							w=q;
							int64_t={w,0};
							break;
						}else{
							int64_t={w,0};
							++int64_t;
							break;
						}
					}
				}else{
					q=q_z;
				}
			}
			if (!int64_t.e){
				int64_t={w,0};
				++int64_t;
			}
		}
		return int64_t;
	}
	auto backward_prefix(){
		iter int64_t;
		auto q=e_get();
		auto w=q;
		w=nullptr;
		if (!q or q->is_backward){
			int64_t=end();
		}else{
			while (q){
				get(q);
				if (!q_z or q_z->is_backward){
					if (!q_z or q->v<=q_z->last){
						if (!w or w->v>=q->first){
							w=q;
						}else{
							int64_t={w,0};
							++int64_t;
							break;
						}
						q=q_x;
					}else{
						if (!w or w->v>=q->first){
							w=q;
							int64_t={w,0};
							break;
						}else{
							int64_t={w,0};
							++int64_t;
							break;
						}
					}
				}else{
					q=q_z;
				}
			}
			if (!int64_t.e){
				int64_t={w,0};
				++int64_t;
			}
		}
		return int64_t;
	}
	bool next_permutation(){
		rev();
		auto q=forward_prefix().find_index();
		// assert(q==e_get()->forward_prefix);
		rev();
		// assert(q==e_get()->backward_suffix);
		q=size()-q;
		auto int64_t=cut_left(q);
		if (int64_t.size()){
			auto r=int64_t.pop_back();
			rev();
			auto p=upper_bound(r).find_index();
			// assert(size()>p);
			r=update(p,r);
			int64_t.push_back(r);
			add_left(int64_t);
			return 1;
		}else{
			rev();
			return 0;
		}
	}
	bool prev_permutation(){
		rev();
		auto q=backward_prefix().find_index();
		rev();
		q=size()-q;
		auto int64_t=cut_left(q);
		if (int64_t.size()){
			auto r=int64_t.pop_back();
			assert(is_forward());
			auto p=lower_bound(r).find_index();
			// assert(r>(*this)[p-1]);
			r=update(p-1,r);
			int64_t.push_back(r);
			rev();
			add_left(int64_t);
			return 1;
		}else{
			rev();
			return 0;
		}
		return 0;
	}
	int64_t sum(){
		if (e_get()){
			return _e->sum;
		}else{
			return 0;
		}
	}
	void add(int64_t v){
		if (e_get()){
			const_cast<int64_t&>(_e->to_add)+=v;
		}
	}
	void mul(int64_t v){
		if (e_get()){
			const_cast<int64_t&>(_e->to_mul)*=v;
		}
	}
};

template<typename TT>
auto operator-(TT q,TT w)->typename TT::template is_iterator<ptrdiff_t>{
	assert(q.d==w.d);
	if (q==w){
		return 0;
	}
	return ((q.e)->nz_find_index()-(w.e)->nz_find_index()+q.o-w.o)*q.d;
}

template<typename TT>
auto operator+(TT q,int64_t w)->typename TT::template is_iterator<TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator-(TT q,int64_t w)->typename TT::template is_iterator<TT>{
	auto e=q;
	e-=w;
	return e;
}

template<typename TT>
auto operator+(int64_t w,TT q)->typename TT::template is_iterator<TT>{
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

int main(){
	int64_t n;
	std::cin>>n;
	treap<int64_t> a;
	for (int64_t w=0;w<n;++w){
		int64_t int64_t;
		std::cin>>int64_t;
		a.push_back(int64_t);
	}
	int64_t qq;
	std::cin>>qq;
	for (int64_t w=0;w<qq;++w){
		int64_t q;
		std::cin>>q;
		if (q==-1){
			break;
		}
		if (q==1){
			int64_t l,r;
			std::cin>>l>>r;
			++r;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			std::cout<<s.sum()<<std::endl;
			s.add_left(d);
			a.add_left(s);
		}
		if (q==2){
			int64_t x;
			int64_t u;
			std::cin>>x>>u;
			a.insert(u,x);
		}
		if (q==3){
			int64_t u;
			std::cin>>u;
			a.erase(u);
		}
		if (q==4){
			int64_t x;
			std::cin>>x;
			int64_t l,r;
			std::cin>>l;
			std::cin>>r;
			++r;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.mul(0);
			s.add(x);
			s.add_left(d);
			a.add_left(s);
		}
		if (q==5){
			int64_t x;
			std::cin>>x;
			int64_t l,r;
			std::cin>>l>>r;
			++r;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.add(x);
			s.add_left(d);
			a.add_left(s);
		}
		if (q==6){
			int64_t l,r;
			std::cin>>l>>r;
			++r;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.next_permutation();
			s.add_left(d);
			a.add_left(s);
		}
		if (q==7){
			int64_t l,r;
			std::cin>>l>>r;
			++r;
			auto s=a.cut_left(r);
			auto d=s.cut_left(l);
			s.prev_permutation();
			s.add_left(d);
			a.add_left(s);
		}
	}
	for (int64_t w=0;w<a.size();++w){
		std::cout<<a[w]<<' ';
	}
	putchar(10);
}
