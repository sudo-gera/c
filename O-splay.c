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
	// iter find(const T&val)const{
	// 	for (uint64_t w=0;w<len;w++){
	// 		if (CMP{}(data[w],val)==0 and CMP{}(val,data[w])==0){
	// 			iter p;
	// 			p.p=this;
	// 			p.l=w;
	// 			return p;
	// 		}
	// 	}
	// 	for (uint64_t q=0;q<len+1;++q){
	// 		if (next[q]){
	// 			if (len==q or CMP{}(val,data[q])){
	// 				return next[q]->find(val);
	// 			}
	// 		}
	// 	}
	// 	return nullptr;
	// }
	// uint64_t count(const T&val)const{
	// 	return find(val)!=nullptr;
	// }
	// iter lower_bound(const T&val)const{
	// 	for (uint64_t w=0;w<len;w++){
	// 		if (CMP{}(data[w],val)==0 and CMP{}(val,data[w])==0){
	// 			iter p;
	// 			p.p=this;
	// 			p.l=w;
	// 			return p;
	// 		}
	// 	}
	// 	if (next[0]){
	// 		for (uint64_t q=0;q<len+1;++q){
	// 			assert(q<3);
	// 			if (len==q or CMP{}(val,data[q])){
	// 				return next[q]->lower_bound(val);
	// 			}
	// 		}
	// 	}else{
	// 		for (uint64_t q=0;q<len+1;++q){
	// 			assert(q<3);
	// 			if (len==q or CMP{}(val,data[q])){
	// 				iter p;
	// 				p.p=this;
	// 				p.l=0;
	// 				p+=q;
	// 				return p;
	// 			}
	// 		}
	// 	}
	// 	return nullptr;
	// 	// return std::lower_bound(begin(),end(),val);
	// }
	// iter upper_bound(const T&val)const{
	// 	auto p=lower_bound(val);
	// 	if (p!=end() and (CMP{}(*p,val)==0 and CMP{}(val,*p)==0)){
	// 		++p;
	// 	}
	// 	return p;
	// }
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
	// void erase(T val){
	// 	auto q=find(val);
	// 	if (q){
	// 		if (q.p->next[0]){
	// 			long w=q.is_begin()*2-1;
	// 			// T tmp;
	// 			T tmp=q[w];
	// 			erase3(tmp);
	// 			if (len==0 and next[0]){
	// 				auto tmp=next[0];
	// 				next[0]=tmp->next[0];
	// 				next[1]=tmp->next[1];
	// 				next[2]=tmp->next[2];
	// 				next[3]=tmp->next[3];
	// 				data[0]=std::move(tmp->data[0]);
	// 				data[1]=std::move(tmp->data[1]);
	// 				data[2]=std::move(tmp->data[2]);
	// 				len=tmp->len;
	// 				tmp->next[0]=0;
	// 				tmp->next[1]=0;
	// 				tmp->next[2]=0;
	// 				tmp->next[3]=0;
	// 				delete tmp;
	// 				tmp=nullptr;
	// 				update();
	// 			}
	// 			erase3(tmp);
	// 			q=find(val);
	// 			q.mutable_p()->data[q.l]=std::move(tmp);
	// 		}else{
	// 			erase3(val);
	// 			if (len==0 and next[0]){
	// 				auto tmp=next[0];
	// 				next[0]=tmp->next[0];
	// 				next[1]=tmp->next[1];
	// 				next[2]=tmp->next[2];
	// 				next[3]=tmp->next[3];
	// 				data[0]=std::move(tmp->data[0]);
	// 				data[1]=std::move(tmp->data[1]);
	// 				data[2]=std::move(tmp->data[2]);
	// 				len=tmp->len;
	// 				tmp->next[0]=0;
	// 				tmp->next[1]=0;
	// 				tmp->next[2]=0;
	// 				tmp->next[3]=0;
	// 				delete tmp;
	// 				tmp=nullptr;
	// 				update();
	// 			}
	// 		}
	// 	}
	// }
	// void insert3(const T& val){
	// 	assert(len<3);
	// 	for (uint64_t w=0;w<len;w++){
	// 		if (CMP{}(data[w],val)==0 and CMP{}(val,data[w])==0){
	// 			return;
	// 		}
	// 	}
	// 	uint64_t tmp=len;
	// 	for (uint64_t w=0;w<len+1;w++){
	// 		if (next[w]){
	// 			tmp+=next[w]->longlen;
	// 			assert(next[w]->prev==this);
	// 		}
	// 	}
	// 	assert(tmp==longlen);
	// 	if (next[0]==0){
	// 		for (uint64_t q=0;q<len+1;++q){
	// 			assert(q<3);
	// 			if (len==q or CMP{}(val,data[q])){
	// 				for (uint64_t w=2;w>q;--w){
	// 					data[w]=std::move(data[w-1]);
	// 				}
	// 				data[q]=val;
	// 				len++;
	// 				update();
	// 				break;
	// 			}
	// 		}
	// 		update();
	// 	}else{
	// 		for (uint64_t q=0;q<len+1;++q){
	// 			assert(q<3);
	// 			if (len==q or CMP{}(val,data[q])){
	// 				next[q]->insert3(val);
	// 				if (next[q]->len==3){
	// 					for (uint64_t w=2;w>q;--w){
	// 						data[w]=std::move(data[w-1]);
	// 					}
	// 					data[q]=std::move(next[q]->data[1]);
	// 					for (uint64_t w=3;w>1+q;--w){
	// 						next[w]=next[w-1];
	// 					}
	// 					next[q+1]=new tree();
	// 					next[q+1]->data[0]=std::move(next[q]->data[2]);
	// 					next[q+1]->len=1;
	// 					next[q+1]->next[0]=next[q]->next[2];
	// 					next[q+1]->next[1]=next[q]->next[3];
	// 					next[q+1]->update();
	// 					next[q]->next[2]=0;
	// 					next[q]->next[3]=0;
	// 					next[q]->len=1;
	// 					next[q]->update();
	// 					len++;
	// 				}
	// 				update();
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	tmp=len;
	// 	for (uint64_t w=0;w<len+1;w++){
	// 		if (next[w]){
	// 			tmp+=next[w]->longlen;
	// 			assert(next[w]->prev==this);
	// 		}
	// 	}
	// 	assert(tmp==longlen);
	// }
	// void erase3(const T&val){
	// 	uint64_t tmp=len;
	// 	for (uint64_t w=0;w<len+1;w++){
	// 		if (next[w]){
	// 			tmp+=next[w]->longlen;
	// 			assert(next[w]->prev==this);
	// 		}
	// 	}
	// 	assert(tmp==longlen);
	// 	if (next[0]){
	// 		for (uint64_t q=0;q<4;++q){
	// 			assert(q<3);
	// 			if (len==q or CMP{}(val,data[q])){
	// 				next[q]->erase3(val);
	// 				if (next[q]->len==0){
	// 					uint64_t e=q;
	// 					e+=1-2*bool(e);
	// 					if (next[e]->len==1){
	// 						if (e>q){
	// 							next[e]->data[1]=std::move(next[e]->data[0]);
	// 							next[e]->data[0]=std::move(data[q]);
	// 							next[e]->next[2]=next[e]->next[1];
	// 							next[e]->next[1]=next[e]->next[0];
	// 							next[e]->next[0]=next[q]->next[0];
	// 							next[e]->len=2;
	// 							next[e]->update();
	// 							next[q]->next[0]=0;
	// 							delete next[q];
	// 							for (uint64_t w=q+1;w<len+1;++w){
	// 								next[w-1]=next[w];
	// 							}
	// 							next[len]=0;
	// 							for (uint64_t w=q+1;w<len;++w){
	// 								data[w-1]=std::move(data[w]);
	// 							}
	// 							len--;
	// 						}else{
	// 							next[e]->data[1]=std::move(data[e]);
	// 							next[e]->next[2]=next[q]->next[0];
	// 							next[e]->len=2;
	// 							next[e]->update();
	// 							next[q]->next[0]=0;
	// 							delete next[q];
	// 							for (uint64_t w=q+1;w<len+1;++w){
	// 								next[w-1]=next[w];
	// 							}
	// 							next[len]=0;
	// 							for (uint64_t w=e+1;w<len;++w){
	// 								data[w-1]=std::move(data[w]);
	// 							}
	// 							len--;
	// 						}
	// 					}else{
	// 						assert(next[e]->len==2);
	// 						if (e>q){
	// 							next[q]->data[0]=std::move(data[q]);
	// 							next[q]->next[1]=next[e]->next[0];
	// 							next[q]->len=1;
	// 							data[q]=std::move(next[e]->data[0]);
	// 							next[e]->data[0]=std::move(next[e]->data[1]);
	// 							next[e]->next[0]=next[e]->next[1];
	// 							next[e]->next[1]=next[e]->next[2];
	// 							next[e]->next[2]=next[e]->next[3];
	// 							next[e]->len=1;
	// 						}else{
	// 							next[q]->data[0]=std::move(data[e]);
	// 							next[q]->next[1]=next[q]->next[0];
	// 							next[q]->next[0]=next[e]->next[2];
	// 							data[e]=std::move(next[e]->data[1]);
	// 							next[e]->next[2]=0;
	// 							next[q]->len=1;
	// 							next[e]->len=1;
	// 						}
	// 						next[q]->update();
	// 						next[e]->update();
	// 					}
	// 				}
	// 				update();
	// 				break;
	// 			}
	// 		}
	// 	}else{
	// 		for (uint64_t q=0;q<len;++q){
	// 			if (CMP{}(data[q],val)==0 and CMP{}(val,data[q])==0){
	// 				for (uint64_t w=q+1;w<len;++w){
	// 					data[w-1]=std::move(data[w]);
	// 				}
	// 				len--;
	// 				update();
	// 				break;
	// 			}
	// 		}
	// 	}
	// }
	// void insert(const T& val){
	// 	insert3(val);
	// 	if (len==3){
	// 		tree*t=new tree();
	// 		t->prev=this;
	// 		t->next[0]=next[0];
	// 		t->next[1]=next[1];
	// 		t->len=1;
	// 		t->data[0]=std::move(data[0]);
	// 		t->update();
	// 		next[0]=t;
	// 		t=new tree();
	// 		t->prev=this;
	// 		t->next[0]=next[2];
	// 		t->next[1]=next[3];
	// 		t->len=1;
	// 		t->data[0]=std::move(data[2]);
	// 		t->update();
	// 		next[1]=t;
	// 		data[0]=std::move(data[1]);
	// 		len=1;
	// 		next[2]=next[3]=0;
	// 		update();
	// 	}
	// }
	void left(){
		std::swap(next[0],next[1]->next[0]);
		std::swap(next[0],next[1]);
		std::swap(next[1],next[0]->next[1]);
		std::swap(data[0],next[0]->data[0]);
		next[0]->update();
						// ic()
						// treeprint(this);
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


	// bool splay(const T& val){
	// 	if (!len){
	// 		return 0;
	// 	}
	// 	auto p=this;
	// 	while(p){
	// 		if (CMP{}(val,p->data[0])){
	// 			p=p->next[0];
	// 		}else
	// 		if (CMP{}(p->data[0],val)){
	// 			p=p->next[1];
	// 		}else{
	// 			break;
	// 		}
	// 	}
	// 	if (p){
	// 		assert(p->data[0]==val);
	// 		while(p->prev){
	// 			if (p->prev->next[0]==p){
	// 				p=p->prev;
	// 				p->right();
	// 				assert(p->data[0]==val);
	// 			}else{
	// 				p=p->prev;
	// 				p->left();
	// 				assert(p->data[0]==val);
	// 			}
	// 		}
	// 		assert(p->data[0]==val);
	// 		return 1;
	// 	}
	// 	return 0;
	// }
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
	// for (uint64_t w=root->len;w<3;++w){
	// 	for (uint64_t e=0;e<l;++e){
	// 		putchar('-');
	// 	}
	// 	printf("\x1b[94m-> %li\n\x1b[0m",root->data[w]);
	// 	treep(root->next[w+1],l+1);
	// }
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

#include <vector>

template<typename T>
void check(T q,T e){
	std::vector<T> a;
	for (auto w=q;w!=e;++w){
		a.push_back(w);
	}
	a.push_back(e);
	for (size_t w=0;w<a.size();w++){
		for (size_t e=0;e<a.size();++e){
			long d=long(w)-long(e);
			assert(a[w]-a[e]==d);
			assert(w>=e or  a[w]<a[e]);
			assert(w<=e or  a[w]>a[e]);
			assert(w==e or a[w]!=a[e]);
			assert(w>e  or a[w]<=a[e]);
			assert(w<e  or a[w]>=a[e]);
			assert(w!=e or a[w]==a[e]);
			assert(a[w]+(-d)==a[e]);
			assert(a[w]-(d)==a[e]);
		}
	}
	auto s=a;
	s.clear();
	for (auto w=e;w!=q;--w){
		s.push_back(w);
	}
	s.push_back(q);
	reverse(s.begin(),s.end());
	assert(a==s);
}




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

// #ifdef assert_m
// #define assert assert_m
// #endif

#define get(a) auto a##_z=a?a->z_get():0;auto a##_x=a?a->x_get():0;auto a##_z_s=a##_z?a##_z->s:0;auto a##_x_s=a##_x?a##_x->s:0;

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
		long const is_forward=1;
		long const is_backward=1;
		long min=0;
		long max=0;
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
				const el*te=const_cast<const el*&>(z);
				const_cast<const el*&>(z)=const_cast<const el*&>(x);
				const_cast<const el*&>(x)=te;
				long tl=const_cast<long&>(is_forward);
				const_cast<long&>(is_forward)=const_cast<long&>(is_backward);
				const_cast<long&>(is_backward)=tl;
				tl=const_cast<long&>(first);
				const_cast<long&>(first)=const_cast<long&>(last);
				const_cast<long&>(last)=tl;
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
			if (z){
				const_cast<const el*&>(z->p)=this;
				if (z->rev){
					const_cast<long&>(first)=z->last*z->to_mul+z->to_add;
				}else{
					const_cast<long&>(first)=z->first*z->to_mul+z->to_add;
				}
			}else{
				const_cast<long&>(first)=v;
			}
			if (x){
				const_cast<const el*&>(x->p)=this;
				if (x->rev){
					const_cast<long&>(last)=x->first*x->to_mul+x->to_add;
				}else{
					const_cast<long&>(last)=x->last*x->to_mul+x->to_add;
				}
			}else{
				const_cast<long&>(last)=v;
			}
			if (z and x){
				long s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
				long s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
				long s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
				long s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
				long s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
				long s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
				long s_z_s=z->s;
				long s_x_s=x->s;
				const_cast<long&>(s)=z->s+x->s+1;
				const_cast<long&>(d)=1+(z->d>x->d?z->d:x->d);
				const_cast<long&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s + x->sum*x->to_mul+x->to_add*x->s;
				const_cast<long&>(is_forward)=(s_z_forward and s_x_forward and s_z_last<=v and s_x_first>=v);
				const_cast<long&>(is_backward)=(s_z_backward and s_x_backward and s_z_last>=v and s_x_first<=v);
			}else
			if (z){
				long s_x_forward=1;
				long s_x_backward=1;
				long s_z_forward=(z->to_mul==0 or (z->rev?z->is_backward:z->is_forward));
				long s_z_backward=(z->to_mul==0 or (z->rev?z->is_forward:z->is_backward));
				long s_z_last=(z->rev?z->first:z->last)*z->to_mul+z->to_add;
				long s_x_first=0;
				long s_z_s=z->s;
				long s_x_s=0;
				const_cast<long&>(s)=z->s+1;
				const_cast<long&>(d)=z->d+1;
				const_cast<long&>(sum)=v + z->sum*z->to_mul+z->to_add*z->s;
				const_cast<long&>(is_forward)=(s_z_forward and s_z_last<=v);
				const_cast<long&>(is_backward)=(s_z_backward and s_z_last>=v);
			}else
			if (x){
				long s_z_forward=1;
				long s_z_backward=1;
				long s_x_forward=(x->to_mul==0 or (x->rev?x->is_backward:x->is_forward));
				long s_x_backward=(x->to_mul==0 or (x->rev?x->is_forward:x->is_backward));
				long s_x_first=(x->rev?x->last:x->first)*x->to_mul+x->to_add;
				long s_z_last=0;
				long s_z_s=0;
				long s_x_s=x->s;
				const_cast<long&>(s)=x->s+1;
				const_cast<long&>(d)=x->d+1;
				const_cast<long&>(sum)=v + x->sum*x->to_mul+x->to_add*x->s;
				const_cast<long&>(is_forward)=(s_x_forward and s_x_first>=v);
				const_cast<long&>(is_backward)=(s_x_backward and s_x_first<=v);
			}else{
				const_cast<long&>(s)=1;
				const_cast<long&>(d)=1;
				const_cast<long&>(sum)=v;
				const_cast<long&>(is_forward)=1;
				const_cast<long&>(is_backward)=1;
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
		if (__FILE__[0]!='t'){
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
		left=root->z;
		right=root->x;

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

	static std::pair<const el*,const el*> split(const el* t,int64_t n){
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

	static std::pair<const el*,long> add(const el*q,int64_t n){
		long o=0;
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
	template <typename y=std::initializer_list<T>>
	treap(const y&l=std::initializer_list<T>(),
		std::enable_if_t<
			std::is_same_v<
				typename y::value_type,T
			> and std::is_copy_constructible_v<T>
			and std::is_same_v<decltype(l.begin()!=l.end()),bool>
			,int> =0){
		for (auto&w:l){
			_e=(merge(e_get(),new auto (el(w))));
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
			_e=(merge(e_get(),new auto (el(T()))));
		}
	}
	treap(const treap&l){
		for (auto&w:l){
			_e=(merge(e_get(),new auto (el(w))));
		}
	}
	treap(treap&&l){
		auto t=e_get();
		_e=(l.e_get());
		l._e=(t);
	}
	auto&operator=(treap&&l){
		auto t=e_get();
		_e=(l.e_get());
		l._e=(t);
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
		e_get()?const_cast<long&>(e_get()->rev)^=1:0;
	}

	bool is_forward(){
		return e_get()?e_get()->is_forward:1;
	}

	bool is_backward(){
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
	void add_left(treap<T>&q){
		_e=(merge(q.e_get(),e_get()));
		q._e=(nullptr);
	}
	void add_right(treap<T>&q){
		_e=merge(e_get(),q.e_get());
		q._e=nullptr;
	}
	treap<T> cut_left(int64_t n){
		// assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),n);
		// assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=(tmp.second);
		auto r=treap<T>();
		r._e=(tmp.first);
		return r;
	}
	treap<T> cut_right(int64_t n){
		// assert(0<=n and n<=size());
		auto s=size();
		auto tmp=split(e_get(),size()-n);
		// assert(el_size(tmp.first)+el_size(tmp.second)==s);
		_e=tmp.first;
		auto r=treap<T>();
		r._e=(tmp.second);
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
		// if(_e){_e->make();};
	}
	void push_front(const T&a){
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
			auto t=add(e,w);
			e=t.first;
			o=t.second;
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
		long find_index(){
			return e?e->nz_find_index()+o:0;
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
	auto update(int64_t n,const T&q){
		auto w=cut_left(n);
		auto r=cut_left(1);
		auto t=r[0];
		push_front(q);
		add_left(w);
		return t;
	}
	template<typename TT>
	auto insert(TT n,const T&q)->typename TT::template is_iterator<iter>{
		return begin()+insert(n.find_index(),q);
	}
	template<typename TT>
	auto update(TT n,const T&q)->typename TT::template is_iterator<iter>{
		return update(n.find_index(),q);
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
	iter lower_bound(const T&d){
		if (is_forward()){
			iter t,y;
			auto q=e_get();
			if (!q){
				t=begin();
			}else
			if (d<=q->first){
				t=begin();
			}else
			if (d>q->last){
				t=end();
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
		}else{
			assert(0);
		}
		assert(0);
		return iter{};
	}
	iter upper_bound(const T&d){
		if (is_forward()){
			iter t;
			auto q=e_get();
			if (!q){
				t=begin();
			}else
			if (d<q->first){
				t=begin();
			}else
			if (d>=q->last){
				t=end();
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
		}else{
			assert(0);
		}
		assert(0);
		return iter{};
	}
	auto forward_prefix(){
		iter t;
		auto q=e_get();
		auto w=q;
		w=nullptr;
		if (!q or q->is_forward){
			t=end();
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
	auto backward_prefix(){
		iter t;
		auto q=e_get();
		auto w=q;
		w=nullptr;
		if (!q or q->is_backward){
			t=end();
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
	bool next_permutation(){
		rev();
		auto q=forward_prefix().find_index();
		// assert(q==e_get()->forward_prefix);
		rev();
		// assert(q==e_get()->backward_suffix);
		q=size()-q;
		auto t=cut_left(q);
		if (t.size()){
			auto r=t.pop_back();
			rev();
			auto p=upper_bound(r).find_index();
			// assert(size()>p);
			r=update(p,r);
			t.push_back(r);
			add_left(t);
			return 1;
		}else{
			rev();
			return 0;
		}
	}
	bool prev_permutation(){
		rev();
		auto q=backward_prefix().find_index();
		// assert(q==e_get()->backward_prefix);
		rev();
		// assert(q==e_get()->forward_suffix);
		q=size()-q;
		auto t=cut_left(q);
		if (t.size()){
			auto r=t.pop_back();
			assert(is_forward());
			auto p=lower_bound(r).find_index();
			// assert(r>(*this)[p-1]);
			r=update(p-1,r);
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
			return _e->sum;
		}else{
			return 0;
		}
	}
	void add(long v){
		if (e_get()){
			const_cast<long&>(_e->to_add)+=v;
		}
	}
	void mul(long v){
		if (e_get()){
			const_cast<long&>(_e->to_mul)*=v;
		}
	}
};

// template <typename T>
// bool operator<(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)<0;
// }

// template <typename T>
// bool operator>(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)>0;
// }

// template <typename T>
// bool operator==(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)==0;
// }

// template <typename T>
// bool operator<=(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)<=0;
// }

// template <typename T>
// bool operator>=(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)>=0;
// }

// template <typename T>
// bool operator!=(const treap<T>&q,const treap<T>&w){
// 	return q.__cmp__(w)!=0;
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


#include <vector>

// #include <set>
// #include <map>
// #include <bits/stdc++.h>
using namespace std;


// #include "treap.hpp"

// int main(){
// 	tree<long> a;
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	a.insert(rand()%99);
// 	treeprint(&a);
// 	for (uint64_t w=0;w<99;++w){
// 		auto s=a.cut_greater(w);
// 		a.add_greater(s);
// 	}
// 	treeprint(&a);
// }

// int main(){
// 	tree<long> a;
// 	set<long> s;
// 	while (1){
// 		uint64_t q=rand()%4;
// 		q=q?q:1;
// 		long w=rand()%99-50;
// 		// ic(q,w);
// 		// treeprint(&a);
// 		if (q==1){
// 			a.insert(w);
// 			s.insert(w);
// 		}
// 		if (q==2){
// 			auto p=a.find(w);
// 			auto o=s.find(w);
// 			assert((p==nullptr)==(o==s.end()));
// 			if (p){
// 				assert(*p==w);
// 				assert(*o==w);
// 			}
// 		}
// 		if (q==3){
// 			a.erase(w);
// 			s.erase(w);
// 		}
// 		// ic()
// 		// treeprint(&a);
// 		a.check();
// 		auto o=s.begin();
// 		auto p=a.begin();
// 		// ic(itervect(a.begin(),a.end()),s)
// 		// treeprint(&a);
// 		for (;o!=s.end() and p!=a.end();++o,++p){
// 			assert(*o==*p);
// 		}
// 		assert(o==s.end() and p==a.end());
// 	}
// }

// struct item{
// 	char a[40];
// };

// struct is_less{
// 	auto operator()(item q,item e)const{
// 		return strcmp(q.a,e.a)<0;
// 	}
// };

// #include <map>

// int main(){
// 	char c=0;
// 	dict<item,item,is_less> a;
// 	item s,d,f;
// 	while(1){
// 		s.a[0]=0;
// 		scanf(" %s",s.a);
// 		if(s.a[0]==0){
// 			break;
// 		}else
// 		if (strcmp(s.a,"insert")==0){
// 			scanf("%s %s",d.a,f.a);
// 			a[d]=f;
// 		}else
// 		if (strcmp(s.a,"erase")==0){
// 			scanf("%s",d.a);
// 			a.erase(d);
// 		}else
// 		if (strcmp(s.a,"find")==0){
// 			scanf("%s",d.a);
// 			auto p=a.find(d);
// 			if (p){
// 				printf("%s\n",p->second.a);
// 			}else{
// 				printf("MISSING\n");
// 			}
// 		}else{
// 			assert(0);
// 		}
// 	}
// }

int main(){
	uint64_t n=getint();
	// uint64_t n=-1;
	// tree<long> a;
	// treap<long> z;
	vector<long> b;
	long last=0;
	// long sr=0;
	// sr=time(0);
	// printf("seed == %li\n",sr);
	// srand(sr);
	for (uint64_t w=0;w<n;++w){
		char c;
		c=0;
		// c=rand()%2;
		scanf(" %c",&c);
		if (c=='+'){
			long x=getint();
			// long x=rand()%99;
			x+=last;
			// a.insert(x);
			// auto y=z.lower_bound(x);
			// if (y==z.upper_bound(x)){
			// 	z.insert(y,x);
			// }
			auto h=lower_bound(b.begin(),b.end(),x);
			if (h==upper_bound(b.begin(),b.end(),x)){
				b.insert(h,x);
			}
			last=0;
		}else
		if (c=='?'){
			// long x=rand()%99;
			// long y=rand()%99;
			long x=getint(),y=getint();
			if (x<y){
				// auto s=a.cut_less(x);
				// auto d=a.cut_greater(y);
				// auto c=z.cut_left(z.lower_bound(x)-z.begin());
				// auto v=z.cut_right(z.end()-z.upper_bound(y));
				last=0;
				for (auto w=lower_bound(b.begin(),b.end(),x);w!=upper_bound(b.begin(),b.end(),y);++w){
					last+=*w;
				}
				// assert(last==a.sum());
				// assert(last==z.sum());
				// a.add_less(s);
				// a.add_greater(d);
				// z.add_left(c);
				// z.add_right(v);
			}else{
				last=0;
			}
			putint(last);
			putchar('\n');
		}else{
			assert(0);
		}
	}
}
