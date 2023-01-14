#include "read_options.h"

enum SortId get_sort_id(const char *str) {
  if (strcmp("std_quick", str) == 0) {
    return SORT_ID_STD_QUICK;
  } else if (strcmp("custom_quick", str) == 0) {
    return SORT_ID_CUSTOM_QUICK;
  } else if (strcmp("custom_selection", str) == 0) {
    return SORT_ID_CUSTOM_SELECTION;
  } else {
    printf(
        "error reading argument -s value; possible values are: "
        "std_quick, custom_quick, custom_selection\n");
    return SORT_ID_UNDEFINED;
  }
}

enum SortMember get_member_id(const char *str) {
  if (strcmp("id", optarg) == 0) {
    return SORT_MEMBER_ID;
  } else if (strcmp("name", optarg) == 0) {
    return SORT_MEMBER_NAME;
  } else if (strcmp("count", optarg) == 0) {
    return SORT_MEMBER_COUNT;
  } else {
    // TODO
    printf(
        "error reading argument -s value; possible values are: "
        "id, name, count\n");
    return SORT_MEMBER_UNDEFINED;
  }
  // printf("-m = %d\n", *sort_memb);
}

// for (index = optind; index < argc; index++)
//     printf ("Non-option argument %s\n", argv[index]);
void read_options(int argc, char **argv, enum SortId *sort_id,
                  enum SortDirection *sort_dir, enum SortMember *sort_memb) {
  int rez = 0;
  //	opterr = 0;
  while ((rez = getopt(argc, argv, "s:m:ad")) !=
         -1) {  // sort, member, direction, input, output
    switch (rez) {
      case 's':
        *sort_id = get_sort_id(optarg);
        // printf("-s = %d\n", *sort_id);
        break;
      case 'm':
        *sort_memb = get_member_id(optarg);
        // printf("-m = %d\n", *sort_memb);
        break;
      case 'd':
        *sort_dir = SORT_DIRECTION_DES;
        // printf("-d = %d\n", *sort_dir);
        break;
      case 'a':
        *sort_dir = SORT_DIRECTION_ASC;
        // printf("-d = %d\n", *sort_dir);
        break;
      case '?':
        printf("Error found ! \n");
        break;
    }  // switch
  }    // while
}