#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

Point *a;

int cmp2(Point q, Point b, Point e) {
  int64_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  return -v;
}

int cmp3(Point *_q, Point *_e) {
  Point &b = *a;
  Point &q = *_q;
  Point &e = *_e;
  int64_t v = (q.x - b.x) * (e.y - b.y) - (q.y - b.y) * (e.x - b.x);
  if (v) {
    return v;
  }
  return (q.x - b.x) * (q.x - b.x) + (q.y - b.y) * (q.y - b.y) -
         (e.x - b.x) * (e.x - b.x) - (e.y - b.y) * (e.y - b.y);
}

int cmp1(Point *q, Point *e) {
  if (q->x != e->x) {
    return q->x - e->x;
  }
  return q->y - e->y;
}

bool cmp4(Point q, Point w) {
	return q.x == w.x and q.y == w.y;
}

typedef int (*qsort_cmp_t)(const void *, const void *);

int main() {
  int64_t n = 0;
  std::cin >> n;
  a = new Point[n];
  for (int64_t w = 0; w < n; w++) {
    std::cin >> a[w].x;
    std::cin >> a[w].y;
  }
  qsort(a, n, sizeof(a[0]), (qsort_cmp_t)cmp1);
  n = std::unique(a, a + n, cmp4) - a;
  qsort(a + 1, n - 1, sizeof(a[0]), (qsort_cmp_t)cmp3);
  auto s = new Point[n];
  int64_t ls = 0;
  s[ls++] = a[0];
  s[ls++] = a[1];
  for (int64_t w = 2; w < n; ++w) {
    while (ls > 1 and cmp2(s[ls - 2], s[ls - 1], a[w]) >= 0) {
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
    d -= cmp3(s + w - 1, s + w);
  }
  std::cout << std::fixed << std::setprecision(1) << d / 2. << std::endl;
  delete[] s;
}
