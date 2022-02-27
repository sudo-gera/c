#ifndef DESKTOP_HEAP_H
#define DESKTOP_HEAP_H
template <typename T>
void PushHeap(T *begin, T *end) {
  int i = end - begin;
  while (1 < i && begin[i / 2 - 1] < begin[i - 1]) {
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
      if (left - 1 < n && begin[i - 1] < begin[left - 1]) {
        c = left;
      }
      if (right - 1 < n && begin[c - 1] < begin[right - 1]) {
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
#endif  // DESKTOP_HEAP_H
