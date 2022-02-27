#ifndef DESKTOP_BINARYSEARCH_H
#define DESKTOP_BINARYSEARCH_H
template <typename T>
void Swap(T *a, T *b) {
  T c = *a;
  *a = *b;
  *b = c;
}
template <typename T>
int Partition(T *list, int l, int r) {
  int pivot_idx = (l + r) / 2;
  T pivot_value = list[pivot_idx];
  int i = l, j = r;
  while (i < j) {
    while (i < r && list[i] < pivot_value) {
      ++i;
    }
    while (l < j && !(j < i) && pivot_value < list[j]) {
      --j;
    }
    if (i < j) {
      Swap(list + i, list + j);
      ++i;
      --j;
    }
  }
  if (pivot_value < list[j]){
    j--;
  }
  return j;
}
template <typename T>
void QuickSort(T *list, int l, int r) {
  if (l < r) {
    int pivot_idx = Partition(list, l, r);
    if (pivot_idx < r){
      QuickSort(list, l, pivot_idx);
    }
    if (l < pivot_idx + 1){
      QuickSort(list, pivot_idx + 1, r);
    }
  }
}
template <typename T>
void Sort(T *begin, T *end) {
  int n = end - begin;
  QuickSort(begin, 0, n - 1);
}

#endif  // DESKTOP_BINARYSEARCH_H
