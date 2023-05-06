#include <bits/stdc++.h>
using namespace std;

    static void *coarg;

    void *coto(jmp_buf here, jmp_buf there, void *arg) {
	coarg = arg;
        if (setjmp(here)) return(coarg);
	longjmp(there, 1);
    }

    #define STACKDIR - // set to + for upwards and - for downwards
    #define STACKSIZE (1<<12)

    static char *tos; // top of stack

    void *cogo(jmp_buf here, void (*fun)(void*), void *arg) {
        if (tos == NULL) tos = (char*)&arg;
        tos += STACKDIR STACKSIZE;
        char n[STACKDIR (tos - (char*)&arg)];
        printf("%p\n", n);
        coarg = n; // ensure optimizer keeps n
        if (setjmp(here)) return(coarg);
	fun(arg);
	abort();
    }


    #define MAXTHREAD 4

    static jmp_buf thread_[MAXTHREAD];
    static int count_ = 0;

    static void comain(void *arg) {
	int *p = (int*)arg, i = *p;
	for (;;) {
		printf("coroutine %d at %p arg %p\n", i, (void*)&i, arg);
		int n = arc4random() % count_;
		printf("jumping to %d\n", n);
		arg = coto(thread_[i], thread_[n], (char*)arg + 1);
	}
    }

    int main(void) {
	while (++count_ < MAXTHREAD) {
		printf("spawning %d\n", count_);
		cogo(thread_[0], comain, &count_);
	}
	return 0;
    }