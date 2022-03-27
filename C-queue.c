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
#define queue queue_home
#endif

struct queue{
	void* data;
	size_t size;
	size_t dsize;
	size_t elem_size;
	size_t used;
};

size_t tmpst=0;

#define check {if(v->data){tmpst=access(0)[0];tmpst=access(v->size)[0];tmpst=access(v->used)[0];}if(v->size>v->dsize or v->used>v->size){tmpst=*(int*)0;};}
// #define check {if(v->data){tmpst=*(char*)(v->data);tmpst=*((char*)(v->data)+v->size*v->elem_size);}while(v->size>v->dsize){};}


#define access(index) ((uint8_t*)(v->data)+(index)*v->elem_size)


int queue_resize(struct queue *v, size_t new_size){
	if (!v){
		return 1;
	}
	check
	if (new_size+1>v->dsize){
		void*tmp=realloc(v->data,(new_size+1)*v->elem_size);
		// if (!tmp){
		// 	return 1;
		// }
		v->data=tmp;
		// for (size_t w=v->dsize*v->elem_size;w<(new_size+1)*v->elem_size;++w){
		// 	access(0)[w]=0;
		// }
		v->dsize=new_size+1;
	}else{
		// for (size_t w=new_size*v->elem_size;w<v->size*v->elem_size;++w){
		// 	access(0)[w]=0;
		// }
	}
	v->size=new_size;
	check
	return 0;
}

struct queue *queue_new(size_t elem_size){
	if (!elem_size){
		return 0;
	}
	struct queue*v=(struct queue*)malloc(sizeof(struct queue));
	if (!v){
		return 0;
	}
	v->data=0;
	v->dsize=0;
	v->size=0;
	v->used=0;
	v->elem_size=elem_size;
	if (queue_resize(v,0)){
		free(v);
		return 0;
	}
	check
	return v;
}

int queue_empty(struct queue const *v){
	if (!v){
		return 1;
	}
	check
	return v->size==v->used;
}

struct queue *queue_delete(struct queue *v){
	check
	if (v){
		if (v->data){
			free(v->data);
			v->data=0;
		}
		free(v);
	}
	return 0;
}

void queue_print(struct queue const *v, void (*pf)(void const *data)){
	check
	printf("[");
	int c=0;
	for (size_t w=v->used;w<v->size;++w){
		if (c){
			printf(", ");
		}else{
			c=1;
		}
		(*pf)(access(w));
	}
	printf("]\n");
	check
}

int queue_set(struct queue *v, size_t index, void const *elem){
	if (!v or !elem){
		return 1;
	}
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(access(index),elem,v->elem_size);
	check
	return 0;
}

int queue_get(struct queue const *v, size_t index, void *elem){
	if (!v or !elem){
		return 1;
	}
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,access(index),v->elem_size);
	check
	return 0;
}

int queue_push(struct queue *v, void const *elem){
	if (!v or !elem){
		return 1;
	}
	check
	size_t s=v->size;
	if (v->dsize==v->size+1){
		if (queue_resize(v,v->dsize*2+1)){
			return 1;
		}
	}
	v->size=s+1;
	if (queue_set(v,v->size-1,elem)){
		return 1;
	}
	check
	return 0;
}

int queue_pop(struct queue *v, void *elem){
	if (!v or !elem){
		return 1;
	}
	check
	if (v->size == v->used){
		return 1;
	}
	if (queue_get(v,v->used,elem)){
		return 1;
	}
	v->used+=1;
	// for (size_t w=(v->used-1)*v->elem_size;w<v->used*v->elem_size;++w){
	// 	access(0)[w]=0;
	// }
	check
	return 0;
}

size_t queue_size(struct queue const *v){
	if (!v){
		return 0;
	}
	check
	return v->size;
}










#ifdef HOME
static void print_int(void const *data) {
	uint32_t r=0,t=0;
	uint32_t y=0;
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
	// if (y>=(1<<23)){
	// 	y-=1<<24;
	// }
	printf("%u", y);
}

int main() {
	struct queue*v=queue_new(3);
	for (;1;){
		uint32_t q=0,w=0,r=0,e=0;
		__int128_t ww=0;
		scanf("%u",&q);
		printf("- %i\n",q);
		if (q==0){
			v=queue_delete(v);
			v=queue_new(3);
		}else
		if (q==1){
			scanf("%u",&w);
			ww=w;
			r=queue_push(v,&ww);
			printf("%i\n",r);
		}else
		if (q==2){
			r=queue_pop(v,&ww);
			printf("%u ",r);
			print_int(&ww);
			printf("\n");
		}else
		if (q==3){
			r=queue_empty(v);
			printf("%u\n",r);
		}else
		if (q==4){
			queue_print(v,print_int);
		}else{
			break;
		}
	}
}
#endif
