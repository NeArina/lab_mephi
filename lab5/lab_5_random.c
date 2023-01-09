#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "detail.h"
#include "mysort.h"
#include "read_options.h"

// .csv comma separated values
// 12345678|Some Name|25
// 12345678;Some Name;25

extern char *optarg;
extern int optind, opterr, optopt;

// .csv comma separated values
// 12345678|Some Name|25
// 12345678;Some Name;25
// -o output.tx -i input.txt

void *choose_sort_function(enum SortId sort_id, enum SortDirection sort_dir,
                           enum SortMember sort_memb) {
  if (sort_dir == SORT_DIRECTION_ASC) {
    switch (sort_memb) {
      case SORT_MEMBER_ID:
        return &cmp_detail_id_asc;
        break;
      case SORT_MEMBER_NAME:
        return &cmp_detail_name_asc;
        break;
      case SORT_MEMBER_COUNT:
        return &cmp_detail_count_asc;
        break;

      default:
        // should not happen as we checked that sort_memb is initialised
        // properly
        break;
    }
  } else {
    switch (sort_memb) {
      case SORT_MEMBER_ID:
        return &cmp_detail_id_des;
        break;
      case SORT_MEMBER_NAME:
        return &cmp_detail_name_des;
        break;
      case SORT_MEMBER_COUNT:
        return &cmp_detail_count_des;
        break;

      default:
        // should not happen as we checked that sort_memb is initialised
        // properly
        break;
    }
  }

  return NULL;
}

double task_once(enum SortId sort_id, enum SortDirection sort_dir,
                 enum SortMember sort_memb, int arr_size) {
  int size = arr_size;
  detail **arr = rand_detail_array(arr_size);

  // printf("%p %d", arr, size);
  // printf("s = %d, d = %d, m = %d\n", sort_id, sort_dir, sort_memb);
  // print_detail_array(arr, size);

  int (*cmp)(const void *a, const void *b) =
      choose_sort_function(sort_id, sort_dir, sort_memb);

  clock_t begin = clock();
  clock_t end;
  double time_spent = 0;

  switch (sort_id) {
    case SORT_ID_STD_QUICK:
      // printf("using std qsort\n");
      qsort(arr, size, sizeof(detail *), cmp);
      break;
    case SORT_ID_CUSTOM_QUICK:
      // printf("using custom qsort\n");
      myqsort(arr, size, cmp);
      break;
    case SORT_ID_CUSTOM_INSERT:
      // printf("using custom insert sort\n");
      sort_insert(arr, size, cmp);
      break;

    default:
      // should not happen as we checked that sort_id is initialised
      // properly
      break;
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  // print_detail_array(arr, size);
  // printf("size = %d,time = %.7lf\n", arr_size, time_spent);

  free_detail_array(arr, size);
  return time_spent;
}

double my_sort_task(enum SortId sort_id, enum SortDirection sort_dir,
                    enum SortMember sort_memb, int arr_num, int arr_size) {
  srand(time(0));

  double time_sum = 0;
  int arr_num_copy = arr_num;
  while (arr_num_copy-- > 0) {
    time_sum += task_once(sort_id, sort_dir, sort_memb, arr_size);
  }
  double avg = time_sum / arr_num;
  // printf("AAA %.7lf %d average execution time is %.7lf\n", time_sum, arr_num,
  //        avg);

  return avg;
}

int main(int argc, char **argv) {
  enum SortId sort_id = SORT_ID_UNDEFINED;
  enum SortDirection sort_dir = SORT_DIRECTION_UNDEFINED;
  enum SortMember sort_memb = SORT_MEMBER_UNDEFINED;

  read_options(argc, argv, &sort_id, &sort_dir, &sort_memb);

  char *array_count_s = NULL;
  char *array_len_s = NULL;
  if (optind + 1 < argc) {
    array_count_s = argv[optind];
    array_len_s = argv[optind + 1];
  }

  int arr_count = atoi(array_count_s);
  int arr_len = atoi(array_len_s);

  // лишние позиционные аргументы
  if (optind + 2 < argc) {
    fprintf(stderr, "Unexpected argument %s\n", argv[optind + 2]);
  }

  if (sort_dir == SORT_DIRECTION_UNDEFINED || sort_id == SORT_ID_UNDEFINED ||
      sort_memb == SORT_MEMBER_UNDEFINED || arr_count <= 0 || arr_len <= 0) {
    printf(
        "program arguments are incorrect\n\
        usage: -s <sort_id> -m <sort_member> <sort_direction> <arrays_count> <array_len>\n\
        where\n\
        <sort_id> is one of std_quick, custom_quick, custom_insert\n\
        <sort_member> is one of id, name, count\n\
        <sort_direction> is -a or -d\n");
    return 1;
  }

  char filename[80];
  sprintf(filename, "sort_time_sort_%d_member_%d_direction_%d.txt", sort_id,
          sort_memb, sort_dir);
  FILE *out = fopen(filename, "a");

  double time = my_sort_task(sort_id, sort_dir, sort_memb, arr_count, arr_len);

  fprintf(out, "%d\t%.10lf\n", arr_len, time);

  fclose(out);
  return 0;
}