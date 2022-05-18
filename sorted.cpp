#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct tree;

void treep(tree<long>*,uint64_t);

template <typename T>
struct tree{
	tree* next[4];
	T data[3];
	tree*prev;
	long len;
	long longlen;
	tree(){
		memset(this,0,sizeof(*this));
	}
	tree(const tree&q){
		memset(this,0,sizeof(*this));
		for (auto w=q.begin();w!=q.end();++w){
			insert(*w);
		}
	}
	void update(){
		longlen=len;
		for (uint64_t w=0;w<len+1;w++){
			if (next[w]){
				longlen+=next[w]->longlen;
				next[w]->prev=this;
			}
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
		using original_type=tree<T>;
		tree*p=0;
		long l=0;
		iter(const nullptr_t& r){}
		iter(){}
		operator T*(){
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
	};
	using iterator=iter;
	using value_type=T;
	iter begin(){
		iter t;
		t.p=this;
		t.l=-1;
		t+=1;
		return t;
	}
	iter end(){
		iter t;
		t.p=this;
		t.l=len;
		return t;
	}
	long size(){
		return longlen;
	}
	~tree(){
		for (uint64_t w=0;w<len+1;++w){
			if (next[w]){
				delete next[w];
			}
		}
	}
	iter find(const T&val){
		for (uint64_t w=0;w<len;w++){
			if (data[w]==val){
				iter p;
				p.p=this;
				p.l=w;
				return p;
			}
		}
		if (next[0]){
			for (uint64_t q=0;q<len+1;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					return next[q]->find(val);
				}
			}
		}
		return nullptr;
	}
	iter lower_bound(const T&val){
		for (uint64_t w=0;w<len;w++){
			if (data[w]==val){
				iter p;
				p.p=this;
				p.l=w;
				return p;
			}
		}
		if (next[0]){
			for (uint64_t q=0;q<len+1;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					return next[q]->lower_bound(val);
				}
			}
		}else{
			for (uint64_t q=0;q<len+1;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					iter p;
					p.p=this;
					p.l=0;
					p+=q;
					return p;					
				}
			}
		}
		return nullptr;
	}
	iter upper_bound(const T&val){
		auto p=lower_bound(val);
		if (p!=end() and *p==val){
			++p;
		}
		return p;
	}
	void erase(T val){
		auto q=find(val);
		if (q){
			if (q.p->next[0]){
				long w=q.is_begin()*2-1;
				auto tmp=q[w];
				erase3(tmp);
				if (len==0 and next[0]){
					auto tmp=next[0];
					next[0]=tmp->next[0];
					next[1]=tmp->next[1];
					next[2]=tmp->next[2];
					next[3]=tmp->next[3];
					data[0]=tmp->data[0];
					data[1]=tmp->data[1];
					data[2]=tmp->data[2];
					len=tmp->len;
					tmp->next[0]=0;
					tmp->next[1]=0;
					tmp->next[2]=0;
					tmp->next[3]=0;
					delete tmp;
					update();
				}
				erase3(tmp);
				q=find(val);
				q.p->data[q.l]=tmp;
			}else{
				erase3(val);
				if (len==0 and next[0]){
					auto tmp=next[0];
					next[0]=tmp->next[0];
					next[1]=tmp->next[1];
					next[2]=tmp->next[2];
					next[3]=tmp->next[3];
					data[0]=tmp->data[0];
					data[1]=tmp->data[1];
					data[2]=tmp->data[2];
					len=tmp->len;
					tmp->next[0]=0;
					tmp->next[1]=0;
					tmp->next[2]=0;
					tmp->next[3]=0;
					delete tmp;
					update();
				}
			}
		}
	}
	void insert3(const T& val){
		assert(len<3);
		for (uint64_t w=0;w<len;w++){
			if (data[w]==val){
				return;
			}
		}
		uint64_t tmp=len;
		for (uint64_t w=0;w<len+1;w++){
			if (next[w]){
				tmp+=next[w]->longlen;
				assert(next[w]->prev==this);
			}
		}
		assert(tmp==longlen);
		if (next[0]==0){
			data[len++]=val;
			std::sort(data,data+len);
			longlen++;
		}else{
			for (uint64_t q=0;q<len+1;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					next[q]->insert3(val);
					if (next[q]->len==3){
						for (uint64_t w=2;w>q;--w){
							data[w]=data[w-1];
						}
						data[q]=next[q]->data[1];
						for (uint64_t w=3;w>1+q;--w){
							next[w]=next[w-1];
						}
						next[q+1]=new tree();
						next[q+1]->data[0]=next[q]->data[2];
						next[q+1]->len=1;
						next[q+1]->next[0]=next[q]->next[2];
						next[q+1]->next[1]=next[q]->next[3];
						next[q+1]->update();
						next[q]->next[2]=0;
						next[q]->next[3]=0;
						next[q]->len=1;
						next[q]->update();
						len++;
					}
					update();
					break;
				}
			}
		}
	}
	void erase3(const T&val){
		uint64_t tmp=len;
		for (uint64_t w=0;w<len+1;w++){
			if (next[w]){
				tmp+=next[w]->longlen;
				assert(next[w]->prev==this);
			}
		}
		assert(tmp==longlen);
		if (next[0]){
			for (uint64_t q=0;q<4;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					next[q]->erase3(val);
					if (next[q]->len==0){
						uint64_t e=q;
						e+=1-2*bool(e);
						if (next[e]->len==1){
							if (e>q){
								next[e]->data[1]=next[e]->data[0];
								next[e]->data[0]=data[q];
								next[e]->next[2]=next[e]->next[1];
								next[e]->next[1]=next[e]->next[0];
								next[e]->next[0]=next[q]->next[0];
								next[e]->len=2;
								next[e]->update();
								next[q]->next[0]=0;
								delete next[q];
								for (uint64_t w=q+1;w<len+1;++w){
									next[w-1]=next[w];
								}
								for (uint64_t w=q+1;w<len;++w){
									data[w-1]=data[w];
								}
								len--;
							}else{
								next[e]->data[1]=data[e];
								next[e]->next[2]=next[q]->next[0];
								next[e]->len=2;
								next[e]->update();
								next[q]->next[0]=0;
								delete next[q];
								for (uint64_t w=q+1;w<len+1;++w){
									next[w-1]=next[w];
								}
								for (uint64_t w=e+1;w<len;++w){
									data[w-1]=data[w];
								}
								len--;
							}
						}else{
							assert(next[e]->len==2);
							if (e>q){
								next[q]->data[0]=data[q];
								next[q]->next[1]=next[e]->next[0];
								next[q]->len=1;
								data[q]=next[e]->data[0];
								next[e]->data[0]=next[e]->data[1];
								next[e]->next[0]=next[e]->next[1];
								next[e]->next[1]=next[e]->next[2];
								next[e]->next[2]=next[e]->next[3];
								next[e]->len=1;
							}else{
								next[q]->data[0]=data[e];
								next[q]->next[1]=next[q]->next[0];
								next[q]->next[0]=next[e]->next[2];
								data[e]=next[e]->data[1];
								next[e]->next[2]=0;
								next[q]->len=1;
								next[e]->len=1;
							}
							next[q]->update();
							next[e]->update();
						}
					}
					update();
					break;
				}
			}
		}else{
			for (uint64_t q=0;q<len;++q){
				if (data[q]==val){
					for (uint64_t w=q+1;w<len;++w){
						data[w-1]=data[w];
					}
					len--;
					update();
					break;
				}
			}
		}
	}
	void insert(const T& val){
		insert3(val);
		if (len==3){
			tree*t=new tree();
			t->prev=this;
			t->next[0]=next[0];
			t->next[1]=next[1];
			t->len=1;
			t->data[0]=data[0];
			t->update();
			next[0]=t;
			t=new tree();
			t->prev=this;
			t->next[0]=next[2];
			t->next[1]=next[3];
			t->len=1;
			t->data[0]=data[2];
			t->update();
			next[1]=t;
			data[0]=data[1];
			len=1;
			next[2]=next[3]=0;
			update();
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
			s+=(q.p->next[2]?q.p->next[2]->longlen:0);
			s+=(q.p->next[3]?q.p->next[3]->longlen:0);
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


void treeprint(tree<long>*root,size_t* prev_node=0){
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
		printf("%li\n",root->data[q]);

		save=0;
		if (prev_node && prev_node[1]==2+(q==root->len-1)){
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

void treep(tree<long>*root,uint64_t l){
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

template<typename T>
void check(T q,T e){
	vector<T> a;
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

int main(){
	tree<long> a;
	set<long> s;
	uint64_t c_=0;
	for (uint64_t w=0;w<4321;++w){
		// auto z=rand()%6;
		auto z=getint();
		if (feof(stdin)){
			break;
		}
		if (z<2){
			auto q=getint();
			// auto q=rand()%49;
			// print(z,q)
			a.insert(q);
			s.insert(q);
		}
		if (z==3){
			auto q=getint();
			// auto q=rand()%49;
			// print(z,q)
			assert((a.find(q)==nullptr)==(s.find(q)==s.end()));
		}
		if (z==4){
			auto q=getint();
			// auto q=rand()%49;
			// print(z,q)
			a.erase(q);
			s.erase(q);
		}
		if (z==5){
			auto q=getint();
			// auto q=rand()%49;
			// print(z,q)
			if (distance(a.begin(),a.lower_bound(q))!=distance(s.begin(),s.lower_bound(q))){
				ic(itervect(s.begin(),s.end()))
				ic(itervect(a.begin(),a.end()))
				ic(q)
				ic(distance(a.begin(),a.lower_bound(q)))
				ic(distance(s.begin(),s.lower_bound(q)))
				treeprint(&a);
			}
			assert(distance(a.begin(),a.lower_bound(q))==distance(s.begin(),s.lower_bound(q)));
		}
		if (z==6){
			auto q=getint();
			// auto q=rand()%49;
			// print(z,q)
			assert(distance(a.begin(),a.upper_bound(q))==distance(s.begin(),s.upper_bound(q)));
		}
		auto x=a.begin();
		auto c=s.begin();
		for (;x!=a.end() and c!=s.end();++x,++c){
			assert(*x==*c);
		}
		assert(x==a.end() and c==s.end());
		if (++c_ > 111){
			treeprint(&a);
		}
	}

	// vector<long> d={8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 25, 26, 27, 28, 29, 31, 33, 34, 35, 36, 38, 39, 42, 44, 46, 47, 48};
	// for (auto w:d){
	// 	a.insert(w);
	// 	s.insert(w);
	// }
	// ic(distance(a.begin(),a.lower_bound(16)));
	// ic(distance(s.begin(),s.lower_bound(16)));

	// for (uint64_t w=0;w<9;++w){
	// 	a.insert(w*2);
	// 	s.insert(w*2);
	// }
	// for (uint64_t w=0;w<20;++w){
	// 	ic(distance(a.begin(),a.lower_bound(w))==distance(s.begin(),s.lower_bound(w)))
	// }
	// // a.erase(4);
	// // a.erase(1);
	// while (a.size()){
	// 	auto i=rand()%a.size();
	// 	auto j=*(a.begin()+i);
	// 	a.erase(*(a.begin()+i));
	// }


	// check(a.begin()-200,a.end()+200);
	// assert(a.end()-a.begin()==a.size());

	// auto g=a.find(20);
	// ic(g.p,g.l,g==nullptr);


	// auto s=a.end()-1;
	// ic(s.l)
	// treeprint(s.p);
	// ++s;
	// ic(s.l)
	// treeprint(s.p);
	// ++s;
	// ic(s.l)
	// treeprint(s.p);
	// --s;
	// ic(s.l)
	// treeprint(s.p);
	// --s;
	// ic(s.l)
	// treeprint(s.p);

	// ic(*s)
	// tree<long>::iter q,e;
	// q=a.begin();
	// e=a.end();
	// q.p=a.next[0];
	// q.l=0;
	// e.p=a.next[1];
	// e.l=0;
	// cout<<*q<<endl;
	// cout<<*e<<endl;
	// cout<<(q-e)<<endl;
	// treeprint(&a,0);
	// auto q=a.begin();
	// auto e=a.end();
	// ic(itervect(q,e))

}

