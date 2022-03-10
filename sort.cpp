#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <algorithm>
using namespace std;

void sort_bubble(int *a, int n) {
   bool sorted = false;
   while (!sorted) {
      sorted = true;
      for (int i = 0; i < n-1; i++) {
        if (a[i] > a[i+1]) {
           int tmp = a[i];
           a[i] = a[i+1];
           a[i+1] = tmp;
           sorted = false;
        }
      }
      n--;
    }
}

void sort_shaker(int *a, int n) {
   bool sorted = false;
   int l = 0, r = n;
   while (!sorted) {
      sorted = true;
      for (int i = l; i < r-1; i++) {
        if (a[i] > a[i+1]) {
           int tmp = a[i];
           a[i] = a[i+1];
           a[i+1] = tmp;
           sorted = false;
        }
      }
      r--;
      if (sorted) break;
      sorted = true;
      for (int i = r-2; i >= l; i--) {
        if (a[i] > a[i+1]) {
           int tmp = a[i];
           a[i] = a[i+1];
           a[i+1] = tmp;
           sorted = false;
        }
      }
      l++;
    }
}

void sort_bubble_traditional(int *a, int n) {
   bool sorted = false;
   for (int i = n-1; --n >- 0;) {
	   for (int j = 0; j < i; j++) {
	   	   if (a[j] > a[j+1]) {
	           int tmp = a[j];
	           a[j] = a[j+1];
	           a[j+1] = tmp;
	   	   }
	   }
   }
}

void sort_insertion(int *a, int n) {
  for (int i = n-1; i > 0; i--) {
    if (a[i-1] > a[i]) {
      int tmp = a[i-1]; a[i-1] = a[i]; a[i] = tmp;
    }
  }
  for (int i = 2; i < n; i++) {
    int j = i;
    int tmp = a[i];
    while (tmp < a[j-1]) {
       a[j] = a[j-1]; j--;
    }
    a[j] = tmp;
  } 
}

void sort_shell(int  *a, int n) {
   int h;
   for (h = 1; h <= n / 9; h = 3*h + 1) 
      ;
   for ( ; h > 0; h /= 3) {
      for (int i = h; i < n; i++) {
        int j = i; 
        int tmp = a[i];
        while (j >= h && tmp < a[j-h]) {
          a[j] = a[j-h];
          j -= h;
        }
        a[j] = tmp;
      }
   }
}


void sort_shell2(int  *a, int n) {
   static long long steps[] = {1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913, 1050113, 4197377, 16783361, 67121153, 268460033, 1073790977, 4295065601, 17180065793, 68719869953, 274878693377, 1099513200641, 4398049656833, 17592192335873, 70368756760577};
   int s;
   for (s = 0; steps[s] < n; s++)
       ;
   for (; --s >= 0; ) {
      int h = steps[s];
      for (int i = h; i < n; i++) {
        int j = i; 
        int tmp = a[i];
        while (j >= h && tmp < a[j-h]) {
          a[j] = a[j-h];
          j -= h;
        }
        a[j] = tmp;
      }
   }
}

void sort_shell3(int  *a, int n) {
    int h = n/2;
    for ( ; h > 0; h /= 2) {
      for (int i = h; i < n; i++) {
        int j = i; 
        int tmp = a[i];
        while (j >= h && tmp < a[j-h]) {
          a[j] = a[j-h];
          j -= h;
        }
        a[j] = tmp;
      }
   }
}

void merge(int *a, int low, int mid, int high, int *aux) {
   int i,j;
   for (i = mid+1; i > low; i--) aux[i-1] = a[i-1];
   for (j = mid; j < high; j++) aux[high+mid-j]=a[j+1];
   for (int k = low; k <= high; k++) {
      if (aux[j] < aux[i])
         a[k] = aux[j--];
      else
         a[k] = aux[i++];
   }
}

void mergeSort(int a[], int low, int high, int *aux) {
   const int THRESHOLD = 50;
   if (high - low < THRESHOLD) {
      sort_insertion(a+low, high-low+1);
   } else {
      int mid = (low + high) / 2;
      mergeSort(a, low, mid, aux);
      mergeSort(a, mid+1, high, aux);
      merge(a, low, mid ,high, aux);
  }
}

void sort_merge(int *a, int n) {
    int *aux = new int[n];
    mergeSort(a,0,n-1, aux);
    delete [] aux;
}

void quickSortBase(int *a, int l, int r) {
    int i = l, j = r;
    int pp[3] = { a[l], a[r], a[(l+r)>>1]};
    if (pp[0] < pp[1]) swap(pp[0],pp[1]);
    if (pp[1] < pp[2]) swap(pp[1],pp[2]);
    if (pp[0] < pp[1]) swap(pp[0],pp[1]);
    int p = pp[1];
    while (i <= j) {
        while (p > a[i])
           i++;
        while (a[j] > p)
           j--;
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }
    if (l < j)
       quickSortBase(a, l, j);
    if (i < r)
       quickSortBase(a, i, r);
}

void sort_quick_recursive(int *a, int n) {
   quickSortBase(a,0,n-1);
}

