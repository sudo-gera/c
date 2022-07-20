#include "stack.c"
static void print_double(void const *st) {
   printf("%lf", *(double *)st);
}

<<<<<<< HEAD
int main() {
    struct stack *st = stack_new(sizeof (double));
    for (int i = 0; i < 10; i++) {
        double tmp = i * i;
        stack_push(st, &tmp);
    }
    stack_print(st, print_double);
=======
static void print_str21(void const *st) {
	for (size_t w=0;w<21;++w){
		printf("%c",((char*)(st))[w]);
	}	
    // printf("%", *(double *)st);
}

int main() {
    struct stack *st = stack_new(21);
    for (int i = 0; i < 10; i++) {
    	char*a=(char*)calloc(21,1);
    	sprintf(a,"%i",i);
        stack_push(st, a);
        free(a);
    }
    stack_print(st, print_str21);
    for (int i = 0; i < 5; i++) {
    	char*a=(char*)calloc(21,1);
        stack_pop(st, a);
        printf("%s\n",a);
        free(a);
    }
    stack_print(st, print_str21);
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
    st = stack_delete(st);
}
