

#include <iostream>

long Getint() {
  long ll;
  std::cin >> ll;
  return ll;
}

struct Item {
  long Sum = 0;
  long Add = 0;
};

Item* a = 0;
#define ll 16384

Item& get(long b, long e) {
  return a[(ll + b) / (e - b)];
}

void Add(long ub, long ue, long v, long b = 0, long e = ll) {
  assert(b <= ub and ub != ue and ue <= e);
  get(b, e).Sum += v * (ue - ub);
  long c = (b + e) / 2;
  if (b == ub and ue == e) {
    get(b, e).Add += v;
  } else if (b <= ub and ue <= c) {
    Add(ub, ue, v, b, c);
  } else if (c <= ub and ue <= e) {
    Add(ub, ue, v, c, e);
  } else {
    Add(ub, c, v, b, c);
    Add(c, ue, v, c, e);
  }
}

long Sum(long ub, long ue, long b = 0, long e = ll) {
  long r = -1;
  assert(b <= ub and ub != ue and ue <= e);
  long c = (b + e) / 2;
  if (b == ub and ue == e) {
    r = get(b, e).Add * (ue - ub) + get(b, e).Sum;
  } else if (b <= ub and ue <= c) {
    r = get(b, e).Add * (ue - ub) + Sum(ub, ue, b, c);
  } else if (c <= ub and ue <= e) {
    r = get(b, e).Add * (ue - ub) + Sum(ub, ue, c, e);
  } else {
    r = get(b, e).Add * (ue - ub) + Sum(ub, c, b, c) + Sum(c, ue, c, e);
  }
  return r;
}

int main() {
  long n = Getint(), m = Getint();
  a = new Item[ll * 2]();
  for (long w = 0; w < m; ++w) {
    long q = Getint();
    long l = Getint();
    long r = Getint();
    if (q == 1) {
      Add(l, r, Getint());
    } else {
      std::cout << Sum(l, r) << std::endl;
    }
  }
}
