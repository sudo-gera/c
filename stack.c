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

#ifdef HOME
#define stack stack_home
#endif

struct stack{
	size_t elem_size;
	struct stack *next;
	void*elem;
	size_t size;
};

struct stack *stack_new(size_t elem_size){
	struct stack*a=(struct stack*)calloc(sizeof(struct stack),1);
	a->elem_size=elem_size;
	return a;
}

int stack_push(struct stack *st, const void *elem){
	if (!st or !elem){
		return 1;
	}
	struct stack*j=st->next;
	st->next=(struct stack*)calloc(sizeof(struct stack),1);
	if (!st->next){
		return 1;
	}
	st->next->next=j;
	st->next->elem_size=st->elem_size;
	st->next->size=st->size;
	st->size++;
	st->next->elem=malloc(st->elem_size);
	if (!st->next->elem){
		return 1;
	}
	memcpy(st->next->elem,elem,st->elem_size);
	return 0;
}

int stack_pop (struct stack *st, void *elem){
	if (!st or !elem){
		return 1;
	}
	if (!st->next){
		return 1;
	}
	memcpy(elem,st->next,st->elem_size);
	struct stack*j=st->next->next;
	if (st->next->elem){
		free(st->next->elem);
	}
	free(st->next);
	st->size--;
	st->next=j;
	return 0;
}

int stack_top (struct stack *st, void *elem){
	if (!st or !elem){
		return 1;
	}
	if (!st->next){
		return 1;
	}
	memcpy(elem,st->next,st->elem_size);
	return 0;
}

int stack_empty(struct stack const *st){
	return !st->next;
}

struct stack *stack_delete(struct stack *st){
	if (st){
		while (!st->next){
			struct stack*j=st->next->next;
			if (st->next->elem){
				free(st->next->elem);
			}
			free(st->next);
			st->next=j;
		}
		if (st->elem){
			free(st->elem);
		}
		free(st);
	}
	return NULL;
}

void stack_print(struct stack const *st, void (*pf)(void const *st)){
	void**a=(void**)malloc(sizeof(void*)*st->size);
	size_t la=0;
	struct stack*j=st->next;
	while (j){
		a[la++]=j->elem;
		j=j->next;
	}
	printf("[");
	int c=0;
	while (la){
		if (c){
			printf(", ");
		}else{
			c=1;
		}
		(*pf)(a[--la]);
	}
	printf("]\n");
}
