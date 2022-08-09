def treeprint_impl(root,get_left,get_right,get_str,prev_node=None):
	#━┃┏┓┗┛┣┫┳┻╋► 
	if root==None{
		return
	}
	left=get_left(root)
	right=get_right(root)
	st=get_str(root)

    node=[0]*3
	node[0]=prev_node
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

// template<typename T>
// void treeprint(const T&root,size_t* prev_node=0){
// 	//━┃┏┓┗┛┣┫┳┻╋► 
// 	if (!root){
// 		return;
// 	}

// 	size_t node[3];
// 	node[2]=(size_t)NULL;
// 	node[0]=(size_t)prev_node;
// 	if (prev_node){
// 		prev_node[2]=(size_t)node;
// 	}

// 	size_t save=0;
// 	if (prev_node && prev_node[1]==1){
// 		save=prev_node[1];
// 		prev_node[1]=0;
// 	}
// 	node[1]=1;
// 	treeprint(root->next[0],node);
// 	if (save){
// 		prev_node[1]=save;
// 	}

// 	for (uint64_t q=0;q<root->len;++q){

// 		size_t*d=node;
// 		while(d[0]){
// 			d=(size_t*)d[0];
// 		}

// 		for (;d!=node;d=(size_t*)d[2]){
// 			// printf("%li",d[1]);
// 			if (d[1]==3){
// 				if (d==prev_node){
// 					if (q==root->len-1){
// 						printf("┗");
// 					}else{
// 						printf("┣");
// 					}
// 				}else{
// 					printf("┃");
// 				}
// 			}else
// 			if (d[1]==2){
// 				if (d==prev_node){
// 					printf("┣");
// 				}else{
// 					printf("┃");
// 				}
// 			}else
// 			if (d[1]==1){
// 				if (d==prev_node){
// 					if (q==0){
// 						printf("┏");
// 					}else{
// 						printf("┣");
// 					}
// 				}else{
// 					printf("┃");
// 				}
// 			}else{
// 				printf(" ");
// 			}
// 		}

// 		if (root->next[q]==NULL and q==0 and root->next[q+1]==NULL and q==root->len-1){
// 			printf("━");
// 		}else
// 		if (root->next[q]==NULL and q==0){
// 			printf("┳");
// 		}else
// 		if (root->next[q+1]==NULL and q==root->len-1){
// 			printf("┻");
// 		}else{
// 			printf("╋");
// 		}
// 		printf("► ");
// #define _put(s) std::cout<<#s<<" = "<<root->s<<'\t';

// 		_put(data[q])
// 		_put(depth)
// 		_put(longlen)
// 		std::cout<<std::endl;
// 		// printf("%li %li %li\n",root->data[q],root->depth,root->longlen);

// 		save=0;
// 		if (prev_node and q==root->len-1 and prev_node[1]==3){
// 			save=prev_node[1];
// 			prev_node[1]=0;
// 		}
// 		node[1]=2+(q==root->len-1);
// 		treeprint(root->next[q+1],node);
// 		if (save){
// 			prev_node[1]=save;
// 		}
// 	}
// }
