#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void print_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    printf("a[%d] = %d\n", i, arr[i]);
  }
}

int *handle_input(int *arr, int *size, int i, int v) { 
  if (i < *size) {
    // move +1 right
    if (arr[i] != 0) {
      (*size)++;
      arr = (int *)realloc(arr, *size*sizeof(int));
      for (int j = *size - 1; j > i ; --j) {
        arr[j] = arr[j - 1];
      }
    }
  } else {
    int old_size = *size;
    *size = i + 1;
    arr = (int *)realloc(arr, *size*sizeof(int));
    for (int j = old_size; j < *size; ++j) {
      arr[j] = 0;
    }
  }

  arr[i] = v;

  return arr;
}

int main() {
  int *arr = (int *)malloc(sizeof(int));
  arr[0] = 0;
  int size = 1;

  int i, v;

  int stop = 0;
  while (!stop) {
    printf("Enter index and value:\n");
    scanf("%d %d", &i, &v);

    if (v == 0) {
      printf("end\n");
      stop = 1;
      continue;
    }

    if (i < 0) {
      continue;
    }

    arr = handle_input(arr, &size, i, v);
    print_array(arr, size);
  }
  free(arr);
  return 0;
}
