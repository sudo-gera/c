#include <bits/stdc++.h>
using namespace std;


#ifdef assert_m
#define assert assert_m
#endif

#define get(a) auto a##_z=a?a->z_get():0;auto a##_x=a?a->x_get():0;auto a##_z_s=a##_z?a##_z->s:0;auto a##_x_s=a##_x?a##_x->s:0;

struct el{
	int64_t v=0;
	int64_t w=0;
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
	template<typename Y>
	el(const Y& _v):v(_v),w(rand()){update();}

	el(){}

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
		get(q);
		if (w==nullptr){
			return q_z_s;
		}else if (w->z_get()==q){
			return w->nz_find_index()-q_x_s-1;
		}else if (w->x_get()==q){
			return w->nz_find_index()+q_z_s+1;
		}
		assert(0);
		return 0;
	}
};
const el* get_by_index(const el*s,int64_t n){
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
std::pair<const el*,int64_t> add(const el*q,int64_t n){
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
struct iter {
	const el*e=nullptr;
	int64_t o=0;
	const int64_t&operator*(){
		return e->v;
	}
	auto&operator+=(int64_t w){
		w+=o;
		if (!e){
			return *this;
		}
		auto t=add(e,w);
		e=t.first;
		o=t.second;
		return *this;
	}
	auto&operator-=(int64_t w){
		return *this+=(-w);
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
	auto&operator[](int64_t q){
		auto t=*this;
		t+=q;
		return *t;
	}
	auto& operator=(const iter&q){
		e=q.e;
		o=q.o;
		return *this;
	}
	int64_t find_index(){
		return e->nz_find_index()+o;
	}
};

void check(const el*s){
	#if !__has_include("d")
		return;
	#endif
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

pair<const el*,const el*> be(const el*q){
	if (!q){
		return {q,q};
	}
	const el*b=q,*e=q;
	while (b->z_get()){
		b=b->z;
	}
	while(e->x_get()){
		e=e->x;
	}
	return {b,e};
}

int64_t el_size(const el*s){
	return s?s->s:0;
}

void del(const el* q){
	if (!q){
		return;
	}
	del(q->z);
	del(q->x);
	delete q;
}

const el* merge(const el* t1,const el* t2){
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

std::pair<const el*,const el*> split(const el* t,int64_t n){
	if (!t){
		return {nullptr,nullptr};
	}
	if (n==0){
		return {nullptr,t};
	}
	if (n==t->s){
		return {t,nullptr};
	}
	get(t);
	if (t_z_s<n){
		auto tmp=split(t_x,n-t_z_s-1);
		t->x_put(tmp.first);
		auto t2=tmp.second;
		if (t2){
			const_cast<const el*&>(t2->p)=nullptr;
		}
		return {t,t2};
	}else{
		auto tmp=split(t_z,n);
		auto t1=tmp.first;
		t->z_put(tmp.second);
		if (t1){
			const_cast<const el*&>(t1->p)=nullptr;
		}
		return {t1,t};
	}
}


iter _lower_bound(const el*q,int64_t d){
	iter t,y;
	if (!q){
		t={be(q).first,0};
	}else
	if (d<=q->first){
		t={be(q).first,0};
	}else
	if (d>q->last){
		t={be(q).second,1};
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
		t={w,0};
	}
	return t;
}
iter _upper_bound(const el*q,int64_t d){
	iter t;
	if (!q){
		t={be(q).first,0};
	}else
	if (d<q->first){
		t={be(q).first,0};
	}else
	if (d>=q->last){
		t={be(q).second,1};
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
		t=iter{w,0};
	}
	return t;
}
iter _forward_prefix(const el*q){
	iter t;
	auto w=q;
	w=nullptr;
	if (!q or q->is_forward){
		t={be(q).second,bool(q)};
	}else{
		while (q){
			get(q);
			if (!q_z or q_z->is_forward){
				if (!q_z or q->v>=q_z->last){
					if (!w or w->v<=q->first){
						w=q;
					}else{
						t={w,0};
						++t;
						break;
					}
					q=q_x;
				}else{
					if (!w or w->v<=q->first){
						w=q;
						t={w,0};
						break;
					}else{
						t={w,0};
						++t;
						break;
					}
				}
			}else{
				q=q_z;
			}
		}
		if (!t.e){
			t={w,0};
			++t;
		}
	}
	return t;
}
iter _backward_prefix(const el*q){
	iter t;
	auto w=q;
	w=nullptr;
	if (!q or q->is_backward){
		t={be(q).second,bool(q)};
	}else{
		while (q){
			get(q);
			if (!q_z or q_z->is_backward){
				if (!q_z or q->v<=q_z->last){
					if (!w or w->v>=q->first){
						w=q;
					}else{
						t={w,0};
						++t;
						break;
					}
					q=q_x;
				}else{
					if (!w or w->v>=q->first){
						w=q;
						t={w,0};
						break;
					}else{
						t={w,0};
						++t;
						break;
					}
				}
			}else{
				q=q_z;
			}
		}
		if (!t.e){
			t={w,0};
			++t;
		}
	}
	return t;
}

const el* _next_permutation(const el* s__e){
	if (!s__e){
		return s__e;
	}
	const_cast<int64_t&>(s__e->rev)^=1;
	s__e->make();
	auto q=_forward_prefix(s__e).find_index();
	const_cast<int64_t&>(s__e->rev)^=1;
	s__e->make();
	q=(s__e?s__e->s:0)-q;
	auto tmp=split(s__e,q);
	auto t__e=tmp.first;
	s__e=tmp.second;
	if (t__e){
		auto tmp=split(t__e,t__e->s-1);
		t__e=tmp.first;
		auto h=tmp.second;
		auto r=h->v;
		const_cast<int64_t&>(s__e->rev)^=1;
		s__e->make();
		auto p=_upper_bound(s__e,r).find_index();
		tmp=split(s__e,p);
		auto z__e=tmp.first;
		s__e=tmp.second;
		tmp=split(s__e,1);
		auto x__e=tmp.first;
		s__e=tmp.second;
		auto tr=x__e->v;
		const_cast<int64_t&>(x__e->v)=r;
		x__e->update();
		r=tr;
		s__e=merge(x__e,s__e);
		x__e=nullptr;
		s__e=merge(z__e,s__e);
		z__e=nullptr;
		auto c__e=h;
		const_cast<int64_t&>(c__e->v)=r;
		c__e->update();
		t__e=merge(t__e,c__e);
		c__e=nullptr;
		s__e=merge(t__e,s__e);
		t__e=nullptr;
		return s__e;
	}else{
		const_cast<int64_t&>(s__e->rev)^=1;
		s__e->make();
		return s__e;
	}
}

const el* _prev_permutation(const el*s__e){
	if (!s__e){
		return s__e;
	}
	const_cast<int64_t&>(s__e->rev)^=1;
	s__e->make();
	auto q=_backward_prefix(s__e).find_index();
	const_cast<int64_t&>(s__e->rev)^=1;
	s__e->make();
	q=(s__e?s__e->s:0)-q;
	auto tmp=split(s__e,q);
	auto t__e=tmp.first;
	s__e=tmp.second;
	if (t__e){
		tmp=split(t__e,t__e->s-1);
		t__e=tmp.first;
		auto h=tmp.second;
		auto r=h->v;
		auto p=_lower_bound(s__e,r).find_index();
		tmp=split(s__e,p-1);
		auto z__e=tmp.first;
		s__e=tmp.second;
		tmp=split(s__e,1);
		auto x__e=tmp.first;
		s__e=tmp.second;
		auto tr=x__e->v;
		const_cast<int64_t&>(x__e->v)=r;
		x__e->update();
		r=tr;
		s__e=merge(x__e,s__e);
		x__e=nullptr;
		s__e=merge(z__e,s__e);
		z__e=nullptr;
		auto c__e=h;
		const_cast<int64_t&>(c__e->v)=r;
		c__e->update();
		t__e=merge(t__e,c__e);
		c__e=nullptr;
		const_cast<int64_t&>(s__e->rev)^=1;
		s__e->make();
		s__e=merge(t__e,s__e);
		t__e=nullptr;
		return s__e;
	}else{
		const_cast<int64_t&>(s__e->rev)^=1;
		s__e->make();
		return s__e;
	}
}


const el* _next_permutation(const el*s);
const el* _prev_permutation(const el*s);

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

int64_t getint(){
	int64_t l;
	std::cin>>l;
	return l;
}

///////////////////////////////////////////////////end of lib

int main(){
	pair<const el*,const el*> tmp;
	uint64_t n=getint();
	const el* a__e;
	for (uint64_t w=0;w<n;++w){
		a__e=merge(a__e,new auto(el(getint())));
	}
	uint64_t qq=getint();
	for (uint64_t w=0;w<qq;++w){
		uint64_t q=getint();
		if (q==-1){
			break;
		}
		if (q==1){
			uint64_t l=getint(),r=getint()+1;
			tmp=split(a__e,r);
			auto s__e=tmp.first;
			a__e=tmp.second;
			tmp=split(s__e,l);
			auto d__e=tmp.first;
			s__e=tmp.second;
			cout<<(s__e?s__e->sum:0)<<'\n';
			s__e=merge(d__e,s__e);
			d__e=nullptr;
			a__e=merge(s__e,a__e);
			s__e=nullptr;
		}
		if (q==2){
			int64_t x=getint();
			uint64_t u=getint();
			tmp=split(a__e,u);
			auto z__e=tmp.first;
			a__e=tmp.second;
			auto s__e=new auto(el(x));
			a__e=merge(s__e,a__e);
			s__e=nullptr;
			a__e=merge(z__e,a__e);
			z__e=nullptr;
		}
		if (q==3){
			uint64_t u=getint();
			tmp=split(a__e,u);
			auto z__e=tmp.first;
			a__e=tmp.second;
			tmp=split(a__e,1);
			a__e=tmp.second;
			delete tmp.first;
			a__e=merge(z__e,a__e);
			z__e=nullptr;
		}
		if (q==4){
			int64_t x=getint();
			uint64_t l=getint(),r=getint()+1;
			tmp=split(a__e,r);
			auto s__e=tmp.first;
			a__e=tmp.second;
			tmp=split(s__e,l);
			auto d__e=tmp.first;
			s__e=tmp.second;
			s__e?const_cast<int64_t&>(s__e->to_mul)*=0:0;
			s__e?const_cast<int64_t&>(s__e->to_add)+=x:0;
			s__e->make();
			s__e=merge(d__e,s__e);
			d__e=nullptr;
			a__e=merge(s__e,a__e);
			s__e=nullptr;
		}
		if (q==5){
			int64_t x=getint();
			uint64_t l=getint(),r=getint()+1;
			tmp=split(a__e,r);
			auto s__e=tmp.first;
			a__e=tmp.second;
			tmp=split(s__e,l);
			auto d__e=tmp.first;
			s__e=tmp.second;
			s__e?const_cast<int64_t&>(s__e->to_add)+=x:0;
			s__e->make();
			s__e=merge(d__e,s__e);
			d__e=nullptr;
			a__e=merge(s__e,a__e);
			s__e=nullptr;
		}
		if (q==6){
			uint64_t l=getint(),r=getint()+1;
			tmp=split(a__e,r);
			auto s__e=tmp.first;
			a__e=tmp.second;
			tmp=split(s__e,l);
			auto d__e=tmp.first;
			s__e=tmp.second;
			s__e=_next_permutation(s__e);
			s__e=merge(d__e,s__e);
			d__e=nullptr;
			a__e=merge(s__e,a__e);
			s__e=nullptr;
		}
		if (q==7){
			uint64_t l=getint(),r=getint()+1;
			tmp=split(a__e,r);
			auto s__e=tmp.first;
			a__e=tmp.second;
			tmp=split(s__e,l);
			auto d__e=tmp.first;
			s__e=tmp.second;
			s__e=_prev_permutation(s__e);
			s__e=merge(d__e,s__e);
			d__e=nullptr;
			a__e=merge(s__e,a__e);
			s__e=nullptr;
		}
	}
	while (a__e){
		tmp=split(a__e,1);
		auto s__e=tmp.first;
		a__e=tmp.second;
		cout<<s__e->v<<' ';
		// delete s__e;
		s__e=nullptr;
	}
	cout<<endl;
}

