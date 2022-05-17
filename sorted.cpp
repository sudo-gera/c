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
#include <algorithm>

template <typename T>
struct tree;

void treep(tree<long>*,uint64_t);

template <typename T>
struct tree{
	tree* next[4];
	T data[3];
	tree*prev;
	uint64_t len;
	uint64_t size;
	tree(){
		memset(this,0,sizeof(*this));
	}
	void update(){
		size=len;
		for (uint64_t w=0;w<len+1;w++){
			if (next[w]){
				size+=next[w]->size;
				next[w]->prev=this;
			}
		}
	}
	void insert3(T val){
		// ic(val)
		assert(len<3);
		for (uint64_t w=0;w<len;w++){
			if (data[w]==val){
				return;
			}
		}
		uint64_t tmp=len;
		for (uint64_t w=0;w<len+1;w++){
			if (next[w]){
				tmp+=next[w]->size;
				assert(next[w]->prev==this);
			}
		}
		// ic(tmp,size)
		assert(tmp==size);
		if (next[0]==0){
			data[len++]=val;
			std::sort(data,data+len);
			size++;
		}else{
			for (uint64_t q=0;q<4;++q){
				assert(q<3);
				if (len==q or data[q]>val){
					// ic(q)
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
		// ic()
	}
	void insert(T val){
		insert3(val);
		// treep(this,0);
		// printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
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
		void add(long n){
			while(n!=0 or !(0<=l and l<p->len or !p->prev)){
				ic(n,l)
				treeprint(p);
				if (0<=l and l<p->len){
					if (n>0){
						if ((p->next[l+1]?p->next[l+1]->size:0)<n){
				ic(n,l)
							n-=(p->next[l+1]?p->next[l+1]->size:0)+1;
							l++;
				ic(n,l)
						}else{
							ic()
							p=p->next[l+1];
							l=0;
							n-=p->next[0]?p->next[0]->size:0;
							n-=1;
						}
					}else{
						if ((p->next[l]?p->next[l]->size:0)<-n){
							n+=(p->next[l]?p->next[l]->size:0)+1;
							l--;
						}else{
							p=p->next[l];
							l=p->len-1;
							n+=p->next[l+1]?p->next[l+1]->size:0;
							n+=1;
						}
					}
				}else{
					if (p->prev){
						uint64_t w=0;
						for (;p->prev->next[w]!=p;++w);
						p=p->prev;
						if (l<0){
							l=w-1;
						}else{
							l=w;
						}
					}else{
						n=0;
					}
				}
				ic(n,l)
			}
		}


		T&operator*(){
			return p->data[l];
		}

		// auto&operator--(){
		// 	return *this-=1;
		// }
		// auto&operator++(){
		// 	return *this+=1;
		// }
		// auto operator--(int){
		// 	auto q=*this;
		// 	*this-=1;
		// 	return q;
		// }
		// auto operator++(int){
		// 	auto q=*this;
		// 	*this+=1;
		// 	return q;
		// }
		// auto&operator+=(long w){
		// 	w*=d;
		// 	w+=o;
		// 	if (!e){
		// 		return *this;
		// 	}
		// 	while (1){
		// 		auto s=w*2;
		// 		auto q=e;
		// 		q=nullptr;
		// 		while (!q){
		// 			s/=2;
		// 			q=add(e,s);
		// 		}
		// 		if (q==e){
		// 			break;
		// 		}
		// 		e=q;
		// 		w-=s;
		// 	}
		// 	o=w;
		// 	return *this;
		// }
		// auto&operator-=(long w){
		// 	return *this+=(-w);
		// }
		// auto&operator[](long q){
		// 	return *(*this+q);
		// }
		// auto& operator=(const iter&q){
		// 	e=q.e;
		// 	o=q.o;
		// 	d=q.d;
		// 	return *this;
		// }
	};
};



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


int main(){
	tree<long> a;
	for (uint64_t w=0;w<20;++w){
		a.insert(rand()%99);
	// treeprint(&a,0);
	}
	treeprint(&a,0);
	auto p=tree<long>::iter();
	p.p=&a;
	p.l=0;
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	ic(*p);
	p.add(1);
	// ic(*p);
	// p.add(1);
	ic(*p);
	p.add(-1);
	ic(*p);
	p.add(-1);
	ic(*p);
	p.add(-1);
	ic(*p);
}
