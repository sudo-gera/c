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
#define set set_home
#endif

struct set{
	uint8_t*data;
	size_t size;
	size_t usize;
};

struct set *set_new(size_t capacity){
	struct set*a=(struct set*)malloc(sizeof(struct set));
	a->size=capacity;
	a->usize=0;
	a->data=(uint8_t*)calloc(1,capacity/8+1);
	return a;
}
// Создать новое пустое множество, значения элементов которого могут лежать в границах от 0 до capacity-1 включительно. Вернуть указатель на него.

int set_insert(struct set *s, size_t elem){
	if (!s or elem>=s->size){
		return 1;
	}
	if ((s->data[elem/8]&(1U<<(elem%8))) == 0){
		s->usize++;
		s->data[elem/8]+=1U<<(elem%8);
	}
	return 0;
}
// Добавить во множество s элемент elem. Если элемент существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
int set_erase(struct set *s, size_t elem){
	if (!s or elem>=s->size){
		return 1;
	}
	if ((s->data[elem/8]&(1U<<(elem%8))) != 0){
		s->usize--;
		s->data[elem/8]-=1U<<(elem%8);
	}
	return 0;
}
// Удалить элемент из множества. Если элемент не существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
int set_find(struct set const *s, size_t elem){
	if (!s){
		return 0;
	}
	if (s->size<=elem){
		return 0;
	}
	return s->data[elem/8]>>(elem%8)&1U;
}
// Вернуть 1, если элемент присутствует в множестве и 0 в противном случае.
struct set *set_delete(struct set *s){
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
	if (!s){
		return 1;
	}
	return s->usize==0;
}
// Предикат: вернуть единицу, если в множестве есть хотя бы один элемент и ноль в противном случае.
ssize_t set_findfirst(struct set const *s, size_t start){
	if (!s){
		return -1;
	}
	for (size_t w=start;w<s->size;++w){
		if (set_find(s,w)){
			return w;
		}
	}
	return -1;
}
// Вернуть наименьший из элементов множества, не меньших start. Если таких элементов нет (например, множество пустое), то вернуть -1.
size_t set_size(struct set const *s){
	if (!s){
		return 0;
	}
	return s->usize;
}
// Вернуть количество элементов множества.
void set_print(struct set const *s){
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
}
// Вывести на стандартный вывод содержимое множества в формате по образцу: []\n или [1, 2, 3]\n.

#ifdef HOME
int main() {
	// struct set*v=0;
	// while (1){
	// 	int q=0,w=0,r=0,e=0;
	// 	scanf("%i",&q);
	// 	if (q==0){
	// 		scanf("%i",&w);
	// 		v=set_delete(v);
	// 		v=set_new(w);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==1){
	// 		scanf("%i",&w);
	// 		r=set_insert(v,w);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==2){
	// 		scanf("%i",&w);
	// 		r=set_erase(v,w);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==3){
	// 		scanf("%i",&w);
	// 		r=set_find(v,w);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==4){
	// 		v=set_delete(v);
	// 	}else
	// 	if (q==5){
	// 		r=set_empty(v);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==6){
	// 		scanf("%i",&w);
	// 		r=set_findfirst(v,w);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==7){
	// 		r=set_size(v);
	// 		printf("%i\n",r);
	// 	}else
	// 	if (q==8){
	// 		set_print(v);
	// 	}else
	// 	{
	// 		break;
	// 	}
	// }
	// v=set_delete(v);
	struct set*s=set_new(16);
	ic(set_insert(s,3))
	ic(set_find(s,3))
	ic(set_find(s,4))
	ic(set_size(s))
	ic(set_insert(s,4))
	ic(set_find(s,3))
	ic(set_find(s,4))
	ic(set_size(s))
	ic(set_erase(s,3))
	ic(set_find(s,3))
	ic(set_find(s,4))
	ic(set_size(s))
	ic(set_delete(s))
}
#endif
