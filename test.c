#include <stdio.h>

typedef struct node{
	int value;
	struct node *prev;
} node;

void run(int n,int k,node** a){
	if (k){
		node f;
		int g;
		scanf("%i%i",&g,&(f.value));
		f.prev=a[g];
		a[g]=&f;
		run(n,k-1,a);
	}else{
		for (int w=0;w<n;++w){
			while (a[w]){
				printf("%i ",a[w]->value);
				a[w]=a[w]->prev;
			}
			printf("\n");
		}
	}
}


int main(){
	int n,k;
	scanf("%i%i",&n,&k);
	node* a[n];
	for (int w=0;w<n;++w){
		a[w]=0;
	}
	run(n,k,a);
}
