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

void array_remove_dups(int *data, int *len) {
  for (int i = 0; i < *len - 1; ++i) {
    for (int j = i + 1; j < *len; ++j) {
      if (data[i] == data[j]) {
        int count = 1;
        while (data[i] == data[j + count]) {
          count++;
        }
        // сдвинуть хвост на count влево
        for (int k = j; k < *len - 1; ++k) {
          data[k] = data[k + 1]; // j + count
        }
        (*len)--;
        j--;
      }
    }
  }
}
void print_array(int *data, int len) {
  printf("array's length: %d\n", len);
  for (int i = 0; i < len; ++i) {
    printf("data[%d] = %d\n", i, data[i]);
  }
  printf("\n");
}
int main() {
  int len;
  int *arr = NULL;
  double time_spent2 = 0.0;
  arr = input_array(&len);
  if (arr != NULL) {
    clock_t begin2 = clock();
    array_remove_dups(arr, &len);
    clock_t end2 = clock();
    print_array(arr, len);
    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
  }
  printf("(original) The elapsed time is %.10f seconds\n", time_spent2);
  free(arr);
  return 0;
}
