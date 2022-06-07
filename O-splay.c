#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#ifndef assert
#include <assert.h>
#endif
#include <iso646.h>

template <typename T,typename CMP=std::less<T>>
struct tree{
	tree* next[2]={0,0};
	T data[1];
	tree*prev=0;
	long len=0;
	long longlen=0;
	long depth=0;
	long s=0;
	tree(){
		memset(next,0,sizeof(*next));
	}
	tree(const tree&q){
		memset(next,0,sizeof(*next));
		for (auto w=q.begin();w!=q.end();++w){
			insert(*w);
		}
	}
	tree(tree&&q){
		next[0]=q.next[0];
		next[1]=q.next[1];
		data[0]=std::move(q.data[0]);
		len=q.len;
		update();
		q.next[0]=0;
		q.next[1]=0;
		q.len=0;
		q.update();
	}
	auto&operator=(const tree&q){
		if(&q==this){
			return *this;
		}
		for (uint64_t w=0;w<len+1;++w){
			if (next[w]){
				delete next[w];
			}
		}
		len=0;
		memset(next,0,sizeof(*next));
		for (auto w=q.begin();w!=q.end();++w){
			insert(*w);
		}
		return *this;
	}
	auto&operator=(tree&&q){
		if(&q==this){
			return *this;
		}
		for (uint64_t w=0;w<len+1;++w){
			if (next[w]){
				delete next[w];
			}
		}
		next[0]=q.next[0];
		next[1]=q.next[1];
		data[0]=std::move(q.data[0]);
		len=q.len;
		update();
		q.next[0]=0;
		q.next[1]=0;
		q.len=0;
		q.update();
		return *this;
	}
	void update(uint64_t c=1){
		if (c==0){
			return;
		}
		longlen=len;
		if (next[0] and next[1]){
			next[0]->update(c-1);
			next[1]->update(c-1);
			depth=std::max(next[0]->depth,next[1]->depth)+1;
			longlen+=next[0]->longlen;
			next[0]->prev=this;
			longlen+=next[1]->longlen;
			next[1]->prev=this;
			s=next[0]->s+next[1]->s+data[0];
		}else
		if (next[0]){
			next[0]->update(c-1);
			depth=next[0]->depth+1;
			longlen+=next[0]->longlen;
			next[0]->prev=this;
			s=next[0]->s+data[0];
		}else
		if (next[1]){
			next[1]->update(c-1);
			depth=next[1]->depth+1;
			longlen+=next[1]->longlen;
			next[1]->prev=this;
			s=next[1]->s+data[0];
		}else{
			depth=1;
			s=data[0];
		}
	}
	void check(){
		if (next[0] and next[1]){
			next[0]->check();
			next[1]->check();
			// assert(depth==next[0]->depth+1 or depth==next[0]->depth+2);
			// assert(depth==next[1]->depth+1 or depth==next[1]->depth+2);
			assert(longlen==len+next[0]->longlen+next[1]->longlen);
			assert(next[0]->prev==this);
			assert(next[1]->prev==this);
		}else
		if (next[0]){
			next[0]->check();
			assert(depth==next[0]->depth+1);
			assert(longlen==len+next[0]->longlen);
			assert(next[0]->prev==this);
		}else
		if (next[1]){
			next[1]->check();
			assert(depth==next[1]->depth+1);
			assert(longlen==len+next[1]->longlen);
			assert(next[1]->prev==this);
		}else{
			assert(depth==len);
			assert(longlen==len);
		}
	}
	struct iter {
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;
		template<typename Y>
		using is_iterator_tree=Y;
		using original_type=tree;
		const tree*p=0;
		tree*mutable_p(){
			return const_cast<tree*>(p);
		}
		long l=0;
		iter(const nullptr_t& r){}
		iter(){}
		operator const T*(){
			return p?p->data+l:0;
		}
		auto operator->(){
			return p?p->data+l:0;
		}
		// operator bool(){
		// 	return p;
		// }
		auto&operator+=(long n){
			while(n!=0 or !(0<=l and l<p->len or !p->prev)){
				if (0<=l and l<p->len){
					if (n>0){
						if ((p->next[l+1]?p->next[l+1]->longlen:0)<n){
							n-=(p->next[l+1]?p->next[l+1]->longlen:0)+1;
							l++;
						}else{
							p=p->next[l+1];
							l=0;
							n-=p->next[0]?p->next[0]->longlen:0;
							n-=1;
						}
					}else{
						if ((p->next[l]?p->next[l]->longlen:0)<-n){
							n+=(p->next[l]?p->next[l]->longlen:0)+1;
							l--;
						}else{
							p=p->next[l];
							l=p->len-1;
							n+=p->next[l+1]?p->next[l+1]->longlen:0;
							n+=1;
						}
					}
				}else{
					if (p->prev){
						long w=0;
						for (;p->prev->next[w]!=p;++w);
						p=p->prev;
						if (l<0){
							l=w-1;
						}else{
							l=w;
						}
					}else{
						if (l<-1){
							n+=l+1;
							l=-1;
						}else
						if (l>p->len){
							n+=l-p->len;
							l=p->len;
						}else
						if (l==-1){
							if (n>0){
								n-=p->next[0]?p->next[0]->longlen:0;
								n--;
								l=0;
							}else{
								l+=n;
								n=0;
							}
						}else
						if (l==p->len){
							if (n<0){
								n+=p->next[p->len]?p->next[p->len]->longlen:0;
								n++;
								l=p->len-1;
							}else{
								l+=n;
								n=0;
							}
						}else{
							assert(0);
						}
					}
				}
			}
			return *this;
		}
		const T&operator*(){
			return p->data[l];
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
		auto&operator-=(long w){
			return *this+=(-w);
		}
		const T&operator[](long q){
			return *(*this+q);
		}
		bool is_begin(){
			return (*this-1).l==-1;
		}
		bool is_end(){
			return l==p->len;
		}
	};
	using iterator=iter;
	using value_type=T;
	iter begin()const{
		iter t;
		t.p=this;
		t.l=-1;
		t+=1;
		return t;
	}
	iter end()const{
		iter t;
		t.p=this;
		t.l=len;
		return t;
	}
	long size()const{
		return longlen;
	}
	~tree(){
		for (uint64_t w=0;w<len+1;++w){
			if (next[w]){
				delete next[w];
			}
		}
	}
	void clear(){
		for (uint64_t w=0;w<len+1;++w){
			if (next[w]){
				delete next[w];
			}
			next[w]=nullptr;
		}
		len=0;
		update();
	}
	void left(){
		std::swap(next[0],next[1]->next[0]);
		std::swap(next[0],next[1]);
		std::swap(next[1],next[0]->next[1]);
		std::swap(data[0],next[0]->data[0]);
		next[0]->update();
		update();
	}
	void right(){
		std::swap(next[1],next[0]->next[1]);
		std::swap(next[0],next[1]);
		std::swap(next[0],next[1]->next[0]);
		std::swap(data[0],next[1]->data[0]);
		next[1]->update();
		update();
	}
	bool splay(const T&val){
		if (!len){
			return 0;
		}
		if (CMP{}(val,data[0])){
			if (next[0]){
				auto t=next[0]->splay(val);
				right();
				return t;
			}else{
				return 0;
			}
		}
		if (CMP{}(data[0],val)){
			if (next[1]){
				auto t=next[1]->splay(val);
				left();
				return t;
			}else{
				return 0;
			}
		}
		return 1;
	}
	tree* cut_less(const T&val){
		if (!len){
			return nullptr;
		}
		splay(val);
		auto t=this;
		auto s=t;
		s=t=nullptr;
		if (data[0]<val){
			s=this;
			t=next[1];
			next[1]=nullptr;
			if (t){
				t->prev=nullptr;
			}
		}else{
			s=next[0];
			t=this;
			next[0]=nullptr;
			if (t){
				t->prev=nullptr;
			}
		}
		if (s){
			s->update();
		}
		if (t){
			t->update();
		}
		if (s==this and t){
			std::swap(s->next[0],t->next[0]);
			std::swap(s->next[1],t->next[1]);
			std::swap(s->data[0],t->data[0]);
			std::swap(s->len,t->len);
			s->update();
			t->update();
			std::swap(s,t);
		}else
		if (s==this){
			t=new tree();
			t->len=0;
			std::swap(s->next[0],t->next[0]);
			std::swap(s->next[1],t->next[1]);
			std::swap(s->data[0],t->data[0]);
			std::swap(s->len,t->len);
			s->update();
			t->update();
			std::swap(s,t);
			assert(t);
		}
		assert(t);
		t->splay(data[0]);
		assert(t==this);
		return s;
	}
	void add_less(tree*v){
		if (len){
			splay(*begin());
			assert(next[0]==nullptr);
			next[0]=v;
			update();
		}else
		if(v){
			std::swap(next[0],v->next[0]);
			std::swap(next[1],v->next[1]);
			std::swap(data[0],v->data[0]);
			std::swap(len,v->len);
			update();
			v->next[0]=0;
			v->next[1]=0;
			delete v;
		}
	}
	tree* cut_greater(const T&val){
		if (!len){
			return nullptr;
		}
		splay(val);
		auto t=this;
		auto s=t;
		s=t=nullptr;
		if (data[0]>val){
			s=this;
			t=next[0];
			next[0]=nullptr;
			if (t){
				t->prev=nullptr;
			}
		}else{
			s=next[1];
			t=this;
			next[1]=nullptr;
			if (t){
				t->prev=nullptr;
			}
		}
		if (s){
			s->update();
		}
		if (t){
			t->update();
		}
		if (s==this and t){
			std::swap(s->next[0],t->next[0]);
			std::swap(s->next[1],t->next[1]);
			std::swap(s->data[0],t->data[0]);
			std::swap(s->len,t->len);
			s->update();
			t->update();
			std::swap(s,t);
		}else
		if (s==this){
			t=new tree();
			t->len=0;
			std::swap(s->next[0],t->next[0]);
			std::swap(s->next[1],t->next[1]);
			std::swap(s->data[0],t->data[0]);
			std::swap(s->len,t->len);
			s->update();
			t->update();
			std::swap(s,t);
			assert(t);
		}
		assert(t);
		t->splay(data[0]);
		assert(t==this);
		return s;
	}
	void add_greater(tree*v){
		if (len){
			splay(end()[-1]);
			assert(next[1]==nullptr);
			next[1]=v;
			update();
		}else
		if(v){
			std::swap(next[0],v->next[0]);
			std::swap(next[1],v->next[1]);
			std::swap(data[0],v->data[0]);
			std::swap(len,v->len);
			update();
			v->next[0]=0;
			v->next[1]=0;
			delete v;
		}
	}


