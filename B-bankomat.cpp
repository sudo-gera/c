#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::cin, std::cout, std::vector, std::string, std::sort, std::pair;
using std::set, std::unordered_set, std::map, std::unordered_map;

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

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

///////////////////////////////////////////////////end of lib

struct find{
  unordered_map<llu,llu> cache;
  vector<llu> a;

  long find1(llu s){
      if (s==0){
          return 0;
      }
      if (cache.count(s)){
          return cache[s];
      }
      llu r=1LL<<50;
      for (auto w:a){
          if (s>=w){
              auto t=find1(s-w);
              if (t<r){
                  r=t;
              }
          }
      }
      r+=1;
      cache[s]=r;
      return r;
  }

  long find2(llu s, llu c){
      if (s*c==0){
          return !(s+c);
      }
      for (auto w:a){
          if (s>=w){
              if (find1(s-w)==c-1 and find2(s-w,c-1)){
                  write(w);
                  return 1;
              }
          }
      }
      return 0;
  }
};

int main(){
    llu n=getint();
    find f;
    for (llu w=0;w<n;++w){
        f.a.push_back(getint());
    }
    llu s=getint();
    auto z=f.find1(s);
    if (z<1LL<<40){
        print(z);
        f.find2(s,z);
        putchar(10);
    }else{
        print(-1);
    }
}