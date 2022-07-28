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
#ifndef HOME
#define HOME
#endif
#endif

#ifdef HOME
#define vector vector_home
#endif

struct vector{
	void* data;
	size_t size;
	size_t dsize;
	size_t elem_size;
};

size_t tmpst=0;

#define check {tmpst=*(char*)(v->data);tmpst=*(char*)(v->data)+v->dsize*v->elem_size-1;}


// #define while(...) assert(not(__VA_ARGS__));while(__VA_ARGS__)

struct vector *vector_new(size_t elems, size_t elem_size){
	// if (!elem_size){
	// 	while (1){}
	// 	return 0;
	// }
	// if (elem_size*elems>=0x1000000000){
	// 	while (1){}
	// 	return 0;
	// }
	struct vector*v=(struct vector*)malloc(sizeof(struct vector));
	// if (!a){
	// 	while(1){}
	// 	return 0;
	// }
	v->elem_size=elem_size;
	v->size=elems;
	v->dsize=elems+1;
	v->data=calloc(1,(elems+1)*elem_size);
	// for (size_t w=0;w<v->dsize*v->elem_size;++w){
	// 	*((uint8_t*)(v->data)+w)=0;
	// }
	// if (!a->data){
	// 	while(1){}
	// 	free(a);
	// 	return 0;
	// }
	check
	return v;
}

int vector_push(struct vector *v, void const *elem){
	// while (v->dsize<v->size){}
	check
	// if (!v or !elem){
	// 	while (1){}
	// 	return 1;
	// }
	if (v->dsize==v->size){
		void*tmp=realloc(v->data,(v->dsize*2+1)*v->elem_size);
		// if (!tmp){
		// 	while(1){}
		// 	return 1;
		// }
		v->data=tmp;
		v->dsize=v->dsize*2+1;
	}
	// if (v->dsize<v->size){
	// 	while (1){}
	// 	return 1;
	// }



	memcpy( (char*)(v->data)+v->elem_size*v->size ,elem,v->elem_size);
	v->size++;
	// while (v->dsize<v->size){}
	// check
	check
	return 0;
}

int vector_pop (struct vector *v, void *elem){
	// while (v->dsize<v->size){}
	check
	// if (!v or !elem){
	// 	while (1){}
	// 	return 1;
	// }
	if (v->size == 0){
		return 1;
	}
	v->size--;
	memcpy(elem,((char*)(v->data)+v->elem_size*v->size),v->elem_size);
	// if (v->size<v->dsize/4+1){
	// 	void*tmp=realloc(v->data,(v->dsize/4+1)*v->elem_size);
	// 	if (!tmp){
	// 		while(1){}
	// 		return 0;
	// 	}
	// 	v->data=tmp;
	// 	v->dsize=v->dsize/4+1;
	// }
	// while (v->dsize<v->size){}
	// check
	check
	return 0;
}

int vector_empty(struct vector const *v){
	// while (v->dsize<v->size){}
	check
	// if (!v){
	// 	while (1){}
	// 	return 1;
	// }
	return v->size==0;
}

struct vector *vector_delete(struct vector *v){
	if (!v){
		return 0;
	}
	// while (v->dsize<v->size){}
	check
	// if (v){
		// if (v->data){
			free(v->data);
		// }else{
		// 	while (1){}
		// }
		free(v);
	// }else{
	// 	while (1){}
	// }
	return 0;
}

void vector_print(struct vector const *v, void (*pf)(void const *data)){
	// while (v->dsize<v->size){}
	check
	// if (v and v->data){
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
	// }else{
	// 	while(1){}
	// }
	check
}

int vector_set(struct vector *v, size_t index, void const *elem){
	// while (v->dsize<v->size){}
	check
	// if (!v or !elem){
	// 	while (1){}
	// 	return 1;
	// }
	if (index>=v->size){
		return 1;
	}
	memcpy((char*)(v->data)+index*v->elem_size,elem,v->elem_size);
	// while (v->dsize<v->size){}
	check
	return 0;
}

int vector_get(struct vector const *v, size_t index, void *elem){
	// while (v->dsize<v->size){}
	// while(call_count){}
	check
	// if (!v or !elem){
	// 	while (1){}
	// 	return 1;
	// }
	// while (v->dsize<v->size){}
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,(char*)(v->data)+index*v->elem_size,v->elem_size);
	// while (v->dsize<v->size){}
	check
	return 0;
}

int vector_resize(struct vector *v, size_t new_size){
	// while (v->dsize<v->size){}
	check
	// if (!v){
	// 	while (1){}
	// 	return 1;
	// }
	// if (v->elem_size*new_size>=0x1000000000){
	// 	while (1){}
	// 	return 1;
	// }
	void*tmp=realloc(v->data,(new_size+1)*v->elem_size);
	// if (!tmp){
	// 	while(1){}
	// 	return 1;
	// }
	v->data=tmp;
	for (size_t w=v->dsize*v->elem_size;w<(new_size+1)*v->elem_size;++w){
		*((uint8_t*)(v->data)+w)=0;
	}
	v->size=new_size;
	v->dsize=new_size+1;
	// for (size_t w=0;w<v->dsize*v->elem_size;++w){while( ((uint8_t*)(v->data)) [w]>300+call_count){}}
	// while (v->dsize<v->size){}
	check
	return 0;
}

size_t vector_size(struct vector const *v){
	check
	// if (v){
		return v->size;
	// }else{
	// 	while (1){}
	// 	return 0;
	// }
}

#ifdef HOME
static void print_int(void const *data) {
	uint32_t r=0,t=0;
	int y;
	uint8_t*id=(uint8_t*)(data);
	t=id[0];
	r+=t;
	t=id[1];
	t<<=8;
	r+=t;
	t=id[2];
	t<<=16;
	r+=t;
	r<<=8;
	r>>=8;
	y=r;
	if (y>=1U<<23){
		y-=1U<<24;
	}
	printf("%d", y);
}

int main() {
	struct vector*v=0;
	for (;1;){
		int q=0,w=0,r=0,e=0;
		scanf("%i",&q);
		if (q==0){
			scanf("%i",&w);
			vector_delete(v);
			v=vector_new(w,3);
			for (int t=0;t<w;++t){
				r+=vector_set(v,t,&t);
			}
			printf("%i\n",r);
		}else
		if (q==1){
			scanf("%i",&w);
			r=vector_push(v,&w);
			printf("%i\n",r);
		}else
		if (q==2){
			r=vector_pop(v,&w);
			printf("%i %i\n",r,w);
		}else
		if (q==3){
			r=vector_empty(v);
			printf("%i\n",r);
		}else
		if (q==4){
			v=vector_delete(v);
		}else
		if (q==5){
			vector_print(v,print_int);
		}else
		if (q==6){
			scanf("%i %i",&w,&e);
			r=vector_set(v,e,&w);
			printf("%i\n",r);
		}else
		if (q==7){
			scanf("%i",&e);
			r=vector_get(v,e,&w);
			printf("%i %i\n",w,r);
		}else
		if (q==8){
			scanf("%i",&w);
			e=vector_size(v);
			r=vector_resize(v,w);
			for (size_t t=e;t<w;++t){
				r+=vector_set(v,t,&t);
			}
			printf("%i\n",r);
		}else
		if (q==9){
			w=vector_size(v);
			printf("%i\n",w);
		}else{
			break;
		}
	}
}
#endif
