#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::cin, std::cout, std::vector, std::string, std::sort;
using std::set, std::unordered_set, std::map, std::unordered_map;

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

///////////////////////////////////////////////////end of lib


using namespace std::literals;

template<typename T>
auto replace(T self,T old,T ne,long maxcount=-1){
	T res;
	for (int64_t w=0;w<self.size();){
		if (maxcount and self.rfind(old,w)==w){
			res+=ne;
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res+=(self)[w];
			++w;
		}
	}
	return res;
}

std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	pclose(pipe);
	return s;
}

std::string python(std::string q){
	q=replace(q,"\\"s,"\\\\"s);
	q=replace(q,"\""s,"\\\""s);
	q=replace(q,"`"s,"\\`"s);
	q=replace(q,"$"s,"\\$"s);
  q="python3 -c \""+q+"\"";
	return popen(q);
}


int main(){
    long n=getint(),m=getint();
    cout<<python(
        "n,m="+std::to_string(n)+","+std::to_string(m)+"\n"
        "a=[0]*(n+m+n+m)\n"
        "a[0]=1\n"
        "q=0\n"
        "while q<=n:\n"
        "    for w in range(1,m+1):\n"
        "        a[q+w]+=a[q]\n"
        "    q+=1\n"
        "print(a[n])\n"
    );
    // vector<long> a(n+m+2);
    // a[0]=1;
    // for (long q=0;q<n+1;++q){
    //     for (long w=1;w<m+1;++w){
    //         a[w+q]+=a[q];
    //     }
    // }
    // print(a[n]);
}