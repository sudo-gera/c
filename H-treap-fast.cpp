using ll=long long int;

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
#include <bits/stdc++.h>

#ifdef assert_m
#define assert assert_m
#endif

#define get(a) auto a##_s=a?a->s:0;auto a##_z=a?a->z_get():0;auto a##_x=a?a->x_get():0;auto a##_z_s=a##_z?a##_z->s:0;auto a##_x_s=a##_x?a##_x->s:0;

struct treap{
    struct el{
        ll v=0;
        ll w=0;
        el const*const z=nullptr;
        el const*const x=nullptr;
        el const*const p=nullptr;
        ll const s=1;
        ll const d=1;
        ll const rev=0;
        ll const first=0;
        ll const last=0;
        ll const sum=0;
        ll const to_add=0;
        ll const to_mul=1;
        ll const is_forward=1;
        ll const is_backward=1;
    
        el(){}
        el(ll t):
            v(t),
            w(rand())
        {
            update();
        }
        // el(ll t,ll y):
        //     v(t),
        //     w(y)
        // {
        //     update();
        // }

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

        void make()const{
            if (to_mul!=1){
                const_cast<ll&>(sum)*=to_mul;
                const_cast<ll&>(first)*=to_mul;
                const_cast<ll&>(last)*=to_mul;
                const_cast<ll&>(v)*=to_mul;
                if (z){
                    const_cast<ll&>(z->to_mul)*=to_mul;
                    const_cast<ll&>(z->to_add)*=to_mul;
                }
                if (x){
                    const_cast<ll&>(x->to_mul)*=to_mul;
                    const_cast<ll&>(x->to_add)*=to_mul;
                }
                if (to_mul==0){
                    const_cast<ll&>(is_forward)=1;
                    const_cast<ll&>(is_backward)=1;
                }
                const_cast<ll&>(to_mul)=1;
            }

            if (to_add!=0){
                const_cast<ll&>(sum)+=to_add*s;
                const_cast<ll&>(first)+=to_add;
                const_cast<ll&>(last)+=to_add;
                const_cast<ll&>(v)+=to_add;
                if (z){
                    const_cast<ll&>(z->to_add)+=to_add;
                }
                if (x){
                    const_cast<ll&>(x->to_add)+=to_add;
                }
                const_cast<ll&>(to_add)=0;
            }

            if (rev){
                const el*te=const_cast<const el*&>(z);
                const_cast<const el*&>(z)=const_cast<const el*&>(x);
                const_cast<const el*&>(x)=te;
                ll tl=const_cast<ll&>(is_forward);
                const_cast<ll&>(is_forward)=const_cast<ll&>(is_backward);
                const_cast<ll&>(is_backward)=tl;
                tl=const_cast<ll&>(first);
                const_cast<ll&>(first)=const_cast<ll&>(last);
                const_cast<ll&>(last)=tl;
                if (z){
                    const_cast<ll&>(z->rev)^=1;
                }
                if (x){
                    const_cast<ll&>(x->rev)^=1;
                }
                const_cast<ll&>(rev)=0;
            }
        }
        void update()const{
            if (z){
                const_cast<const el*&>(z->p)=this;
                if (z->rev){
                    const_cast<ll&>(first)=z->last*z->to_mul+z->to_add;
                }else{
                    const_cast<ll&>(first)=z->first*z->to_mul+z->to_add;
                }
            }else{
                const_cast<ll&>(first)=v;
            }
            if (x){
                const_cast<const el*&>(x->p)=this;
                if (x->rev){
                    const_cast<ll&>(last)=x->first*x->to_mul+x->to_add;
                }else{
                    const_cast<ll&>(last)=x->last*x->to_mul+x->to_add;
                }
            }else{
                const_cast<ll&>(last)=v;
            }
            if (z and x){
                ll s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
                ll s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
                ll s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
                ll s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
                ll s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
                ll s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
                ll s_z_s=z->s;
                ll s_x_s=x->s;
                const_cast<ll&>(s)=z->s+x->s+1;
                const_cast<ll&>(d)=1+(z->d>x->d?z->d:x->d);
                const_cast<ll&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s + x->sum*x->to_mul+x->to_add*x->s;
                const_cast<ll&>(is_forward)=(s_z_forward and s_x_forward and s_z_last<=v and s_x_first>=v);
                const_cast<ll&>(is_backward)=(s_z_backward and s_x_backward and s_z_last>=v and s_x_first<=v);
            }else
            if (z){
                ll s_x_forward=1;
                ll s_x_backward=1;
                ll s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
                ll s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
                ll s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
                ll s_x_first=0;
                ll s_z_s=z->s;
                ll s_x_s=0;
                const_cast<ll&>(s)=z->s+1;
                const_cast<ll&>(d)=z->d+1;
                const_cast<ll&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s;
                const_cast<ll&>(is_forward)=(s_z_forward and s_z_last<=v);
                const_cast<ll&>(is_backward)=(s_z_backward and s_z_last>=v);
            }else
            if (x){
                ll s_z_forward=1;
                ll s_z_backward=1;
                ll s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
                ll s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
                ll s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
                ll s_z_last=0;
                ll s_z_s=0;
                ll s_x_s=x->s;
                const_cast<ll&>(s)=x->s+1;
                const_cast<ll&>(d)=x->d+1;
                const_cast<ll&>(sum)=v + x->sum*x->to_mul+x->to_add*x->s;
                const_cast<ll&>(is_forward)=(s_x_forward and s_x_first>=v);
                const_cast<ll&>(is_backward)=(s_x_backward and s_x_first<=v);
            }else{
                const_cast<ll&>(s)=1;
                const_cast<ll&>(d)=1;
                const_cast<ll&>(sum)=v;
                const_cast<ll&>(is_forward)=1;
                const_cast<ll&>(is_backward)=1;
            }
            if (d>128){
                std::cerr<<"bamboo!! "<<d<<std::endl;
                exit(0);
            }
        }
    };

