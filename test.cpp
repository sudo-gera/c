#include <cassert>
#include <iomanip>
#include <iostream>
// auto ppp=perf();

struct Point {
  int64_t x;
  int64_t y;
};

bool IsLess(Point q, Point w) {
  if (q.x != w.x) {
    return q.x < w.x;
  }
  return q.y < w.y;
}

bool IsEq(Point q, Point w) {
  return !IsLess(q, w) && !IsLess(w, q);
}

int64_t VecProdDot(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

int64_t *pppp;

Point *aaaa;

bool AnLess(int64_t b, int64_t c) {
  return (VecProdDot(aaaa[pppp[0]], aaaa[b], aaaa[c]) >= 0);
}

template <typename T>
void PushHeapA(T *begin, T *end) {
  int i = end - begin;
  while (1 < i && AnLess(begin[i / 2 - 1], begin[i - 1])) {
    T t = begin[i - 1];
    begin[i - 1] = begin[i / 2 - 1];
    begin[i / 2 - 1] = t;
    i /= 2;
  }
}
template <typename T>
void PopHeapA(T *begin, T *end) {
  int i = 0, n = end - begin;
  if (1 < n) {
    T t = *(end - 1);
    *(end - 1) = *begin;
    *begin = t;
    --n;
    int left, right, c = 1;
    while (i < c) {
      if (0 < c) {
        i = c;
      } else {
        c = i;
      }
      left = 2 * i;
      right = 2 * i + 1;
      if (left - 1 < n && AnLess(begin[i - 1], begin[left - 1])) {
        c = left;
      }
      if (right - 1 < n && AnLess(begin[c - 1], begin[right - 1])) {
        c = right;
      }
      if (i < c) {
        T t = begin[i - 1];
        begin[i - 1] = begin[c - 1];
        begin[c - 1] = t;
      }
    }
  }
}
template <typename T>
void HeapsortA(T *begin, T *end) {
  for (int64_t i = 0; i != end - begin; ++i) {
    PushHeapA(begin, begin + i + 1);
  }
  for (int64_t i = end - begin; i != 0; --i) {
    PopHeapA(begin, begin + i);
  }
}

int64_t Grahamscan(Point *a, int64_t n, int64_t *s) {
  auto *p = new int64_t[n];
  for (int64_t w = 0; w < n; ++w) {
    p[w] = w;
  }
  for (int64_t i = 1; i < n; ++i) {
    if (a[p[i]].x < a[p[0]].x) {
      std::swap(p[i], p[0]);
    }
  }
  pppp = p;
  aaaa = a;
  HeapsortA(p, p + n);

  s[0] = p[0];
  s[1] = p[1];
  int64_t ls = 2;
  for (int64_t i = 2; i < n; ++i) {
    while (VecProdDot(a[s[ls - 2]], a[s[ls - 1]], a[p[i]]) < 0) {
      ls--;
    }
    s[ls++] = p[i];
  }
  delete[] p;
  return ls;
}

int64_t VecProd(Point q, Point e) {
  return q.x * e.y - q.y * e.x;
}

Point Diff(Point xx, Point yy) {
  int64_t x = yy.x - xx.x;
  int64_t y = yy.y - xx.y;
  return Point{x, y};
}

double Area(Point *arr, int64_t n) {
  int64_t res = 0;
  for (int64_t w = 2; w < n; ++w) {
    res += VecProd(Diff(arr[0], arr[w - 1]), Diff(arr[w - 1], arr[w]));
  }
  return abs(res) / 2.;
}

Point *Unique(Point *first, Point *last) {
  if (first == last) {
    return last;
  }

  Point *result = first;
  while (++first != last) {
    if (!IsEq(*result, *first) && ++result != first) {
      *result = *first;
    }
  }
  return ++result;
}

void Rotate(Point *first, Point *r_to, Point *last) {
  if (first == r_to) {
    return;
  }
  if (r_to == last) {
    return;
  }

  Point *read = r_to;
  Point *write = first;
  Point *next_read = first;

  while (read != last) {
    if (write == next_read) {
      next_read = read;
    }
    std::swap(*(write++), *(read++));
  }

  Rotate(write, next_read, last);
}

template <typename T>
void PushHeap(T *begin, T *end) {
  int i = end - begin;
  while (1 < i && IsLess(begin[i / 2 - 1], begin[i - 1])) {
    T t = begin[i - 1];
    begin[i - 1] = begin[i / 2 - 1];
    begin[i / 2 - 1] = t;
    i /= 2;
  }
}
template <typename T>
void PopHeap(T *begin, T *end) {
  int i = 0, n = end - begin;
  if (1 < n) {
    T t = *(end - 1);
    *(end - 1) = *begin;
    *begin = t;
    --n;
    int left, right, c = 1;
    while (i < c) {
      if (0 < c) {
        i = c;
      } else {
        c = i;
      }
      left = 2 * i;
      right = 2 * i + 1;
      if (left - 1 < n && IsLess(begin[i - 1], begin[left - 1])) {
        c = left;
      }
      if (right - 1 < n && IsLess(begin[c - 1], begin[right - 1])) {
        c = right;
      }
      if (i < c) {
        T t = begin[i - 1];
        begin[i - 1] = begin[c - 1];
        begin[c - 1] = t;
      }
    }
  }
}
template <typename T>
void Heapsort(T *begin, T *end) {
  for (int64_t i = 0; i != end - begin; ++i) {
    PushHeap(begin, begin + i + 1);
  }
  for (int64_t i = end - begin; i != 0; --i) {
    PopHeap(begin, begin + i);
  }
}

Point *Run(Point *a, int64_t n) {
  Heapsort(a, a + n);
  n = Unique(a, a + n) - a;
  auto *aa = new int64_t[n];
  int64_t laa = Grahamscan(a, n, aa);
  auto *s = new Point[n];
  int64_t ls = 0;
  for (int64_t w = 0; w < laa; ++w) {
    s[ls++] = a[aa[w]];
  }
  delete[] aa;
  delete[] a;
  a = s;
  n = ls;
  for (int64_t w = 0; w < 3; ++w) {
    auto *s = new Point[n];
    int64_t ls = 0;
    for (int64_t e = 0; e < n; e++) {
      if (ls < 2 || VecProd(Diff(s[ls - 1], a[e]), Diff(s[ls - 1], s[ls - 2]))) {
        s[ls++] = a[e];
      } else {
        s[ls - 1] = a[e];
      }
    }
    n = ls;
    delete[] a;
    a = s;
    Rotate(a, a + 1, a + n);
  }
  Rotate(a, a + n - 3, a + n);
  double d = Area(a, n);
  std::cout << n << std::endl;
  int64_t perf_index = 0;
  for (int64_t w = 0; w < n; ++w) {
    bool mp = false;
    if (a[w].x < a[perf_index].x) {
      mp = true;
    }
    if (a[w].x == a[perf_index].x && a[w].y < a[perf_index].y) {
      mp = true;
    }
    if (mp) {
      perf_index = w;
    }
  }
  Rotate(a, a + perf_index, a + n);
  for (int64_t w = n; w > 0; --w) {
    std::cout << a[w % n].x << ' ' << a[w % n].y << std::endl;
  }
  std::cout << std::fixed << std::setprecision(1) << d << std::endl;
  return a;
}

int main() {
  int64_t n;
  std::cin >> n;
  auto *a = new Point[n];
  for (int64_t w = 0; w < n; ++w) {
    std::cin >> a[w].x;
    std::cin >> a[w].y;
  }
  Point *s = Run(a, n);
  delete[] s;
}
