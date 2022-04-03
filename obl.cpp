#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
struct Point {
  __int128_t x = -4702111234474983746;
  __int128_t y = -4702111234474983746;
};

// enable_print(Point,val.x,val.y);

Point *a;

__int128_t VecCrosProd(Point q, Point b, Point e) {
  __int128_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  return -v;
}

int Zip(__int128_t q) {
  if (q < 0) {
    return -1;
  }
  if (q > 0) {
    return 1;
  }
  return 0;
}

void Sure(bool f) {
  if (!f) {
    std::cout << "not sure" << std::endl;
    std::cerr << "not sure" << std::endl;
    // std::exit(0);
    assert(0);
    int *p = nullptr;
    while (p) {
      p = new int[1234567];
    }
    delete[] p;
  }
}
#define Sure assert

__int128_t AngleCrosProd(Point q, Point e, Point b) {
  __int128_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  return v;
}

int QsortAngleDist(Point *q, Point *e) {
  // ic(*q,*e)
  Point *b = a;
  __int128_t v = (q->x - b->x) * (e->y - b->y) - (q->y - b->y) * (e->x - b->x);
  if (v) {
    // ic(Zip(v))
    return Zip(v);
  }
  v = (q->x - b->x) * (q->x - b->x) + (q->y - b->y) * (q->y - b->y);
  v -= (e->x - b->x) * (e->x - b->x) + (e->y - b->y) * (e->y - b->y);
  // ic(Zip(v))
  return Zip(v);
}

int SortAngleDist(Point q, Point e) {
  Point &b = *a;
  __int128_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  if (v) {
    return v < 0;
  }
  v = (q.x - b.x) * (q.x - b.x) + (q.y - b.y) * (q.y - b.y);
  v -= (e.x - b.x) * (e.x - b.x) + (e.y - b.y) * (e.y - b.y);
  return v < 0;
}

int QsortLex(Point *q, Point *e) {
  if (q->x != e->x) {
    return Zip(q->x - e->x);
  }
  return Zip(q->y - e->y);
}

int SortLex(Point q, Point e) {
  if (q.x != e.x) {
    return q.x < e.x;
  }
  return q.y < e.y;
}

bool IsEq(Point q, Point w) {
  // is equal
  return q.x == w.x and q.y == w.y;
}

using QsortCmpT = int (*)(const void *, const void *);

int main() {
  __int128_t n = 0;
  int64_t tmp;
  std::cin >> tmp;
  n = tmp;
  a = new Point[n];
  for (__int128_t w = 0; w < n; w++) {
    std::cin >> tmp;
    a[w].x = tmp;
    std::cin >> tmp;
    a[w].y = tmp;
  }
  // ic(itervect(a,a+n))
  // qsort(a, n, sizeof(a[0]), reinterpret_cast<QsortCmpT>(QsortLex));
  std::sort(a, a + n, SortLex);
  // ic(itervect(a,a+n))
  n = std::unique(a, a + n, IsEq) - a;
  // ic(itervect(a,a+n))
  // qsort(a + 1, n - 1, sizeof(a[0]),
  // reinterpret_cast<QsortCmpT>(QsortAngleDist));
  std::sort(a + 1, a + n, SortAngleDist);
  // ic(itervect(a,a+n))
  auto s = new Point[n];
  __int128_t ls = 0;
  s[ls++] = a[0];
  s[ls++] = a[1];
  for (__int128_t w = 2; w < n; ++w) {
    while (ls > 1 and VecCrosProd(s[ls - 2], s[ls - 1], a[w]) >= 0) {
      ls--;
    }
    s[ls++] = a[w];
  }
  tmp = ls;
  std::cout << tmp << std::endl;
  for (__int128_t w = 0; w < ls; ++w) {
    tmp = s[w].x;
    std::cout << tmp << ' ';
    tmp = s[w].y;
    std::cout << tmp << '\n';
  }
  for (__int128_t w = 2; w < ls; ++w) {
    Sure(VecCrosProd(s[w - 2], s[w - 1], s[w - 0]) < 0);
  }
  if (ls > 2) {
    Sure(VecCrosProd(s[ls - 2], s[ls - 1], s[0]) < 0);
    Sure(VecCrosProd(s[ls - 1], s[0], s[1]) < 0);
  }
  for (__int128_t w = 0; w < n; ++w) {
    for (__int128_t e = 0; e < 9; ++e) {
      __int128_t z = rand() % ls;
      __int128_t x = (z + 1) % ls;
      // ic(w,z,x,a[w],s[z],s[x])
      Sure(VecCrosProd(s[z], s[x], a[w]) <= 0);
    }
  }
  __int128_t d = 0;
  for (__int128_t w = 2; w < ls; ++w) {
    d -= AngleCrosProd(s[w - 1], s[w], s[0]);
  }
  Sure(d > 0 or ls == 2);
  std::cout << std::fixed << std::setprecision(1) << d / 2. << std::endl;
  for (__int128_t w = 3; w < ls; ++w) {
    d += AngleCrosProd(s[w - 1], s[w], s[1]);
  }
  if (ls > 2) {
    d += AngleCrosProd(s[ls - 1], s[0], s[1]);
  }
  Sure(d == 0);
  delete[] s;
}
