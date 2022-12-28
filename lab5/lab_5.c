#include "detail.h"
#include <stdio.h>
#include <stdlib.h>
// .csv comma separated values
// 12345678|Some Name|25
// 12345678;Some Name;25
int main() {
  FILE *fp = fopen("test_data.string", "r");
    if (fp == NULL) {
        //oi oi 
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    // читаем строчку за строчкой, strtok()
    while((read = getline(&line, &len, fp)) != -1) {
        printf("line len = %zu\n", read);
        printf("line: %s", line);
    }
  // передать сюда
  // из строки целое число - посмотреть, функция
  detail *d1 = create_detail("12345678", "Some Name", 25);
  detail *d2 = create_detail("00001111", "A Name", 2);
  detail *d3 = create_detail("98765432", "LSKF hkds", 10);

  const int arr_size = 3;

  detail **arr = calloc(arr_size, sizeof(detail *));
  arr[0] = d1;
  arr[1] = d2;
  arr[2] = d3;

  for (int i = 0; i < arr_size; i++) {
    print_detail(arr[i]);
  }

  qsort(arr, arr_size, sizeof(detail *), cmp_detail_count_asc);

  for (int i = 0; i < arr_size; i++) {
    print_detail(arr[i]);
  }

  for (int i = 0; i < arr_size; i++) {
    free_detail(arr[i]);
  }

  return 0;
}