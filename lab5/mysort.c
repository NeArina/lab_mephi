#include "mysort.h"

#include "detail.h"

void swap(detail **a, detail **b) {
  if (*a == *b) {  // *a is a pointer to our struct
    return;
  }
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

void nums(detail **arr, int i, int k, int max_index, int min_index) {
  if (max_index == i && min_index != k) {
    swap(&arr[k], &arr[max_index]);
    swap(&arr[i], &arr[min_index]);
  } else if (min_index == k && max_index != i) {
    swap(&arr[i], &arr[min_index]);
    swap(&arr[k], &arr[max_index]);
  } else if (min_index == k && max_index == i) {
    swap(&arr[k], &arr[i]);
  } else if (min_index != k && max_index != i) {
    swap(&arr[k], &arr[max_index]);
    swap(&arr[i], &arr[min_index]);
  }
}

void sort_insert(detail **arr, int size,
                 int (*cmp)(const void *, const void *)) {
  detail *max = 0;
  detail *min = 0;
  int max_index = 0;
  int min_index = 0;
  int k = size - 1;

  for (int i = 0; i <= k; i++) {
    max = arr[i];
    min = arr[i];
    max_index = i;
    min_index = i;
    for (int j = i + 1; j <= k; j++) {
      if (cmp(&arr[j], &max) > 0) {
        max = arr[j];
        max_index = j;
      }
      if (cmp(&arr[j], &min) < 0) {
        min = arr[j];
        min_index = j;
      }
    }
    nums(arr, i, k, max_index, min_index);
    k--;
  }
}
// void	 qsort(void *__base, size_t __nel, size_t __width,
// int (* _Nonnull __compar)(const void *, const void *));

void q_sort(detail **arr, int first, int last,
            int (*cmp)(const void *, const void *)) {
  int i = first, j = last;
  detail *x = arr[(first + last) / 2];

  do {
    while (cmp(&arr[i], &x) < 0) i++;
    while (cmp(&arr[j], &x) > 0) j--;

    if (i <= j) {
      if (cmp(&arr[i], &arr[j])) {
        void *tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
      i++;
      j--;
    }
  } while (i <= j);

  if (i < last) q_sort(arr, i, last, cmp);
  if (first < j) q_sort(arr, first, j, cmp);
}

void myqsort(detail **arr, int n, int (*cmp)(const void *, const void *)) {
  q_sort(arr, 0, n - 1, cmp);
}