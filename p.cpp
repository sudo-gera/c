#include <iostream>
#include <cassert>

int64_t Getint() {
  int64_t ll;
  std::cin >> ll;
  return ll;
}

struct Item {
  int64_t Sum = 0;
  int64_t Add = 0;
};

Item* a = nullptr;
#define ll 16384

Item& Get(int64_t b, int64_t e) {
  return a[(ll + b) / (e - b)];
}

void Add(int64_t ub, int64_t ue, int64_t v, int64_t b = 0, int64_t e = ll) {
  assert(b <= ub && ub != ue && ue <= e);
  Get(b, e).Sum += v * (ue - ub);
  int64_t c = (b + e) / 2;
  if (b == ub && ue == e) {
    Get(b, e).Add += v;
  } else if (b <= ub && ue <= c) {
    Add(ub, ue, v, b, c);
  } else if (c <= ub && ue <= e) {
    Add(ub, ue, v, c, e);
  } else {
    Add(ub, c, v, b, c);
    Add(c, ue, v, c, e);
  }
}

int64_t Sum(int64_t ub, int64_t ue, int64_t b = 0, int64_t e = ll) {
  int64_t r = -1;
  assert(b <= ub && ub != ue && ue <= e);
  int64_t c = (b + e) / 2;
  if (b == ub && ue == e) {
    r = Get(b, e).Add * (ue - ub) + Get(b, e).Sum;
  } else if (b <= ub && ue <= c) {
    r = Get(b, e).Add * (ue - ub) + Sum(ub, ue, b, c);
  } else if (c <= ub && ue <= e) {
    r = Get(b, e).Add * (ue - ub) + Sum(ub, ue, c, e);
  } else {
    r = Get(b, e).Add * (ue - ub) + Sum(ub, c, b, c) + Sum(c, ue, c, e);
  }
  return r;
}

int main() {
  int64_t n = Getint(), m = Getint();
  a = new Item[ll * 2]();
  for (int64_t w = 0; w < m; ++w) {
    int64_t q = Getint();
    int64_t l = Getint();
    int64_t r = Getint();
    if (q == 1) {
      Add(l, r, Getint());
    } else {
      std::cout << Sum(l, r) << std::endl;
    }
  }
}
