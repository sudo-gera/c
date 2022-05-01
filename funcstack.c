#define stack_load																\
	static char *__stack_start = 0;												\
	static long __stack_diff = 0;												\
	char *__stack_curr = (char *)&__stack_curr;									\
	if (!__stack_start) {														\
		__stack_start = (char *)&__stack_curr;									\
	} else if (!__stack_diff and __stack_start != (char *)&__stack_curr) {		\
		__stack_diff = __stack_start - (char *)&__stack_curr;					\
	}																			\
	long stack_len =															\
			__stack_diff ? (__stack_start - __stack_curr) / __stack_diff + 1 : 1;

#define stack_get(v, n)															\
	(*(decltype(v) *)((char *)&(v) +											\
		((n) % stack_len + stack_len) % stack_len * __stack_diff))

#define decltype typeof

