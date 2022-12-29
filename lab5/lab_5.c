#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "detail.h"
#include "mysort.h"
// .csv comma separated values
// 12345678|Some Name|25
// 12345678;Some Name;25

extern char *optarg;
extern int optind, opterr, optopt;

enum SortId {
  SORT_ID_UNDEFINED = 0,
  SORT_ID_STD_QUICK,
  SORT_ID_CUSTOM_QUICK,
  SORT_ID_CUSTOM_INSERT
};
enum SortDirection {
  SORT_DIRECTION_UNDEFINED = 0,
  SORT_DIRECTION_ASC,
  SORT_DIRECTION_DES
};
enum SortMember {
  SORT_MEMBER_UNDEFINED = 0,
  SORT_MEMBER_ID,
  SORT_MEMBER_NAME,
  SORT_MEMBER_COUNT
};

// .csv comma separated values
// 12345678|Some Name|25
// 12345678;Some Name;25
// -o output.tx -i input.txt
void read_options(int argc, char **argv, enum SortId *sort_id,
                  enum SortDirection *sort_dir, enum SortMember *sort_memb,
                  char *input, char *output) {
  int rez = 0;
  //	opterr = 0;
  while ((rez = getopt(argc, argv, "s:m:d:i:o:")) !=
         -1) {  // sort, member, direction, input, output
    switch (rez) {
      case 's':
        if (strcmp("std_quick", optarg) == 0) {
          *sort_id = SORT_ID_STD_QUICK;
        } else if (strcmp("custom_quick", optarg) == 0) {
          *sort_id = SORT_ID_CUSTOM_QUICK;
        } else if (strcmp("custom_insert", optarg) == 0) {
          *sort_id = SORT_ID_CUSTOM_INSERT;
        } else {
          printf(
              "error reading argument -s value; possible values are: "
              "std_quick, custom_quick, custom_insert\n");
        }
        printf("-s = %d\n", *sort_id);
        break;
      case 'm':
        if (strcmp("id", optarg) == 0) {
          *sort_memb = SORT_MEMBER_ID;
        } else if (strcmp("name", optarg) == 0) {
          *sort_memb = SORT_MEMBER_NAME;
        } else if (strcmp("count", optarg) == 0) {
          *sort_memb = SORT_MEMBER_COUNT;
        } else {
          // TODO
          printf(
              "error reading argument -s value; possible values are: "
              "std_quick, custom_quick, custom_insert\n");
        }
        printf("-m = %d\n", *sort_memb);
        break;
      case 'd':
        if (strcmp("asc", optarg) == 0) {
          *sort_dir = SORT_DIRECTION_ASC;
        } else if (strcmp("des", optarg) == 0) {
          *sort_dir = SORT_DIRECTION_DES;
        } else {
          // TODO
          printf(
              "error reading argument -s value; possible values are: "
              "std_quick, custom_quick, custom_insert\n");
        }
        printf("-d = %d\n", *sort_dir);
        break;
      case 'i':
        if (optarg) {
          strncat(input, optarg, 80);
        } else {
          // TODO no value
        }
        printf("input = \"%s\"\n", optarg);
        break;
      case 'o':
        if (optarg) {
          strncat(output, optarg, 80);
        } else {
          // TODO no value
        }
        printf("output = \"%s\"\n", optarg);
        break;
      case '?':
        printf("Error found ! \n");
        break;
    }  // switch
  }    // while
}

int main(int argc, char **argv) {
  enum SortId sort_id = SORT_ID_UNDEFINED;
  enum SortDirection sort_dir = SORT_DIRECTION_UNDEFINED;
  enum SortMember sort_memb = SORT_MEMBER_UNDEFINED;

  char input[81] = {0};
  char output[81] = {0};

  read_options(argc, argv, &sort_id, &sort_dir, &sort_memb, input, output);

  FILE *fp = fopen(input, "r");
  if (fp == NULL) {
    // oi oi
    printf("error open input\n");
    return 0;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  detail **arr = calloc(1, sizeof(detail *));
  int arr_capacity = 1;
  int arr_count = 0;
  // читаем строчку за строчкой, strtok()
  while ((read = getline(&line, &len, fp)) != -1) {
    printf("getline: %s\n", line);
    detail *d = detail_from_str(line);
    if (arr_count + 1 > arr_capacity) {
      arr_capacity *= 2;
      arr = realloc(arr, arr_capacity * sizeof(detail *));
      printf("realloc %d\n", arr_capacity);
    }
    printf("count %d\n", arr_count);
    arr[arr_count++] = d;
    printf("count2 %d\n", arr_count);
  }
  free(line);
  printf("YYYYYYY");
  // передать сюда
  // из строки целое число - посмотреть, функция
  // detail *d1 = create_detail("12345678", "Some Name", 25);
  // detail *d2 = create_detail("00001111", "A Name", 2);
  // detail *d3 = create_detail("98765432", "LSKF hkds", 10);

  // const int arr_size = 3;

  // detail **arr = calloc(arr_count, sizeof(detail *));
  // arr[0] = d1;
  // arr[1] = d2;
  // arr[2] = d3;

  for (int i = 0; i < arr_count; i++) {
    print_detail(arr[i]);
    // printf("%s\n", detail_to_str(arr[i]));
  }
  // arr + sizeof(detail*) * 30
  // arr[30]
  // arr[5] == *(arr + 5) array items
  // &arr[5] == arr + 5 pointers to array items
  // qsort(arr, arr_size, sizeof(detail *), cmp_detail_count_asc);
  myqsort(arr, arr_count, cmp_detail_count_asc);

  for (int i = 0; i < arr_count; i++) {
    print_detail(arr[i]);
  }

  for (int i = 0; i < arr_count; i++) {
    free_detail(arr[i]);
  }

  return 0;
}