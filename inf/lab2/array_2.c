#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *input_array(int *len_p) {
  *len_p = 0;
  while (*len_p <= 0) {
    printf("Input arrays length:\n");
    scanf("%d", len_p);
  }

  int *arr = (int *)malloc(*len_p * sizeof(int));
  // 0 means false, not 0 means true
  if (!arr) { // same: if (arr == NULL)
    printf("malloc error\n");
    return NULL; // нулевой адрес/указатель
  } else {
    for (int i = 0; i < *len_p; ++i) {
      scanf("%d", &arr[i]);
    }
    return arr;
  }
}
void array_remove_dups_3(int *data, int *len) {

  int new_size = 1;
  int i = new_size;
  while (i < *len) {
    int is_dup = 0;
    for (int j = 0; j < new_size; j++) {
      if (data[j] == data[i]) {
        is_dup = 1;
        break;
      }
    }

    if (!is_dup) {
      data[new_size] = data[i];
      new_size++;
    }

    i++;
  }

  *len = new_size;
}
void print_array(int *data, int len) {
  printf("array's length: %d\n", len);
  for (int i = 0; i < len - 1; ++i) {
    printf("data[%d] = %d\n", i, data[i]);
  }
  printf("\n");
}

int main() {
  int len, len3;
  int *arr = NULL;
  double time_spent3 = 0.0;
  arr = input_array(&len);
  len3 = len;
  int *arr3 = (int *)malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    arr3[i] = arr[i];
  }
  if (arr != NULL) {
    clock_t begin3 = clock();
    array_remove_dups_3(arr3, &len3);
    clock_t end3 = clock();
    print_array(arr3, len);
    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("(alg3) The elapsed time is %.10f seconds\n", time_spent3);
  }
  free(arr3);
  free(arr);
  return 0;
}
