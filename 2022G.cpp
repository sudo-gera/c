#include <bits/stdc++.h>
using namespace std;

static inline int64_t getint() {
	int sign = 1;
	int c;
	size_t res = 0;
	while (c = getchar_unlocked(), isspace(c))
		;
	if (c == '-') {
		sign = -1;
	} else {
		res = c - '0';
	}
	while (c = getchar_unlocked(), isdigit(c)) {
		res *= 10;
		res += c - '0';
	}
	return (int64_t)(res)*sign;
}

static inline void putint(uint64_t out) {
	if (out > (1LLU << 63) - 1) {
		putchar_unlocked('-');
		out = 1 + ~out;
	}
	char data[44];
	char *dend = data;
	while (out) {
		*++dend = (unsigned)('0') + out % 10;
		out /= 10;
	}
	if (dend == data) {
		putchar_unlocked('0');
	}
	for (; dend != data; --dend) {
		putchar_unlocked(*dend);
	}
}

static inline void print(uint64_t out) {
	putint(out);
	putchar('\n');
}

static inline void write(uint64_t out) {
	putint(out);
	putchar(' ');
}

using llu=long long unsigned;

#define bisect(b, e, ...)														\
	({																			\
		int64_t __begin = b;													\
		int64_t __end = e;														\
		assert(__begin <= __end);												\
		while (__begin + 1 < __end) {											\
			int64_t __center = (__begin + __end) / 2;							\
			if (__VA_ARGS__) {													\
				__end = __center;												\
			} else {															\
				__begin = __center;												\
			}																	\
		}																		\
		int64_t __center = __begin;												\
		if (__begin != __end and (__VA_ARGS__)) {								\
			__end = __center;													\
		}																		\
		__end;																	\
	})

llu floor_root(llu q){
	llu r=0;
	llu p=1ULL<<62;
	llu u=0;
    while (p){
		u=r+p;
		if (q >= u) {
			q-=u;
			r+=p;
			r+=p;
        }
		r>>=1;
		p>>=2;
    }
	return r;
}

int main(){
    llu m=bisect(0,2'100'000'000,({
        cout<<"M "<<__center<<endl;
        string s;
        cin>>s;
        s.size()==2;
    }));
    llu e=bisect(0,2'100'000'000'000'000'000,({
        cout<<"E "<<__center<<endl;
        string s;
        cin>>s;
        s.size()==2;
    }));
    // llu m=8;
    // llu e=32;
    llu y=(floor_root(e+e-m*m)+m)/2;
    llu x=m-y;
    cout<<"! "<<x<<" "<<y<<endl;
}