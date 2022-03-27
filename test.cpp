#include <assert.h>
#include <iomanip>
#include <iostream>
struct point {
  long x;
  long y;
};

bool is_less(point q, point w) {
  if (q.x != w.x) {
    return q.x < w.x;
  }
  return q.y < w.y;
}

bool is_eq(point q, point w) { return not is_less(q, w) and not is_less(w, q); }

auto rotate(point A, point B, point C) {
  return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}

auto grahamscan(point *A, long n, long *S) {
  auto P = new long[n];
  for (long w = 0; w < n; ++w) {
    P[w] = w;
  }
  for (auto i = 1; i < n; ++i) {
    if (A[P[i]].x < A[P[0]].x) {
      std::swap(P[i], P[0]);
    }
  }
  for (auto i = 2; i < n; i++) {
    auto j = i;
    while (j > 1 and (rotate(A[P[0]], A[P[j - 1]], A[P[j]]) < 0)) {
      std::swap(P[j], P[j - 1]);
      j -= 1;
    }
  }
  S[0] = P[0];
  S[1] = P[1];
  long ls = 2;
  for (auto i = 2; i < n; ++i) {
    while (rotate(A[S[ls - 2]], A[S[ls - 1]], A[P[i]]) < 0) {
      ls--;
    }
    S[ls++] = P[i];
  }
  delete[] P;
  return ls;
}

auto vd(point q, point e) { return q.x * e.y - q.y * e.x; }

auto vect(point _x, point _y) {
  auto x = _y.x - _x.x;
  auto y = _y.y - _x.y;
  return point{x, y};
}

auto area(point *vertices, long n) {
  long res = 0;
  for (long w = 2; w < n; ++w) {
    res += vd(vect(vertices[0], vertices[w - 1]),
              vect(vertices[w - 1], vertices[w]));
  }
  return abs(res) / 2.;
}

auto unique(point *first, point *last) {
  if (first == last)
    return last;

  auto result = first;
  while (++first != last) {
    if (!is_eq(*result, *first) && ++result != first) {
      *result = *first;
    }
  }
  return ++result;
}

void rotate(point *first, point *n_first, point *last) {
  if (first == n_first)
    return;
  if (n_first == last)
    return;

  auto read = n_first;
  auto write = first;
  auto next_read = first;

  while (read != last) {
    if (write == next_read) {
      next_read = read;
    }
    std::swap(*(write++), *(read++));
  }
}

template <typename T> void PushHeap(T *begin, T *end) {
  int i = end - begin;
  while (1 < i && is_less(begin[i / 2 - 1], begin[i - 1])) {
    T t = begin[i - 1];
    begin[i - 1] = begin[i / 2 - 1];
    begin[i / 2 - 1] = t;
    i /= 2;
  }
}
template <typename T> void PopHeap(T *begin, T *end) {
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
      if (left - 1 < n && is_less(begin[i - 1], begin[left - 1])) {
        c = left;
      }
      if (right - 1 < n && is_less(begin[c - 1], begin[right - 1])) {
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
template <typename T> void heapsort(T *begin, T *end) {
  for (T *w = begin; w != end; ++w) {
    PushHeap(begin, w + 1);
  }
  for (T *w = end; w != begin; --w) {
    PopHeap(begin, w);
  }
}

auto run(point *a, long n) {
  heapsort(a, a + n);
  n = unique(a, a + n) - a;
  auto aa = new long[n];
  auto laa = grahamscan(a, n, aa);
  auto s = new point[n];
  long ls = 0;
  for (auto w = 0; w < laa; ++w) {
    s[ls++] = a[aa[w]];
  }
  delete[] aa;
  delete[] a;
  a = s;
  n = ls;
  long nn = n;
  for (auto w = 0; w < nn; ++w) {
    auto s = new point[n];
    long ls = 0;
    for (auto e = 0; e < n; e++) {
      if (ls < 2 or vd(vect(s[ls - 1], a[e]), vect(s[ls - 1], s[ls - 2]))) {
        s[ls++] = a[e];
      } else {
        s[ls - 1] = a[e];
      }
    }
    n = ls;
    delete[] a;
    a = s;
    rotate(a, a + 1, a + n);
  }
  // std::sort(a,a+n,is_less);
  std::cout << n << std::endl;
  for (auto w = 0; w < n; ++w) {
    std::cout << a[w].x << ' ' << a[w].y << std::endl;
  }
  std::cout << std::fixed << std::setprecision(1) << area(a, n) << std::endl;
  return a;
}

int main() {
  long n;
  std::cin >> n;
  auto a = new point[n];
  for (auto w = 0; w < n; ++w) {
    std::cin >> a[w].x;
    std::cin >> a[w].y;
  }
  delete[] run(a, n);
}
