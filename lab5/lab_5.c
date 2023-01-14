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

int my_sort_task(int argc, char **argv) {
  enum SortId sort_id = SORT_ID_UNDEFINED;
  enum SortDirection sort_dir = SORT_DIRECTION_UNDEFINED;
  enum SortMember sort_memb = SORT_MEMBER_UNDEFINED;

  read_options(argc, argv, &sort_id, &sort_dir, &sort_memb);

  char *input = NULL;
  char *output = NULL;
  if (optind + 1 < argc) {
    input = argv[optind];
    output = argv[optind + 1];
  }

  // лишние позиционные аргументы
  if (optind + 2 < argc) {
    fprintf(stderr, "Unexpected argument %s\n", argv[optind + 2]);
  }

  if (sort_dir == SORT_DIRECTION_UNDEFINED || sort_id == SORT_ID_UNDEFINED ||
      sort_memb == SORT_MEMBER_UNDEFINED || input == NULL || output == NULL ||
      strlen(input) == 0 || strlen(output) == 0) {
    printf(
        "program arguments are incorrect\n\
        usage: -s <sort_id> -m <sort_member> <sort_direction> <input_file> <output_file>\n\
        where\n\
        <sort_id> is one of std_quick, custom_quick, custom_selection\n\
        <sort_member> is one of id, name, count\n\
        <sort_direction> is -a or -d\n");
    return 1;
  }

  int size = 0;
  detail **arr = read_details_from_file(&size, input);
  if (arr == NULL) {
    printf("%s", "failed to open input file\n");
    return 0;
  }

  printf("s = %d, d = %d, m = %d\n", sort_id, sort_dir, sort_memb);
  // print_detail_array(arr, size);

  int (*cmp)(const void *a, const void *b) =
      choose_sort_function(sort_id, sort_dir, sort_memb);

  switch (sort_id) {
    case SORT_ID_STD_QUICK:
      printf("using std qsort\n");
      qsort(arr, size, sizeof(detail *), cmp);
      break;
    case SORT_ID_CUSTOM_QUICK:
      printf("using custom qsort\n");
      myqsort(arr, size, cmp);
      break;
    case SORT_ID_CUSTOM_SELECTION:
      printf("using custom selection sort\n");
      sort_selection(arr, size, cmp);
      break;

    default:
      // should not happen as we checked that sort_id is initialised
      // properly
      break;
  }

  write_to_file(arr, size, output);

  // print_detail_array(arr, size);

  free_detail_array(arr, size);
  return 0;
}

int main(int argc, char **argv) {
  my_sort_task(argc, argv);
  return 0;
}