#include <stdio.h>
#include <stdlib.h>

typedef void* (* func_t) (void*);

void treeprint(
	void*root,
	func_t get_left,
	func_t get_right,
	func_t get_str
);

void treeprint_impl(void*,func_t,func_t,func_t,size_t*);

void treeprint(void*root,func_t l,func_t r,func_t s){
	treeprint_impl(root,l,r,s,NULL);
}

void treeprint_impl(void*root,func_t get_left,func_t get_right,func_t get_str,size_t* prev_node){
	//━┃┏┓┗┛┣┫┳┻╋► 
	if (!root){
		return;
	}
	void*left=get_left(root);
	void*right=get_right(root);
	char*str=(char*)get_str(root);

	size_t node[3];
	node[2]=(size_t)NULL;
	node[0]=(size_t)prev_node;
	if (prev_node){
		prev_node[2]=(size_t)node;
	}

	size_t save=0;
	if (prev_node && prev_node[1]==2){
		save=prev_node[1];
		prev_node[1]=0;
	}
	node[1]=2;
	treeprint_impl(left,get_left,get_right,get_str,node);
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
				printf("┗");
			}else{
				printf("┃");
			}
		}else
		if (d[1]==2){
			if (d==prev_node){
				printf("┏");
			}else{
				printf("┃");
			}
		}else{
			printf(" ");
		}
	}

	if (left==NULL && right==NULL){
		printf("━");
	}else
	if (left==NULL){
		printf("┳");
	}else
	if (right==NULL){
		printf("┻");
	}else{
		printf("╋");
	}
	printf("► ");
	printf("%s\n",str);
	free(str);

	save=0;
	if (prev_node && prev_node[1]==1){
		save=prev_node[1];
		prev_node[1]=0;
	}
	node[1]=1;
	treeprint_impl(right,get_left,get_right,get_str,node);
	if (save){
		prev_node[1]=save;
	}
}