	iter find(const T& val){
		if (splay(val)){
			iter t;
			t.p=this;
			t.l=0;
			return t;
		}
		return nullptr;
	}
	void insert(const T& val){
		if (!len){
			len=1;
			data[0]=val;
			update();
		}else
		if (CMP{}(val,data[0])){
			if (next[0]){
				next[0]->insert(val);
				// if (next[0]->depth==(next[1]?next[1]->depth:0)+2){
				// 	if ((next[0]->next[0]?next[0]->next[0]->depth:0)<(next[0]->next[1]?next[0]->next[1]->depth:0)){
				// 		// ic()
				// 		// treeprint(next[0]);
				// 		next[0]->left();
				// 	}
				// 	right();
				// 	update(3);
				// }
			}else{
				next[0]=new tree();
				next[0]->data[0]=val;
				next[0]->len=1;
				next[0]->update();
			}
		}else
		if (CMP{}(data[0],val)){
			if (next[1]){
				next[1]->insert(val);
				// if (next[1]->depth==(next[0]?next[0]->depth:0)+2){
				// 	if ((next[1]->next[0]?next[1]->next[0]->depth:0)>(next[1]->next[1]?next[1]->next[1]->depth:0)){
				// 		next[1]->right();
				// 	}
				// 	left();
				// 	update(3);
				// }
			}else{
				next[1]=new tree();
				next[1]->data[0]=val;
				next[1]->len=1;
				next[1]->update();
			}
		}
		update();
		splay(val);
	}
	void erase3(__uint128_t p){
		// ic(bin_repr(uint16_t(p)))
		// treeprint(this);
		if (depth==1){
			len=0;
		}else
		if ((p&2)==0){
			next[0]->erase3(p>>1);
			if (next[0]->len==0){
				delete next[0];
				next[0]=nullptr;
			}
			// if ((next[1]?next[1]->depth:0)==(next[0]?next[0]->depth:0)+2){
			// 	if ((next[1]->next[0]?next[1]->next[0]->depth:0)>(next[1]->next[1]?next[1]->next[1]->depth:0)){
			// 		next[1]->right();
			// 	}
			// 	left();
			// 	update(3);
			// }
		}else{
			next[1]->erase3(p>>1);
			if (next[1]->len==0){
				delete next[1];
				next[1]=nullptr;
			}
			// if ((next[0]?next[0]->depth:0)==(next[1]?next[1]->depth:0)+2){
			// 	if ((next[0]->next[0]?next[0]->next[0]->depth:0)<(next[0]->next[1]?next[0]->next[1]->depth:0)){
			// 		next[0]->left();
			// 	}
			// 	right();
			// 	update(3);
			// }
		}
		update();
	}
	void erase(const T&val){
		auto t=find(val);
		if (t){
			// ic(val)
			while (t.p->depth>1){
				auto p=t;
				++t;
				p.mutable_p()->data[0]=std::move(*t);
				if (t.is_end()){
					--t;
					while (t.p->depth>1){
						auto p=t;
						--t;
						p.mutable_p()->data[0]=std::move(*t);
					}
				}
			}
			__uint128_t p=0;
			auto y=t.p;
			while(y->prev){
				p|=y->prev->next[1]==y;
				p<<=1;
				y=y->prev;
			}
			erase3(p);
		}
	}
	long sum(){
		if (len){
			return s;
		}else{
			return 0;
		}
	}
};

template<typename TT>
auto operator-(TT q,TT e)->typename TT::template is_iterator_tree<ptrdiff_t>{
	if (q.l){
		if(q.l<0){
			long s=q.l;
			q-=s;
			return (q-e)+s;
		}
		if (q.l>=q.p->len){
			long s=q.l-q.p->len+1;
			q-=s;
			return (q-e)+s;
		}
		q.l--;
		return (q.p->next[q.l+1]?q.p->next[q.l+1]->longlen:0)+1+(q-e);
	}
	if (q.p->prev){
		long w=0;
		for (;q.p->prev->next[w]!=q.p;++w){}
		if (w){
			long s=(q.p->next[0]?q.p->next[0]->longlen:0);
			q.p=q.p->prev;
			q.l=w-1;
			return (q-e)+s+1;
		}else{
			long s=q.p->len;
			s+=(q.p->next[1]?q.p->next[1]->longlen:0);
			q.p=q.p->prev;
			q.l=w;
			return (q-e)-s;
		}
	}
	if(e.p->prev or e.l){
		return -(e-q);
	}
	return 0;
}

template<typename TT>
auto operator+(TT q,long w)->typename TT::template is_iterator_tree<TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator-(TT q,long w)->typename TT::template is_iterator_tree<TT>{
	auto e=q;
	e-=w;
	return e;
}

template<typename TT>
auto operator+(long w,TT q)->typename TT::template is_iterator_tree<TT>{
	auto e=q;
	e+=w;
	return e;
}

template<typename TT>
auto operator>=(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return q-w>=0;
}

template<typename TT>
auto operator<=(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return q-w<=0;
}

template<typename TT>
auto operator<(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return q-w<0;
}

template<typename TT>
auto operator>(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return q-w>0;
}

template<typename TT>
auto operator==(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return q.p==w.p and q.l==w.l;
}

template<typename TT>
auto operator!=(TT q,TT w)->typename TT::template is_iterator_tree<bool>{
	return not(q==w);
}

template <typename KEY,typename VALUE,typename CMP>
struct dict_item{
	KEY first;
	VALUE second;
};

template <typename KEY,typename VALUE,typename CMP>
bool operator<(const dict_item<KEY,VALUE,CMP>&q,const dict_item<KEY,VALUE,CMP>&e){
	return CMP{}(q.first,e.first);
}

template <typename KEY,typename VALUE,typename CMP=std::less<KEY>>
struct dict:tree<dict_item<KEY,VALUE,CMP>>{
	VALUE&operator[](const KEY&k){
		dict_item<KEY,VALUE,CMP> d;
		d.first = k;
		auto p=this->find(d);
		if (!p){
			this->insert(d);
		}
		p=this->find(d);
		return p.mutable_p()->data[p.l].second;
	}
	using tree<dict_item<KEY,VALUE,CMP>>::find;
	auto find(const KEY&k){
		dict_item<KEY,VALUE,CMP> d;
		d.first = k;
		return this->find(d);
	}
	using tree<dict_item<KEY,VALUE,CMP>>::count;
	auto count(const KEY&k){
		dict_item<KEY,VALUE,CMP> d;
		d.first = k;
		return this->count(d);
	}
	using tree<dict_item<KEY,VALUE,CMP>>::erase;
	auto erase(const KEY&k){
		dict_item<KEY,VALUE,CMP> d;
		d.first = k;
		return this->erase(d);
	}
};

/////////////////////////

template<typename T,typename CMP>
void treeprint(tree<T,CMP>*root,size_t* prev_node=0){
	//━┃┏┓┗┛┣┫┳┻╋► 
	if (!root){
		return;
	}

	size_t node[3];
	node[2]=(size_t)NULL;
	node[0]=(size_t)prev_node;
	if (prev_node){
		prev_node[2]=(size_t)node;
	}

	size_t save=0;
	if (prev_node && prev_node[1]==1){
		save=prev_node[1];
		prev_node[1]=0;
	}
	node[1]=1;
	treeprint(root->next[0],node);
	if (save){
		prev_node[1]=save;
	}

	for (uint64_t q=0;q<root->len;++q){

		size_t*d=node;
		while(d[0]){
			d=(size_t*)d[0];
		}

		for (;d!=node;d=(size_t*)d[2]){
			// printf("%li",d[1]);
			if (d[1]==3){
				if (d==prev_node){
					if (q==root->len-1){
						printf("┗");
					}else{
						printf("┣");
					}
				}else{
					printf("┃");
				}
			}else
			if (d[1]==2){
				if (d==prev_node){
					printf("┣");
				}else{
					printf("┃");
				}
			}else
			if (d[1]==1){
				if (d==prev_node){
					if (q==0){
						printf("┏");
					}else{
						printf("┣");
					}
				}else{
					printf("┃");
				}
			}else{
				printf(" ");
			}
		}

		if (root->next[q]==NULL and q==0 and root->next[q+1]==NULL and q==root->len-1){
			printf("━");
		}else
		if (root->next[q]==NULL and q==0){
			printf("┳");
		}else
		if (root->next[q+1]==NULL and q==root->len-1){
			printf("┻");
		}else{
			printf("╋");
		}
		printf("► ");
#define _put(s) std::cout<<#s<<" = "<<root->s<<'\t';

		_put(data[q])
		_put(depth)
		_put(longlen)
		std::cout<<std::endl;
		// printf("%li %li %li\n",root->data[q],root->depth,root->longlen);
#undef _put

		save=0;
		if (prev_node and q==root->len-1 and prev_node[1]==3){
			save=prev_node[1];
			prev_node[1]=0;
		}
		node[1]=2+(q==root->len-1);
		treeprint(root->next[q+1],node);
		if (save){
			prev_node[1]=save;
		}
	}
}

template<typename T,typename CMP>
void treep(tree<T,CMP>*root,uint64_t l=0){
	if (!root){
		return;
	}
	treep(root->next[0],l+1);
	for (uint64_t w=0;w<root->len;++w){
		for (uint64_t e=0;e<l;++e){
			putchar('-');
		}
		printf("-> %li\n",root->data[w]);
		treep(root->next[w+1],l+1);
	}
}

#ifndef assert
#include <assert.h>
#endif
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
// /////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
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

int main(){
	uint64_t n=getint();
	tree<long> a;
	long last=0;
	for (uint64_t w=0;w<n;++w){
		char c;
		c=0;
		scanf(" %c",&c);
		if (c=='+'){
			long x=getint();
			x+=last;
			x%=1'000000'000;
			a.insert(x);
			last=0;
		}else
		if (c=='?'){
			long x=getint(),y=getint();
			if (x<y){
				auto s=a.cut_less(x);
				auto d=a.cut_greater(y);
				last=0;
				last=a.sum();
				a.add_less(s);
				a.add_greater(d);
			}else{
				last=0;
			}
			putint(last);
			putchar('\n');
		}else{
			assert(0);
			printf("%li\n",last);
		}
	}
}
