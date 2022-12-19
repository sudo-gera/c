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

using dot=pair<long,long>;

int main(){
    llu k=getint();
    vector<dot> a(k);
    for (llu w=0;w<k;++w){
        a[w]={getint(),getint()};
    }
    sort(a.begin(),a.end());
    vector<tuple<dot,vector<llu>,llu>> s(k);
    for (llu w=0;w<k;++w){
        s[w]={
            a[w],
            {},
            1
        };
    }
    for (llu e=0;e<k;++e){
        long q=a[e].first,w=a[e].second;
        {
            dot o{q-1,w};
            auto bl=lower_bound(a.begin(),a.end(),o);
            if (bl!=upper_bound(a.begin(),a.end(),o)){
                get<1>(s[e]).push_back(bl-a.begin());
            }
        }
        {
            dot o{q,w-1};
            auto bl=lower_bound(a.begin(),a.end(),o);
            if (bl!=upper_bound(a.begin(),a.end(),o)){
                get<1>(s[e]).push_back(bl-a.begin());
            }
        }
        {
            dot o{q+1,w};
            auto bl=lower_bound(a.begin(),a.end(),o);
            if (bl!=upper_bound(a.begin(),a.end(),o)){
                get<1>(s[e]).push_back(bl-a.begin());
            }
        }
        {
            dot o{q,w+1};
            auto bl=lower_bound(a.begin(),a.end(),o);
            if (bl!=upper_bound(a.begin(),a.end(),o)){
                get<1>(s[e]).push_back(bl-a.begin());
            }
        }
    }
    unordered_set<llu> f;
    for (llu w=0;w<k;++w){
        f.insert(w);
    }
    llu c=1;
    while(not f.empty()){
        c*=2;
        c%=998'244'353;
        vector<llu> q;
        llu qg=0;
        q.push_back(*f.begin());
        while (q.size()!=qg){
            llu k=q[qg++];
            if (get<2>(s[k])){
                for (auto w : get<1>(s[k])){
                    q.push_back(w);
                }
                get<2>(s[k])=0;
                f.erase(k);
            }
        }
    }
    print(c);
}