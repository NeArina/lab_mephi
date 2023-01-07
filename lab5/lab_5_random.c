#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
                  enum SortDirection *sort_dir, enum SortMember *sort_memb) {
  int rez = 0;
  //	opterr = 0;
  while ((rez = getopt(argc, argv, "s:m:d:")) !=
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
        // printf("-s = %d\n", *sort_id);
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
        // printf("-m = %d\n", *sort_memb);
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
        // printf("-d = %d\n", *sort_dir);
        break;
      case '?':
        printf("Error found ! \n");
        break;
    }  // switch
  }    // while
}

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

  if (sort_dir == SORT_DIRECTION_UNDEFINED || sort_id == SORT_ID_UNDEFINED ||
      sort_memb == SORT_MEMBER_UNDEFINED) {
    printf(
        "program arguments are incorrect\n\
        usage: -s <sort_id> -m <sort_member> -d <sort_direction> -i <input_file> -o <output_file>\n\
        where\n\
        <sort_id> is one of std_quick, custom_quick, custom_insert\n\
        <sort_member> is one of id, name, count\n\
        <sort_direction> is asc or des\n");
    return 1;
  }
  int n = 100;
  double time = 0;

  double prev_time = -1;

  FILE *out = fopen("sort_time.txt", "w");

  while (n < 1e7) {
    time = my_sort_task(sort_id, sort_dir, sort_memb, 5, n);
    if (prev_time > 0) {
      // printf("ratio to prev: %.10lf\n", time / prev_time);
    }
    prev_time = time;
    printf("len = %d, average execution time is %.7lf\n", n, time);
    fprintf(out, "%d %.10lf\n", n, time);
    n *= 10;
  }
  fclose(out);
  return 0;
}