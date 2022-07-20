#include <bits/stdc++.h>
using namespace std;

uint64_t f(uint64_t x) {
	return x & (x + 1);
}

uint64_t g(uint64_t x) {
	return x | (x + 1);
}

int fen[128][128][128];

int prefix(uint64_t x, uint64_t y, uint64_t z) {
  int s = 0;
  for (uint64_t lx = x; lx < 128; lx = f(lx) - 1) {
    for (uint64_t ly = y; ly < 128; ly = f(ly) - 1) {
      for (uint64_t lz = z; lz < 128; lz = f(lz) - 1) {
        s += fen[lx][ly][lz];
      }
    }
  }
  return s;
}

void inc(uint64_t x, uint64_t y, uint64_t z, int v) {
  for (uint64_t lx = x; lx < 128; lx = g(lx)) {
    for (uint64_t ly = y; ly < 128; ly = g(ly)) {
      for (uint64_t lz = z; lz < 128; lz = g(lz)) {
        fen[lx][ly][lz] += v;
      }
    }
  }
}

int main() {
  uint64_t n;
  cin >> n;
  while (1) {
    uint64_t q;
    cin >> q;
    if (q == 1) {
      uint64_t x, y, z;
      cin >> x >> y >> z;
      int k;
      cin >> k;
      inc(x, y, z, k);
    }
    if (q == 2) {
      uint64_t x1, y1, z1, x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      cout << (prefix(x2 + 0, y2 + 0, z2 + 0) -
               prefix(x1 - 1, y2 + 0, z2 + 0) - prefix(x2 + 0, y1 - 1, z2 + 0) +
               prefix(x1 - 1, y1 - 1, z2 + 0) - prefix(x2 + 0, y2 + 0, z1 - 1) +
               prefix(x1 - 1, y2 + 0, z1 - 1) + prefix(x2 + 0, y1 - 1, z1 - 1) -
               prefix(x1 - 1, y1 - 1, z1 - 1))
           << '\n';
    }
    if (q == 3) {
      break;
    }
  }
}