static void heapify(int *a, int i, int n)
{
    int curr = a[i];
    int index = i;
    for (;;) {
        int left = index + index + 1;
        int right = left + 1;
        if ( left < n && a[left] > curr)
            index = left;
        if ( right < n && a[right] > a[index])
            index = right;
        if (index == i ) break;
        a[i] = a[index];
        a[index] = curr;
        i = index;
    }
}

void sort_heap(int *a, int n) {
    for(int i = n/2-1; i >= 0; i--) {
        heapify(a, i, n);
    }
    while( n > 1 ) {
        n--;
        int tmp = a[0];
        a[0] = a[n];
        a[n] = tmp;
        heapify(a, 0, n);
    }
}

void sort_exchange(int *a, int n) {
   for (int i = 0; i < n-1; i++) {
      int imin = i;
      for (int j = i+1; j < n; j++) {
         if (a[j] < a[imin]) imin = j;
      }
      int tmp = a[imin];
      a[imin] = a[i];
      a[i] = tmp;
   }
}

void sort_vector(int *a, int n) {
   sort(a+0,a+n);
}

int compare_int(const void *a, const void *b) {
   return *(const int *)a - *(const int *)b;
}

void sort_qsort(int *a, int n) {
   qsort(a, n, sizeof(int), compare_int);
}

void radixsort(int32_t*_A,int32_t n){
   uint32_t*A=reinterpret_cast<uint32_t*>(_A);
   for (size_t w=0;w<n;++w){
      A[w]^=1ULL<<31;
   }
   auto C=reinterpret_cast<uint32_t*>(malloc(sizeof(uint32_t)*65536));
   auto B=reinterpret_cast<uint32_t*>(malloc(sizeof(uint32_t)*n));
   for (size_t w=0;w<2;++w){
      memset(C,0,65536*sizeof(C[0]));
      for(size_t i=0;i<n;++i){
         ++C[ reinterpret_cast<uint16_t*>(A+i)[w] ];
      }
      for (size_t j=1;j<65536;++j){
         C[j] += C[j - 1];
      }
      --A;
      for (size_t i=n;i>0;--i){
         B[ --C[ reinterpret_cast<uint16_t*>(A+i)[w] ] ] = A[i];
      }
      ++A;
      auto t=A;
      A=B;
      B=t;
   }
   free(C);
   free(B);
   for (size_t w=0;w<n;++w){
      A[w]^=1LL<<31;
   }
}

#include "/Users/gera/c/heap.h"

typedef void(*sort_func)(int *a, int n);

struct sort_s {
   sort_func func;
   string    name;
} funcs [] = {
   // {sort_bubble, "bubble_simple"},
   // {sort_bubble_traditional, "bubble_trad"},
   // {sort_shaker, "shaker"},
   // {sort_insertion, "insertion"},
   // {sort_exchange, "exchange"},
   // {sort_shell,  "shell"},
   // {sort_shell2,  "shell2"},
   // {sort_shell3,  "shell3"},
   // {sort_merge,  "merge"},
   {sort_heap,   "heap"},
   {sort_quick_recursive, "quick recursive"},
   {sort_vector, "vector"},
   {sort_qsort,  "qsort"},
   {radixsort,  "radixsort"},
   {hs,  "hs"},
};
   
int main(int argc, char **argv) {
    string kind = "random";
    if (argc > 1 && argv[1] == string("random")) { 
        kind = "random";
        argc--; argv++;
    }
    if (argc > 1 && argv[1] == string("ascend")) {
        kind = "ascend";
        argc--; argv++;
    }
    if (argc > 1 && argv[1] == string("descend")) {
        kind = "descend";
        argc--; argv++;
    }
    int start_alg = 0;
    if (argc > 1 && argv[1] == string("fastest")) {
       argc--; argv++;
       start_alg = 5;
    }
    int n = 100000;
    if (argc > 1) {
        n = atoi(argv[1]);
    } 
    if (n>1000){
       start_alg = 5;
    }
    int *copya = new int[n];
    if (kind == "random") {
       srand(time(NULL));
       for (int i = 0; i < n; i++) {
          copya[i] = rand();
       }
    } else if (kind == "ascend") {
       for (int i = 0; i < n; i++) {
           copya[i] = i * 2;
       }
    } else if (kind == "descend") {
       for (int i = 0; i < n; i++) {
           copya[i] = n*2 - i*2;
       }
    }
    int *a = new int[n];
    printf("Sorting %d %s elements\n", n, kind.c_str());
    for (int alg = start_alg; alg < sizeof funcs/sizeof funcs[0]; alg++) {
       memcpy(a, copya, n * sizeof a[0]);
       printf("%30s: ", funcs[alg].name.c_str()); fflush(stdout);
       clock_t start = clock();
       funcs[alg].func(a, n);
       clock_t end = clock();
       printf("%.3f seconds\n", (end - start) / (double)CLOCKS_PER_SEC);
       for (int i = 0; i < n-1; i++) {
          if (a[i] > a[i+1]) {
             printf("sort failed: a[%d]=%d a[%d]=%d\n", i, a[i], i+1, a[i+1]);
             break;
          }
       }
    }
    delete [] a;
}
  
