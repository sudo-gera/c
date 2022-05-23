#include <bits/stdc++.h>
using namespace std;

struct item{
	long a,b;
	item*prev=0;
	item*left=0;
	item*right=0;
	long p=0;
};

bool less_(item q,item e){
	return q.a<e.a;
}

void build(vector<item>&a){
	uint64_t n=a.size();
	item*last=&a[0];
	for (uint64_t w=1;w<n;++w){
		item*c=last;
		assert(c->right==0);
		while(c->prev and c->b>=a[w].b){
			c=c->prev;
		}
		if (c->b>=a[w].b){
			c->prev=&a[w];
			a[w].left=c;
		}else{
			if (c->right){
				assert(c->right->b>=a[w].b);
				c->right->prev=&a[w];
				a[w].left=c->right;
			}
			assert(c->b<=a[w].b);
			c->right=&a[w];
			a[w].prev=c;
		}
		last=&a[w];
	}
}

void check(vector<item>&a){
	uint64_t n=a.size();
	for (uint64_t w=0;w<n;++w){
		if (a[w].prev){
			assert(a[w].prev->b<=a[w].b);
		}
		if (a[w].left){
			assert(a[w].left->b>=a[w].b);
		}
		if (a[w].right){
			assert(a[w].right->b>=a[w].b);
		}
	}
}

int main(){
	uint64_t n;
	cin>>n;
	vector<item> a(n);
	for (auto i = 0; i <n;++i){
		cin>>a[i].a;
		cin>>a[i].b;
		a[i].p=i;
	}
	sort(a.begin(), a.end(),less_);
	build(a);
	check(a);
	printf("YES\n");
	for (uint64_t w=0;w<n;++w){
		printf("%li %li %li\n",a[w].prev?a[w].prev->p+1:0,a[w].left?a[w].left->p+1:0,a[w].right?a[w].right->p+1:0);
	}
}
