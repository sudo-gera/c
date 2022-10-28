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
			assert(depth==next[0]->depth+1 or depth==next[0]->depth+2);
			assert(depth==next[1]->depth+1 or depth==next[1]->depth+2);
			longlen+=next[0]->longlen;
			next[0]->prev=this;
			longlen+=next[1]->longlen;
			next[1]->prev=this;
		}else
		if (next[0]){
			next[0]->update(c-1);
			depth=next[0]->depth+1;
			longlen+=next[0]->longlen;
			next[0]->prev=this;
		}else
		if (next[1]){
			next[1]->update(c-1);
			depth=next[1]->depth+1;
			longlen+=next[1]->longlen;
			next[1]->prev=this;
		}else{
			depth=1;
		}
	}
	void check(){
		if (next[0] and next[1]){
			next[0]->check();
			next[1]->check();
			assert(depth==next[0]->depth+1 or depth==next[0]->depth+2);
			assert(depth==next[1]->depth+1 or depth==next[1]->depth+2);
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
			assert(depth==1);
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
		using is_iterator=Y;
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
	iter find(const T&val)const{
		for (uint64_t w=0;w<len;w++){
			if (CMP{}(data[w],val)==0 and CMP{}(val,data[w])==0){
				iter p;
				p.p=this;
				p.l=w;
				return p;
			}
		}
		for (uint64_t q=0;q<len+1;++q){
			if (next[q]){
				if (len==q or CMP{}(val,data[q])){
					return next[q]->find(val);
				}
			}
		}
		return nullptr;
	}
	uint64_t count(const T&val)const{
		return find(val)!=nullptr;
	}
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
		// next[0]->update();
						// ic()
						// treeprint(this);
		// update();
	}
	void right(){
		std::swap(next[1],next[0]->next[1]);
		std::swap(next[0],next[1]);
		std::swap(next[0],next[1]->next[0]);
		std::swap(data[0],next[1]->data[0]);
		// next[1]->update();
		// update();
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
				if (next[0]->depth==(next[1]?next[1]->depth:0)+2){
					if ((next[0]->next[0]?next[0]->next[0]->depth:0)<(next[0]->next[1]?next[0]->next[1]->depth:0)){
						// ic()
						// treeprint(next[0]);
						next[0]->left();
					}
					right();
					update(3);
				}
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
				if (next[1]->depth==(next[0]?next[0]->depth:0)+2){
					if ((next[1]->next[0]?next[1]->next[0]->depth:0)>(next[1]->next[1]?next[1]->next[1]->depth:0)){
						next[1]->right();
					}
					left();
					update(3);
				}
			}else{
				next[1]=new tree();
				next[1]->data[0]=val;
				next[1]->len=1;
				next[1]->update();
			}
		}
		update();
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
			if ((next[1]?next[1]->depth:0)==(next[0]?next[0]->depth:0)+2){
				if ((next[1]->next[0]?next[1]->next[0]->depth:0)>(next[1]->next[1]?next[1]->next[1]->depth:0)){
					next[1]->right();
				}
				left();
				update(3);
			}
		}else{
			next[1]->erase3(p>>1);
			if (next[1]->len==0){
				delete next[1];
				next[1]=nullptr;
			}
			if ((next[0]?next[0]->depth:0)==(next[1]?next[1]->depth:0)+2){
				if ((next[0]->next[0]?next[0]->next[0]->depth:0)<(next[0]->next[1]?next[0]->next[1]->depth:0)){
					next[0]->left();
				}
				right();
				update(3);
			}
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
};

template<typename TT>
auto operator-(TT q,TT e)->typename TT::template is_iterator<ptrdiff_t>{
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
	return q.p==w.p and q.l==w.l;
}

template<typename TT>
auto operator!=(TT q,TT w)->typename TT::template is_iterator<bool>{
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

// static inline size_t len(void *a) {
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
#define back(a) ((a)[len(a)-1])

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

// #include <set>
// #include <map>
// #include <bits/stdc++.h>
// using namespace std;

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
// 		auto o=s.begin();
// 		auto p=a.begin();
// 		for (;o!=s.end() and p!=a.end();++o,++p){
// 			assert(*o==*p);
// 		}
// 		assert(o==s.end() and p==a.end());
// 	}
// }

struct item{
	char a[40];
};

struct is_less{
	auto operator()(item q,item e)const{
		return strcmp(q.a,e.a)<0;
	}
};

#include <map>

int main(){
	char c=0;
	dict<item,item,is_less> a;
	item s,d,f;
	while(1){
		s.a[0]=0;
		scanf(" %s",s.a);
		if(s.a[0]==0){
			break;
		}else
		if (strcmp(s.a,"insert")==0){
			scanf("%s %s",d.a,f.a);
			a[d]=f;
		}else
		if (strcmp(s.a,"erase")==0){
			scanf("%s",d.a);
			a.erase(d);
		}else
		if (strcmp(s.a,"find")==0){
			scanf("%s",d.a);
			auto p=a.find(d);
			if (p){
				printf("%s\n",p->second.a);
			}else{
				printf("MISSING\n");
			}
		}else{
			assert(0);
		}
	}
}
