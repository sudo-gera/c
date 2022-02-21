#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

#if __has_include("d")
#define HOME
#endif

#ifdef HOME
#define stack stack_home
#endif

struct stack{
	void* data;
	size_t size;
	size_t dsize;
	size_t elem_size;
};

struct stack *stack_new(size_t elem_size){
	size_t elems=0;
	struct stack*a=(struct stack*)malloc(sizeof(struct stack));
	if (!a){
		return 0;
	}
	if (elem_size*elems>=0x10000000000){
		return 0;
	}
	a->data=malloc(elems*elem_size);
	if (!a->data){
		return 0;
	}
	a->elem_size=elem_size;
	a->size=elems;
	a->dsize=elems;
	return a;
}

int stack_push(struct stack *v, void const *elem){
	if (!v or !elem){
		return 1;
	}
	if (v->dsize==v->size){
		void*tmp=realloc(v->data,(v->dsize*2+1)*v->elem_size);
		if (!tmp){
			return 1;
		}
		v->data=tmp;
		v->dsize*=2;
		v->dsize+=1;
	}
	memcpy( (char*)(v->data)+v->elem_size*v->size ,elem,v->elem_size);
	v->size++;
	return 0;
}

int stack_pop (struct stack *v, void *elem){
	if (!v or !elem){
		return 1;
	}
	if (!v->size){
		return 1;
	}
	v->size--;
	memcpy(elem,((char*)(v->data)+v->elem_size*v->size),v->elem_size);
	if (v->size<v->dsize/4){
		void*tmp=realloc(v->data,v->dsize/4*v->elem_size);
		if (!tmp){
			return 0;
		}
		v->data=tmp;
		v->dsize/=4;
	}
	return 0;
}

int stack_top (struct stack *v, void *elem){
	if (!v or !elem){
		return 1;
	}
	if (!v->size){
		return 1;
	}
	v->size--;
	memcpy(elem,((char*)(v->data)+v->elem_size*v->size),v->elem_size);
	v->size++;
	return 0;
}

int stack_empty(struct stack const *v){
	if (!v){
		return 1;
	}
	return v->size==0;
}

struct stack *stack_delete(struct stack *v){
	if (v){
		free(v->data);
		free(v);
	}
	return 0;
}

void stack_print(struct stack const *v, void (*pf)(void const *data)){
	if (v){
		printf("[");
		int c=0;
		for (size_t w=0;w<v->size;++w){
			if (c){
				printf(", ");
			}else{
				c=1;
			}
			(*pf)((char*)(v->data)+w*v->elem_size);
		}
		printf("]\n");
	}
}

int stack_set(struct stack *v, size_t index, void const *elem){
	if (!v or !elem){
		return 1;
	}
	if (index>=v->size){
		return 1;
	}
	memcpy((char*)(v->data)+index*v->elem_size,elem,v->elem_size);
	return 0;
}

int stack_get(struct stack const *v, size_t index, void *elem){
	if (!v or !elem){
		return 1;
	}
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,(char*)(v->data)+index*v->elem_size,v->elem_size);
	return 0;
}

int stack_resize(struct stack *v, size_t new_size){
	if (!v){
		return 1;
	}
	void*tmp=realloc(v->data,new_size*v->elem_size);
	if (!tmp){
		return 1;
	}
	v->data=tmp;
	return 0;
}

size_t stack_size(struct stack const *v){
	if (v){
		return v->size;
	}else{
		return 0;
	}
}

#ifdef HOME
static void print_int(void const *data) {
   printf("%d", *(int *)data);
}

int main() {
	struct stack*v=0;
	while (1){
		int q=0,w=0,r=0,e=0;
		scanf("%i",&q);
		if (q==0){
			scanf("%i",&w);
			if (!v){
				stack_delete(v);
			}
			v=stack_new(w,sizeof(int));
			for (int t=0;t<w;++t){
				r+=stack_set(v,t,&t);
			}
			printf("%i\n",r);
		}else
		if (q==1){
			scanf("%i",&w);
			r=stack_push(v,&w);
			printf("%i\n",r);
		}else
		if (q==2){
			r=stack_pop(v,&w);
			printf("%i %i\n",r,w);
		}else
		if (q==3){
			r=stack_empty(v);
			printf("%i\n",r);
		}else
		if (q==4){
			v=stack_delete(v);
		}else
		if (q==5){
			stack_print(v,print_int);
		}else
		if (q==6){
			scanf("%i %i",&w,&e);
			r=stack_set(v,e,&w);
			printf("%i\n",r);
		}else
		if (q==7){
			scanf("%i",&e);
			r=stack_get(v,e,&w);
			printf("%i %i\n",w,r);
		}else
		if (q==8){
			scanf("%i",&w);
			e=stack_size(v);
			r=stack_resize(v,w);
			for (size_t t=e;t<w;++t){
				r+=stack_set(v,t,&t);
			}
			printf("%i\n",r);
		}else
		if (q==9){
			w=stack_size(v);
			printf("%i\n",w);
		}else{
			break;
		}
	}
}
#endif