	static void check(const el*s){
		if (__FILE__[0]!='H'){
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

    ll find_index(const el*q)const{
        if (!q){
            return 0;
        }
        auto w=q->p;
        get(q);
        get(w);
        if (w==nullptr){
            return q_z_s;
        }else if (w_z==q){
            return find_index(w)-q_x_s-1;
        }else if (w->x_get()==q){
            return find_index(w)+q_z_s+1;
        }
        assert(0);
        return 0;
    }

	static void pri(const el* root,uint64_t*prev_node=0){
		if (!root){
			return;
		}
		const el*left;
		const el*right;
		left=root->z;
		right=root->x;

		uint64_t node[3];
		node[2]=(uint64_t)NULL;
		node[0]=(uint64_t)prev_node;
		if (prev_node){
			prev_node[2]=(uint64_t)node;
		}

		uint64_t save=0;
		if (prev_node and prev_node[1]==2){
			save=prev_node[1];
			prev_node[1]=0;
		}
		node[1]=2;
		pri(left,node);
		if (save){
			prev_node[1]=save;
		}

		uint64_t*d=node;
		while(d[0]){
			d=(uint64_t*)d[0];
		}

		for (;d!=node;d=(uint64_t*)d[2]){
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
		_put(w)
		_put(first)
		_put(last)
		_put(to_mul)
		_put(to_add)
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


    static void printline(const el*s){
        if (!s){
            return;
        }
        printline(s->z_get());
        printf("%lli ",s->v);
        printline(s->x_get());
    };

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

    static std::pair<const el*,const el*> split(const el* t,ll n){
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

    const el* e=nullptr;
    // const el* _econst{
    //     return e;
    // }
    treap(){}
    treap(treap&&l){
        auto t=e;
        e=(l.e);
        l.e=(t);
    }
    auto&operator=(treap&&l){
        auto t=e;
        e=(l.e);
        l.e=(t);
        return *this;
    }
    ~treap(){
        del(e);
    }
    ll size()const{
        return e?e->s:0;
    }

    ll get_one(){
        assert(size()==1);
        get(e)
        assert(!e_z and !e_x);
        return e->v;
    }

    void add_left(treap&q){
        e=(merge(q.e,e));
        q.e=nullptr;
    }
    void add_right(treap&q){
        e=merge(e,q.e);
        q.e=nullptr;
    }
    treap cut_left(ll n){
        auto tmp=split(e,n);
        e=(tmp.second);
        auto r=treap();
        r.e=tmp.first;
        return r;
    }
    treap cut_right(ll n){
        auto tmp=split(e,size()-n);
        e=tmp.first;
        auto r=treap();
        r.e=tmp.second;
        return r;
    }
    void push_back(const ll&a){
        e=(merge(e,new auto(el(a))));
    }
    void push_front(const ll&a){
        e=(merge(new auto(el(a)),e));
    }
    ll pop_back(){
        auto q=cut_right(1);
        return q.get_one();
    }
    ll pop_front(){
        auto q=cut_left(1);
        return q.get_one();
    }
    auto insert(ll n,const ll&q){
        auto w=cut_left(n);
        w.push_back(q);
        add_left(w);
        return n;
    }
    auto erase(ll n){
        auto w=cut_left(n);
        pop_front();
        add_left(w);
        return n;
    }
    auto update(ll n,const ll&_q){
        auto w=cut_left(n);
        auto r=cut_left(1);
        auto&q=r;
        ll t=0;
        t=q.get_one();
        push_front(_q);
        add_left(w);
        return t;
    }
    auto insert(ll n,treap&q){
        auto w=cut_left(n);
        add_left(q);
        add_left(w);
        return n;
    }
    ll lower_bound(const ll&d){
        ll t=-1;
        auto q=e;
        if (!q){
            t=0;
        }else
        if (d<=q->first){
            t=0;
        }else
        if (d>q->last){
            t=size();
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
            t=find_index(w);
        }
        return t;
    }
    ll upper_bound(const ll&d){
        ll t=-1;
        auto q=e;
        if (!q){
            t=0;
        }else
        if (d<q->first){
            t=0;
        }else
        if (d>=q->last){
            t=size();
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
            t=find_index(w);
        }
        return t;
    }
    ll forward_prefix(){
        ll t=-1;
        auto q=e;
        auto w=q;
        w=nullptr;
        if (!q or q->is_forward){
            t=size();
        }else{
            while (q){
                get(q);
                if (!q_z or q_z->is_forward){
                    if (!q_z or q->v>=q_z->last){
                        if (!w or w->v<=q->first){
                            w=q;
                        }else{
                            t=find_index(w);
                            ++t;
                            break;
                        }
                        q=q_x;
                    }else{
                        if (!w or w->v<=q->first){
                            w=q;
                            t=find_index(w);
                            break;
                        }else{
                            t=find_index(w);
                            ++t;
                            break;
                        }
                    }
                }else{
                    q=q_z;
                }
            }
            if (t==-1){
                t=find_index(w);
                ++t;
            }
        }
        return t;
    }
    ll backward_prefix(){
        ll t=-1;
        auto q=e;
        auto w=q;
        w=nullptr;
        if (!q or q->is_backward){
            t=size();
        }else{
            while (q){
                get(q);
                if (!q_z or q_z->is_backward){
                    if (!q_z or q->v<=q_z->last){
                        if (!w or w->v>=q->first){
                            w=q;
                        }else{
                            t=find_index(w);
                            ++t;
                            break;
                        }
                        q=q_x;
                    }else{
                        if (!w or w->v>=q->first){
                            w=q;
                            t=find_index(w);
                            break;
                        }else{
                            t=find_index(w);
                            ++t;
                            break;
                        }
                    }
                }else{
                    q=q_z;
                }
            }
            if (t==-1){
                t=find_index(w);
                ++t;
            }
        }
        return t;
    }
    void next_permutation(){
        rev();
        auto q=forward_prefix();
        rev();
        q=size()-q;
        auto t=cut_left(q);
        if (t.size()){
            auto r=t.pop_back();
            rev();
            auto p=upper_bound(r);
            r=update(p,r);
            t.push_back(r);
            add_left(t);
        }else{
            rev();
        }
    }
    void prev_permutation(){
        rev();
        auto q=backward_prefix();
        rev();
        q=size()-q;
        auto t=cut_left(q);
        if (t.size()){
            auto r=t.pop_back();
            auto p=lower_bound(r);
            r=update(p-1,r);
            t.push_back(r);
            rev();
            add_left(t);
        }else{
            rev();
        }
    }
    ll sum(){
        if (e){
            return e->sum;
        }else{
            return 0;
        }
    }
    void add(ll v){
        if (e){
            const_cast<ll&>(e->to_add)+=v;
            e->make();
        }
    }
    void mul(ll v){
        if (e){
            const_cast<ll&>(e->to_mul)*=v;
            e->make();
        }
    }
    void rev(){
        if (e){
            const_cast<ll&>(e->rev)^=1;
            e->make();
        }
    }
};


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


///////////////////////////////////////////////////end of lib

ll getw(ll e){
    ll r=0;
    while((e&1)==0){
        e>>=1;
        ++r;
    }
    return r;
}

using el=treap::el;

const el* create(ll n,ll w){
    if (n<=0){
        return nullptr;
    }
    ll h=n/2;
    auto q=create(h,w-1);
    ll r;
    scanf("%lli",&r);
    auto e=create(n-h-1,w-1);
    auto y=new el();
    const_cast<ll&>(y->w)=w;
    const_cast<ll&>(y->v)=r;
    const_cast<const el*&>(y->z)=q;
    const_cast<const el*&>(y->x)=e;
    y->update();
    treap::check(y);
    return y;
}

int main(){
    ll n;
    scanf("%lli",&n);
    treap a;
    a.e=create(n,0);
    a.check(a.e);
    ll qq;
    scanf("%lli",&qq);
    for (ll w=0;w<qq;++w){
        ll q;
        scanf("%lli",&q);
        if (q==-1){
            break;
        }
        if (q==1){
            ll l,r;
            scanf("%lli%lli",&l,&r);
            ++r;
            auto s=a.cut_left(r);
            auto d=s.cut_left(l);
            printf("%lli\n",s.sum());
            s.add_left(d);
            a.add_left(s);
        }
        if (q==2){
            ll x,u;
            scanf("%lli%lli",&x,&u);
            a.insert(u,x);
        }
        if (q==3){
            ll u;
            scanf("%lli",&u);
            a.erase(u);
        }
        if (q==4){
            ll x,l,r;
            scanf("%lli%lli%lli",&x,&l,&r);
            ++r;
            auto s=a.cut_left(r);
            auto d=s.cut_left(l);
            s.mul(0);
            s.add(x);
            s.add_left(d);
            a.add_left(s);
        }
        if (q==5){
            ll x,l,r;
            scanf("%lli%lli%lli",&x,&l,&r);
            ++r;
            auto s=a.cut_left(r);
            auto d=s.cut_left(l);
            s.add(x);
            s.add_left(d);
            a.add_left(s);
        }
        if (q==6){
            ll l,r;
            scanf("%lli%lli",&l,&r);
            ++r;
            auto s=a.cut_left(r);
            auto d=s.cut_left(l);
            s.next_permutation();
            s.add_left(d);
            a.add_left(s);
        }
        if (q==7){
            ll l,r;
            scanf("%lli%lli",&l,&r);
            ++r;
            auto s=a.cut_left(r);
            auto d=s.cut_left(l);
            s.prev_permutation();
            s.add_left(d);
            a.add_left(s);
        }
    }
    a.printline(a.e);
    putchar(10);
}
