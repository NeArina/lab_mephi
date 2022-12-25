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

  // int stop = 0;
  // int cmd = 0;
  // while (!stop)
  // {
  //     printf("Commands:               \n \
    // 0 - end the program               \n \
    // 1 - print current array           \n \
    // 2 - do the task and print results \n \
    // 3 - insert by index               \n \
    // 4 - delete by index               \n");
  //     input_int(&cmd, 0, 4, "");
  //     switch (cmd)
  //     {
  //     case 0:
  //         stop = 1;
  //         break;
  //     case 1:
  //         print_array(arr, size);
  //         break;
  //     case 2:
  //         if (arr == NULL)
  //         {
  //             printf("array is empty, cannot execute my task\n");
  //         }
  //         else
  //         {
  //             new_arr = my_task(&arr, &size, &new_size);
  //             printf("Original array, after:\n");
  //             print_array(arr, size);
  //             printf("\n");
  //             printf("New array, after:\n");
  //             print_array(new_arr, new_size);
  //             printf("\n");
  //         }
  //         break;
  //     case 3:
  //         arr = insert_elem(arr, &size, &length);
  //         break;
  //     case 4:
  //         if (arr == NULL)
  //         {
  //             printf("array is empty, cannot execute my task\n");
  //         }
  //         else
  //         {
  //             arr = delete_elem(arr, &size, &length);
  //         }
  //         break;
  //     default:
  //         printf("wrong cmd number\n");
  //     }
  // }

  return 0;
}