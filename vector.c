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

<<<<<<< HEAD
struct vector *vector_new(size_t elems, size_t elem_size){
	struct vector*a=(struct vector*)malloc(sizeof(struct vector));
	if (!a){
		return 0;
	}
	if (elem_size*elems>=0x10000000000){
		return 0;
	}
	a->elem_size=elem_size;
	a->size=elems;
	a->dsize=elems+1;
	a->data=malloc((elems+1)*elem_size);
	if (!a->data){
		return 0;
	}
	return a;
}

int vector_push(struct vector *v, void const *elem){
	if (!v or !elem){
		return 1;
	}
	if (v->dsize==v->size){
		void*tmp=realloc(v->data,(v->dsize*2+1)*v->elem_size);
=======
size_t tmpst=0;

#define check {if(v->data){tmpst=*(char*)(v->data);tmpst=*((char*)(v->data)+v->size*v->elem_size);}while(v->size>v->dsize){};}

#define access(index) ((uint8_t*)(v->data)+(index)*v->elem_size)


int vector_resize(struct vector *v, size_t new_size){
	if (!v){
		return 1;
	}
	check
	if (new_size+1>v->dsize){
		void*tmp=realloc(v->data,(new_size+1)*v->elem_size);
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
		if (!tmp){
			return 1;
		}
		v->data=tmp;
<<<<<<< HEAD
		v->dsize*=2;
		v->dsize+=1;
	}
	memcpy( (char*)(v->data)+v->elem_size*v->size ,elem,v->elem_size);
	v->size++;
	return 0;
}

int vector_pop (struct vector *v, void *elem){
	if (!v or !elem){
		return 1;
	}
	if (v->size == 0){
		return 1;
	}
	v->size--;
	memcpy(elem,((char*)(v->data)+v->elem_size*v->size),v->elem_size);
	// if (v->size<v->dsize/4){
	// 	void*tmp=realloc(v->data,v->dsize/4*v->elem_size);
	// 	if (!tmp){
	// 		return 0;
	// 	}
	// 	v->data=tmp;
	// 	v->dsize/=4;
	// }
	return 0;
=======
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
	if (!elem_size){
		return 0;
	}
	struct vector*v=(struct vector*)malloc(sizeof(struct vector));
	if (!v){
		return 0;
	}
	v->data=0;
	v->dsize=0;
	v->size=0;
	v->elem_size=elem_size;
	if (vector_resize(v,elems)){
		free(v);
		return 0;
	}
	check
	return v;
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
}

int vector_empty(struct vector const *v){
	if (!v){
		return 1;
	}
<<<<<<< HEAD
=======
	check
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	return v->size==0;
}

struct vector *vector_delete(struct vector *v){
<<<<<<< HEAD
	if (v){
		free(v->data);
=======
	check
	if (v){
		if (v->data){
			free(v->data);
			v->data=0;
		}
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
		free(v);
	}
	return 0;
}

void vector_print(struct vector const *v, void (*pf)(void const *data)){
<<<<<<< HEAD
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
=======
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
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
}

int vector_set(struct vector *v, size_t index, void const *elem){
	if (!v or !elem){
		return 1;
	}
<<<<<<< HEAD
	if (index>=v->size){
		return 1;
	}
	memcpy((char*)(v->data)+index*v->elem_size,elem,v->elem_size);
=======
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(access(index),elem,v->elem_size);
	check
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	return 0;
}

int vector_get(struct vector const *v, size_t index, void *elem){
	if (!v or !elem){
		return 1;
	}
<<<<<<< HEAD
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,(char*)(v->data)+index*v->elem_size,v->elem_size);
	return 0;
}

int vector_resize(struct vector *v, size_t new_size){
	if (!v){
		return 1;
	}
	void*tmp=realloc(v->data,(new_size+1)*v->elem_size);
	if (!tmp){
		return 1;
	}
	v->data=tmp;
	v->size=new_size;
	v->dsize=new_size+1;
=======
	check
	if (index>=v->size){
		return 1;
	}
	memcpy(elem,access(index),v->elem_size);
	check
	return 0;
}

int vector_push(struct vector *v, void const *elem){
	if (!v or !elem){
		return 1;
	}
	check
	size_t s=v->size;
	if (v->dsize==v->size+1){
		if (vector_resize(v,v->dsize*2+1)){
			return 1;
		}
	}
	v->size=s+1;
	if (vector_set(v,v->size-1,elem)){
		return 1;
	}
	check
	return 0;
}

int vector_pop(struct vector *v, void *elem){
	if (!v or !elem){
		return 1;
	}
	check
	if (v->size == 0){
		return 1;
	}
	if (vector_get(v,v->size-1,elem)){
		return 1;
	}
	// for (size_t w=(v->size-1)*v->elem_size;w<v->size*v->elem_size;++w){
	// 	access(0)[w]=0;
	// }
	v->size--;
	check
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	return 0;
}

size_t vector_size(struct vector const *v){
<<<<<<< HEAD
	if (v){
		return v->size;
	}else{
		return 0;
	}
}

=======
	if (!v){
		return 0;
	}
	check
	return v->size;
}










>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
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
<<<<<<< HEAD
	if (y>=1U<<23){
		y-=1U<<24;
=======
	if (y>=(1<<23)){
		y-=1<<24;
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
	}
	printf("%d", y);
}

int main() {
	struct vector*v=0;
<<<<<<< HEAD
	while (1){
		int q=0,w=0,r=0,e=0;
		scanf("%i",&q);
		if (q==0){
			scanf("%i",&w);
			if (!v){
				vector_delete(v);
			}
			v=vector_new(w,3);
			for (int t=0;t<w;++t){
				r+=vector_set(v,t,&t);
			}
=======
	for (;1;){
		int q=0,w=0,r=0,e=0;
		__int128_t ww=0;
		scanf("%i",&q);
		printf("- %i\n",q);
		if (q==0){
			scanf("%i",&w);
			if (v){v=vector_delete(v);}
			v=vector_new(abs(w),11);
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
			printf("%i\n",r);
		}else
		if (q==1){
			scanf("%i",&w);
<<<<<<< HEAD
			r=vector_push(v,&w);
			printf("%i\n",r);
		}else
		if (q==2){
			r=vector_pop(v,&w);
			printf("%i %i\n",r,w);
=======
			ww=w;
			r=vector_push(v,&ww);
			printf("%i\n",r);
		}else
		if (q==2){
			r=vector_pop(v,&ww);
			printf("%i ",r);
			print_int(&ww);
			printf("\n");
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
		}else
		if (q==3){
			r=vector_empty(v);
			printf("%i\n",r);
		}else
<<<<<<< HEAD
		if (q==4){
			v=vector_delete(v);
		}else
=======
		// if (q==4){
		// 	if (v){v=vector_delete(v);}
		// }else
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
		if (q==5){
			vector_print(v,print_int);
		}else
		if (q==6){
			scanf("%i %i",&w,&e);
<<<<<<< HEAD
			r=vector_set(v,e,&w);
=======
			ww=w;
			r=vector_set(v,e,&ww);
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
			printf("%i\n",r);
		}else
		if (q==7){
			scanf("%i",&e);
<<<<<<< HEAD
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
=======
			r=vector_get(v,e,&ww);
			printf("%i ",r);
			print_int(&ww);
			printf("\n");
		}else
		if (q==8){
			scanf("%i",&w);
			// e=vector_size(v);
			r=vector_resize(v,abs(w));
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
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
