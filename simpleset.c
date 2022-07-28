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
#define set set_home
#endif

struct set{
	uint8_t*data;
	size_t dsize;
	size_t size;
};


#define bit_get(a,s)   (((a)[(s)/8/sizeof((a)[0])]>>(s)%(8*sizeof((a)[0])))&1)
#define bit_set(a,s,d) {(a)[(s)/8/sizeof((a)[0])]&=~(1<<(s)%(8*sizeof((a)[0])));(a)[(s)/8/sizeof((a)[0])]+=(d)<<(s)%(8*sizeof((a)[0]));}

size_t tmpst=0;

#define check {if (s){tmpst=bit_get(s->data,0);tmpst=bit_get(s->data,s->dsize-1);}}

// Создать новое пустое множество, значения элементов которого могут лежать в границах от 0 до capacity-1 включительно. Вернуть указатель на него.
struct set *set_new(size_t capacity){
	struct set*s=(struct set*)malloc(sizeof(struct set));
	s->dsize=capacity;
	s->size=0;
	s->data=(uint8_t*)calloc(1,capacity/8+8);
	check
	return s;
}

int set_insert(struct set *s, size_t elem){
	check
	if (!s or elem>=s->dsize){
		return 1;
	}
	if (bit_get(s->data,elem) == 0){
		s->size++;
		bit_set(s->data,elem,1);
	}
	check
	return 0;
}
// Добавить во множество s элемент elem. Если элемент существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
int set_erase(struct set *s, size_t elem){
	check
	if (!s or elem>=s->dsize){
		return 1;
	}
	if (get(elem) != 0){
		s->size--;
		del(elem)
	}
	check
	return 0;
}
// Удалить элемент из множества. Если элемент не существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
int set_find(struct set const *s, size_t elem){
	check
	if (!s){
		return 0;
	}
	if (s->dsize<=elem){
		return 0;
	}
	check
	return get(elem);
}
// Вернуть 1, если элемент присутствует в множестве и 0 в противном случае.
struct set *set_delete(struct set *s){
	check
	if (s){
		if (s->data){
			free(s->data);
		}
		free(s);
	}
	return 0;
}
// Удалить объект множество и вернуть NULL
int set_empty(struct set const *s){
	check
	if (!s){
		return 1;
	}
	check
	return s->size==0;
}
// Предикат: вернуть единицу, если в множестве есть хотя бы один элемент и ноль в противном случае.
ssize_t set_findfirst(struct set const *s, size_t start){
	check
	if (!s){
		return -1;
	}
	for (size_t w=start;w<s->dsize;++w){
		if (bit_get(s->data,w)){
			return w;
		}
	}
	check
	return -1;
}
// Вернуть наименьший из элементов множества, не меньших start. Если таких элементов нет (например, множество пустое), то вернуть -1.
size_t set_size(struct set const *s){
	if (!s){
		return 0;
	}
	check
	return s->size;
}
// Вернуть количество элементов множества.
void set_print(struct set const *s){
	check
	if (!s){
		return;
	}
	printf("[");
	int c=0;
	int val=0;
	val=set_findfirst(s,val);
	while (val!=-1){
		if (c){
			printf(", ");
		}else{
			c=1;
		}
		printf("%i",val);
		val=set_findfirst(s,val+1);
	}
	printf("]\n");
	check
}
// Вывести на стандартный вывод содержимое множества в формате по образцу: []\n или [1, 2, 3]\n.

#ifdef HOME
int main() {
	struct set*v=0;
	while (1){
		int q=0,w=0,r=0,e=0;
		scanf("%i",&q);
		if (q==0){
			scanf("%i",&w);
			v=set_delete(v);
			v=set_new(abs(w));
			printf("%i\n",r);
		}else
		if (q==1){
			scanf("%i",&w);
			r=set_insert(v,w);
			printf("%i\n",r);
		}else
		if (q==2){
			scanf("%i",&w);
			r=set_erase(v,w);
			printf("%i\n",r);
		}else
		if (q==3){
			scanf("%i",&w);
			r=set_find(v,w);
			printf("%i\n",r);
		}else
		if (q==4){
			v=set_delete(v);
		}else
		if (q==5){
			r=set_empty(v);
			printf("%i\n",r);
		}else
		if (q==6){
			scanf("%i",&w);
			r=set_findfirst(v,w);
			printf("%i\n",r);
		}else
		if (q==7){
			r=set_size(v);
			printf("%i\n",r);
		}else
		if (q==8){
			set_print(v);
		}else
		{
			break;
		}
	}
}
#endif
