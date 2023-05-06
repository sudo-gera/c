    #define MAXTHREAD 10000

    static jmp_buf thread[MAXTHREAD];
    static int count_ = 0;

    static void comain(void *arg) {
	int *p = arg, i = *p;
	for (;;) {
		printf("coroutine %d at %p arg %p\n", i, (void*)&i, arg);
		int n = arc4random() % count_;
		printf("jumping to %d\n", n);
		arg = coto(thread[i], thread[n], (char*)arg + 1);
	}
    }

    int main(void) {
	while (++count_ < MAXTHREAD) {
		printf("spawning %d\n", count_);
		cogo(thread[0], comain, &count_);
	}
	return 0;
    }