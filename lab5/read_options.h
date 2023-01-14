#ifndef READ_OPTIONS_H
#define READ_OPTIONS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

enum SortId {
  SORT_ID_UNDEFINED = 0,
  SORT_ID_STD_QUICK,
  SORT_ID_CUSTOM_QUICK,
  SORT_ID_CUSTOM_SELECTION
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

void read_options(int argc, char **argv, enum SortId *sort_id,
                  enum SortDirection *sort_dir, enum SortMember *sort_memb);

#endif