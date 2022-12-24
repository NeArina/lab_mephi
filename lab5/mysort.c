#include "mysort.h"

void sort1(void *base, size_t nitems,
           int (*compar)(const void *, const void *)) {}

void swap(void **a, void **b) {
  if (*a == *b) { // *a is a pointer to our struct
    return;
  }
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

void nums(void *arr, int i, int k, int max_index, int min_index) {
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

void sorted_array(int *arr, int size) {

  int max = 0;
  int min = 0;
  int max_index = 0;
  int min_index = 0;
  int k = size - 1;

  for (int i = 0; i <= k; i++) {
    max = arr[i];
    min = arr[i];
    max_index = i;
    min_index = i;
    for (int j = i + 1; j <= k; j++) {
      if (arr[j] > max) {
        max = arr[j];
        max_index = j;
      }
      if (arr[j] < min) {
        min = arr[j];
        min_index = j;
      }
    }
    nums(arr, i, k, max_index, min_index);
    k--;
  }
}