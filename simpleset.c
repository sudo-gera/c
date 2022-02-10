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
	if (elem>=s->size){
		return 1;
	}
	s->data[elem/8]|=1U<<(elem%8);
	s->usize++;
	return 0;
}
// Добавить во множество s элемент elem. Если элемент существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
int set_erase(struct set *s, size_t elem){
	if (elem>=s->size){
		return 1;
	}
	s->data[elem/8]=~s->data[elem/8];
	s->data[elem/8]|=1U<<(elem%8);
	s->data[elem/8]=~s->data[elem/8];
	s->usize--;
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
	return s->usize==0;
}
// Предикат: вернуть единицу, если в множестве есть хотя бы один элемент и ноль в противном случае.
ssize_t set_findfirst(struct set const *s, size_t start){
	for (size_t w=start;w<s->size;++w){
		if (set_find(s,w)){
			return w;
		}
	}
	return -1;
}
// Вернуть наименьший из элементов множества, не меньших start. Если таких элементов нет (например, множество пустое), то вернуть -1.
size_t set_size(struct set const *s){
	return s->usize;
}
// Вернуть количество элементов множества.
void set_print(struct set const *s){
	printf("[");
	int c=0;
	for (size_t w=0;w<s->size;++w){
		if (set_find(s,w)){
			if (c){
				printf(", ");
			}else{
				c=1;
			}
			printf("%zu",w);
		}
	}
	printf("]\n");
}
// Вывести на стандартный вывод содержимое множества в формате по образцу: []\n или [1, 2, 3]\n.

#ifdef HOME
int main() {
    struct set *s = set_new(7);
    set_print(s);
    assert(set_insert(s, 1) == 0);
    set_print(s);
    assert(set_insert(s, 2) == 0);
    set_print(s);
    assert(set_insert(s, 100) != 0);
    set_print(s);
    assert(set_size(s) == 2);
    set_print(s);            
    assert(set_find(s,1) != 0);
    set_print(s);
    assert(set_find(s,100) == 0);
    set_print(s);
    assert(set_insert(s, 5) == 0);
    set_print(s);
    assert(set_erase(s,2) == 0);
    set_print(s);
    assert(set_findfirst(s, 2) == 5);
    set_print(s);
    assert(set_findfirst(s, 10) == -1);
    set_print(s);
    assert(set_delete(s) == NULL);
}
#endif
