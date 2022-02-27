#ifndef DESKTOP_BINARYSEARCH_H
#define DESKTOP_BINARYSEARCH_H
template <typename T>
void Sort(T *begin, T *end) {
  if (begin < end) {
    T *pivot_value = begin + (end - begin) / 2;
    T *i = begin, *j = end - 1;
    while (!(j < i)) {
      while (*i < *pivot_value) {
        ++i;
      }
      while (*pivot_value < *j) {
        --j;
      }
      if (!(j < i)) {
        T c = *i;
        *i = *j;
        *j = c;
        ++i;
        --j;
      }
    }
    Sort(begin, j + 1);
    Sort(i, end);
  }
}

#endif  // DESKTOP_BINARYSEARCH_H
