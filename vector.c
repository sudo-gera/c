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

#define check {if(v->data){tmpst=*(char*)(v->data);tmpst=*((char*)(v->data)+v->size*v->elem_size);}while(v->size>v->dsize){};}

#define access(index) ((uint8_t*)(v->data)+(index)*v->elem_size)


int vector_resize(struct vector *v, size_t new_size){
	check
	if (new_size+1>v->dsize){
		v->data=realloc(v->data,(new_size+1)*v->elem_size);
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

struct vector *vector_new(size_t elems, size_t elem_size){
	struct vector*v=(struct vector*)malloc(sizeof(struct vector));
	v->data=0;
	v->dsize=0;
	v->size=0;
	v->elem_size=elem_size;
	vector_resize(v,elems);
	check
	return v;
}

int vector_empty(struct vector const *v){
	check
	return v->size==0;
}

struct vector *vector_delete(struct vector *v){
	check
	free(v->data);
	free(v);
	return 0;
}

void vector_print(struct vector const *v, void (*pf)(void const *data)){
	check
	printf("[");
	int c=0;
	for (size_t w=0;w<v->size;++w){
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

int vector_set(struct vector *v, size_t index, void const *elem){
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(access(index),elem,v->elem_size);
	check
	return 0;
}

int vector_get(struct vector const *v, size_t index, void *elem){
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,access(index),v->elem_size);
	check
	return 0;
}

int vector_push(struct vector *v, void const *elem){
	check
	size_t s=v->size;
	if (v->dsize==v->size+1){
		vector_resize(v,v->dsize*2+1);
	}
	v->size=s+1;
	vector_set(v,v->size-1,elem);
	check
	return 0;
}

int vector_pop(struct vector *v, void *elem){
	check
	if (v->size == 0){
		return 1;
	}
	vector_get(v,v->size-1,elem);
	// for (size_t w=(v->size-1)*v->elem_size;w<v->size*v->elem_size;++w){
	// 	access(0)[w]=0;
	// }
	v->size--;
	check
	return 0;
}

size_t vector_size(struct vector const *v){
	check
	return v->size;
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
	if (y>=(1<<23)){
		y-=1<<24;
	}
	printf("%d", y);
}

int main() {
	struct vector*v=0;
	for (;1;){
		int q=0,w=0,r=0,e=0;
		__int128_t ww=0;
		scanf("%i",&q);
		printf("- %i\n",q);
		if (q==0){
			scanf("%i",&w);
			if (v){v=vector_delete(v);}
			v=vector_new(abs(w),11);
			printf("%i\n",r);
		}else
		if (q==1){
			scanf("%i",&w);
			ww=w;
			r=vector_push(v,&ww);
			printf("%i\n",r);
		}else
		if (q==2){
			r=vector_pop(v,&ww);
			printf("%i ",r);
			print_int(&ww);
			printf("\n");
		}else
		if (q==3){
			r=vector_empty(v);
			printf("%i\n",r);
		}else
		// if (q==4){
		// 	if (v){v=vector_delete(v);}
		// }else
		if (q==5){
			vector_print(v,print_int);
		}else
		if (q==6){
			scanf("%i %i",&w,&e);
			ww=w;
			r=vector_set(v,e,&ww);
			printf("%i\n",r);
		}else
		if (q==7){
			scanf("%i",&e);
			r=vector_get(v,e,&ww);
			printf("%i ",r);
			print_int(&ww);
			printf("\n");
		}else
		if (q==8){
			scanf("%i",&w);
			// e=vector_size(v);
			r=vector_resize(v,abs(w));
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
