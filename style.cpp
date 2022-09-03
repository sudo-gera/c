#include <bits/stdc++.h>

#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <assert.h>

namespace std{
	template<typename q,typename w>
	constexpr bool is_assignable_v=std::is_assignable<q,w>::value;
	template<typename q,typename w>
	constexpr bool is_same_v=std::is_same<q,w>::value;
    template<bool q,typename w>
    using enable_if_t=typename std::enable_if<q,w>::type;
	template<typename q>
	constexpr bool is_copy_constructible_v=std::is_copy_constructible<q>::value;
	template<typename q>
	constexpr bool is_trivially_constructible_v=std::is_trivially_constructible<q>::value;
};


template <typename T>
class treap{
private:
	struct el{
		T v;
		int64_t w;
		el* z_get=nullptr;
		el* x_get=nullptr;
		el* p=nullptr;
		int64_t s=1;
		int64_t d=1;
		int r=0;
		template<typename...Y>
		el(const Y&..._v):v(_v...),w(rand()){}

		template<typename y>
		void z_put(y q){
			z_get=q;
			update();
		}

		template<typename y>
		void x_put(y q){
			x_get=q;
			update();
		}
		void make(){
			if (r){
				auto t=z_put();
				z_put(x_put());
				x_put(t);
				if (z_put()){
					z_put()->r=1;
				}
				if (x_put()){
					x_put()->r=1;
				}
				r=0;
			}
		}
		void update(){
			auto t=this;
			if (t->z_get==nullptr and t->x_get==nullptr){
				t->s=1;
				t->d=1;
			}
			else if (t->z_get==nullptr){
				t->s=t->x_get->s+1;
				t->x_get->p=t;
				t->d=t->x_get->d+1;
			}
			else if (t->x_get==nullptr){
				t->s=t->z_get->s+1;
				t->z_get->p=t;
				t->d=t->z_get->d+1;
			}else{
				t->s=t->z_get->s+t->x_get->s+1;
				t->x_get->p=t;
				t->z_get->p=t;
				t->d=(t->z_get->d>t->x_get->d?t->z_get->d:t->x_get->d)+1;
			}
			if (t->d>128){
				std::cerr<<"bamboo!! "<<t->d<<std::endl;
				exit(0);
			}
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

	static int64_t el_size(el*s){
		return s?s->s:0;
	}

	static int64_t find_index(el*s){
		return s?s->nz_find_index():0;
	}

	static el* get_by_index(el*s,int64_t n){
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

	static void pr(el* q,int64_t n=0){
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

	static void pri(el* root,size_t*prev_node=0){
		if (!root){
			return;
		}
		el*left=(root)->z_get;
		el*right=(root)->x_get;

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
		std::cout<<root->v<<std::endl;

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

	static void del(el* q){
		if (!q){
			return;
		}
		del(q->z_get);
		del(q->x_get);
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
			t2->z_put(merge(t1,t2->z_get));
			return t2;
		}else{
			t1->x_put(merge(t1->x_get,t2));
			return t1;
		}
	}

	static std::pair<el*,el*> split(el* t,int64_t n){
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
					t2->p=nullptr;
				}
				return {t,t2};
			}
		}else if (t->z_get->s==n){
			auto t1=t->z_get;
			t->z_put((el*)(nullptr));
			if (t1){
				t1->p=nullptr;
			}
			return {t1,t};
		}else if (t->z_get->s+1==n){
			auto t2=t->x_get;
			t->x_put((el*)(nullptr));
			if (t2){
				t2->p=nullptr;
			}
			return {t,t2};
		}else if (t->z_get->s+1<n){
			auto tmp=split(t->x_get,n-t->z_get->s-1);
			t->x_put(tmp.first);
			auto t2=tmp.second;
			if (t2){
				t2->p=nullptr;
			}
			return {t,t2};
		}else if (t->z_get->s>n){
			auto tmp=split(t->z_get,n);
			auto t1=tmp.first;
			t->z_put(tmp.second);
			if (t1){
				t1->p=nullptr;
			}
			return {t1,t};
			return {nullptr,nullptr};
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
	treap&operator=(treap&&l){
		std::swap(e,l.e);
		return *this;
	}
	treap&operator=(const treap&l){
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
        iter(el*_e=0,int64_t _o=0,int64_t _d=1){
            e=_e;
            o=_o;
            d=_d;
        }
		T&operator*(){
			return e->v;
		}
		iter&operator--(){
			return *this-=1;
		}
		iter&operator++(){
			return *this+=1;
		}
		iter operator--(int){
			auto q=*this;
			*this-=1;
			return q;
		}
		iter operator++(int){
			auto q=*this;
			*this+=1;
			return q;
		}
		iter&operator+=(long w){
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
		iter&operator-=(long w){
			return *this+=(-w);
		}
		iter&operator[](long q){
			return *(*this+q);
		}
		iter& operator=(const iter&q){
			e=q.e;
			o=q.o;
			d=q.d;
			return *this;
		}
	};
	iter begin(){
		if (!e){
			return iter{e,0};
		}
		auto q=e;
		while (q->z_get){
			q=q->z_get;
		}
		return iter{q,0};
	}
	iter end(){
		if (!e){
			return iter{e,0};
		}
		auto q=e;
		while (q->x_get){
			q=q->x_get;
		}
		return iter{q,1};
	}
	iter rbegin(){
		auto q=end()-1;
		q.d=-1;
		return q;
	}
	iter rend(){
		auto q=begin()-1;
		q.d=-1;
		return q;
	}
	using iterator=iter;
	using value_type=T;
	int64_t insert(int64_t n,const T&q){
		auto w=cut_left(n);
		w.push_back(q);
		add_left(w);
		return n;
	}
	int64_t erase(int64_t n){
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
	template<typename TT>
	auto erase(TT n)->typename TT::template is_iterator<iter>{
		return begin()+erase(find_index(n.e));
	}
	int64_t insert(int64_t n,treap<T>&q){
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

using namespace std;


enum t{
    emp,_exp,par,com,opr
};

struct item{
    string data;
    t type;
    // item(char t){
    //     data=t;
    // }
};

void pr(vector<item>&a){
    for (auto&w:a){
        cout<<"\x1b["<<30+w.type<<"m";
        cout<<w.data;
        cout<<"\x1b[0m|";
    }
    cout<<endl;
}



void np(treap<item>&a,long q,long e){
    // pr(a);
    for (long w=q;w<e;++w){
        if (w!=q and a[w].type==_exp and a[w-1].type==opr and (w==1+q or a[w-2].type!=_exp)){
            a[w].data=a[w-1].data+a[w].data;
            a.erase(a.begin()+w-1);
            --e;
            --w;
        }
    }
    for (long w=q;w<e;++w){
        if (w>=q+2 and a[w].type==_exp and (a[w-1].type==opr or a[w-1].type==com) and a[w-2].type==_exp){
            a[w-2].data+=(a[w-1].type==com?"":" ")+a[w-1].data+" "+a[w].data;
            a.erase(a.begin()+w-1);
            a.erase(a.begin()+w-1);
            w-=2;
            e-=2;
        }
    }
    // pr(a);
}

int main(){
    string s;
    getline(cin,s);
    treap<item> a;
    for (auto w:s){
        a.push_back(item{.data=string({w}),.type=emp});
    }
    for (long w=0;w<a.size();++w){
        if (w and isalnum(a[w].data[0]) and isalnum(a[w-1].data.back())) {
            a[w-1].data+=a[w].data;
            a.erase(a.begin()+w);
            --w;
        }
    }
    for (long w=0;w<a.size();++w){
        if (a[w].data[0]==' '){
            a.erase(a.begin()+w);
            --w;
        }
    }
    for (auto&w:a){
        if (isalnum(w.data[0])){
            w.type=_exp;
        }else
        if (w.data[0]=='(' or w.data[0]==')'){
            w.type=par;
        }else
        if (w.data[0]==','){
            w.type=com;
        }else{
            w.type=opr;
        }
    }
    // for (long w=0;w<a.size();++w){
    //     if (w and a[w].type==_exp and a[w-1].type==opr and (w==1 or a[w-2].type!=_exp)){
    //         a[w].data=a[w-1].data+a[w].data;
    //         a.erase(a.begin()+w-1);
    //         --w;
    //     }
    // }

    vector<long> b;
    for (long w=0;w<a.size();++w){
        if (a[w].type==par){
            if (a[w].data[0]=='('){
                b.push_back(w);
            }else{
                assert (a[w].data[0]==')');
                auto q=b.back();
                b.pop_back();
                long o=a.size();
                np(a,q+1,w);
                w-=o-a.size();
                a.erase(a.begin()+w);
                a.erase(a.begin()+q);
                w-=2;
                if (q==w){
                    a[w].data="("+a[w].data+")";
                    if (w and a[w-1].type==_exp){
                        a[w-1].data+=a[w].data;
                        a.erase(a.begin()+w);
                    }
                }else{
                    a[w].data+="()";
                }
                --w;
            }
        }
    }
    np(a,0,a.size());

    cout<<a[0].data<<endl;

}

