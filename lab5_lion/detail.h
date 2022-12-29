#ifndef DETAIL_H
#define DETAIL_H

typedef struct detail {
  char id[9];
  char *name;
  unsigned int count;
} detail;

detail *create_detail(const char *id, const char *name, int count);

void free_detail(detail *det);

void print_detail(detail *det);

int cmp_detail_count_asc(const void *a, const void *b);

#endif