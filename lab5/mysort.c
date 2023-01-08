#include "mysort.h"

#include <stdio.h>

#include "detail.h"

void swap(detail **a, detail **b) {
  if (*a == *b) {  // *a is a pointer to our struct
    return;
  }
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

void nums(detail **arr, int i, int num, int max_index, int min_index) {
  if (max_index == i && min_index != num) {
    swap(&arr[num], &arr[max_index]);
    swap(&arr[i], &arr[min_index]);
  } else if (min_index == num && max_index != i) {
    swap(&arr[i], &arr[min_index]);
    swap(&arr[num], &arr[max_index]);
  } else if (min_index == num && max_index == i) {
    swap(&arr[num], &arr[i]);
  } else if (min_index != num && max_index != i) {
    swap(&arr[num], &arr[max_index]);
    swap(&arr[i], &arr[min_index]);
  }
}

void sort_insert(detail **arr, int size,
                 int (*cmp)(const void *, const void *)) {
  detail *maximum = 0;
  detail *minimum = 0;
  int maximum_ind = 0;
  int minimum_ind = 0;
  int num = size - 1;

  for (int i = 0; i <= num; i++) {
    maximum = arr[i];
    minimum = arr[i];
    maximum_ind = i;
    minimum_ind = i;
    for (int j = i + 1; j <= num; j++) {
      if (cmp(&arr[j], &maximum) > 0) {
        maximum = arr[j];
        maximum_ind = j;
      }
      if (cmp(&arr[j], &minimum) < 0) {
        minimum = arr[j];
        minimum_ind = j;
      }
    }
    nums(arr, i, num, maximum_ind, minimum_ind);
    num--;
  }
}
// void	 qsort(void *__base, size_t __nel, size_t __width,
// int (* _Nonnull __compar)(const void *, const void *));

void q_sort(detail **arr, int first, int last,
            int (*cmp)(const void *, const void *)) {
  // printf("abc\n");
  int f = first;
  int l = last;
  detail *x = arr[(first + last) / 2];

  do {
    while (cmp(&arr[f], &x) < 0) {
      f++;
    }
    while (cmp(&arr[l], &x) > 0) {
      l--;
    }
    if (f <= l) {
      if (cmp(&arr[f], &arr[l]) > 0) {
        void *tmp = arr[f];
        arr[f] = arr[l];
        arr[l] = tmp;
      }
      f++;
      l--;
    }
  } while (f <= l);

  if (f < last) {
    q_sort(arr, f, last, cmp);
  }
  if (first < l) {
    q_sort(arr, first, l, cmp);
  }
}

void myqsort(detail **arr, int n, int (*cmp)(const void *, const void *)) {
  q_sort(arr, 0, n - 1, cmp);
}