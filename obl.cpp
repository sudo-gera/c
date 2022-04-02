#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

Point *a;

int Cmp2(Point q, Point b, Point e) {
  int64_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  return -v;
}

int Cmp3(Point *q, Point *e) {
  Point *b = a;
  int64_t v = (q->x - b->x) * (e->y - b->y) - (q->y - b->y) * (e->x - b->x);
  if (v) {
    return v;
  }
  return (q->x - b->x) * (q->x - b->x) + (q->y - b->y) * (q->y - b->y) -
         (e->x - b->x) * (e->x - b->x) - (e->y - b->y) * (e->y - b->y);
}

int Cmp1(Point *q, Point *e) {
  if (q->x != e->x) {
    return q->x - e->x;
  }
  return q->y - e->y;
}

bool Cmp4(Point q, Point w) {
  // is equal
  return q.x == w.x and q.y == w.y;
}

using qsort_Cmp_t = int (*)(const void *, const void *);

int main() {
  int64_t n = 0;
  std::cin >> n;
  a = new Point[n];
  for (int64_t w = 0; w < n; w++) {
    std::cin >> a[w].x;
    std::cin >> a[w].y;
  }
  qsort(a, n, sizeof(a[0]), reinterpret_cast<qsort_Cmp_t>(Cmp1));
  n = std::unique(a, a + n, Cmp4) - a;
  qsort(a + 1, n - 1, sizeof(a[0]), reinterpret_cast<qsort_Cmp_t>(Cmp3));
  auto s = new Point[n];
  int64_t ls = 0;
  s[ls++] = a[0];
  s[ls++] = a[1];
  for (int64_t w = 2; w < n; ++w) {
    while (ls > 1 and Cmp2(s[ls - 2], s[ls - 1], a[w]) >= 0) {
      ls--;
    }
    s[ls++] = a[w];
  }
  delete[] a;
  std::cout << ls << std::endl;
  for (int64_t w = 0; w < ls; ++w) {
    std::cout << s[w].x << ' ' << s[w].y << '\n';
  }
  int64_t d = 0;
  a = s;
  for (int64_t w = 2; w < ls; ++w) {
    d -= Cmp3(s + w - 1, s + w);
  }
  std::cout << std::fixed << std::setprecision(1) << d / 2. << std::endl;
  delete[] s;
}
