#include "stack.c"
static void print_double(void const *st) {
   printf("%lf", *(double *)st);
}

int main() {
    struct stack *st = stack_new(sizeof (double));
    for (int i = 0; i < 10; i++) {
        double tmp = i * i;
        stack_push(st, &tmp);
    }
    stack_print(st, print_double);
    st = stack_delete(st);
}
