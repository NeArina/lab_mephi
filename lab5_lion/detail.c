#include "detail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

detail *create_detail(const char *id, const char *name, int count) {
  detail *result = (detail *)malloc(sizeof(detail));

  if (!result) {
    return NULL;
  }

  strncpy(result->id, id, 8);
  (result->id)[8] = 0;

  int name_len = strlen(name);
  result->name = (char *)malloc(sizeof(char) * name_len + 1);
  strncpy(result->name, name, name_len);
  (result->name)[name_len] = 0;

  result->count = count;

  return result;
}

void free_detail(detail *det) {
  free(det->name);
  free(det);
}

void print_detail(detail *det) {
  printf("Detail: id = %s, name = %s, count = %d\n", det->id, det->name,
         det->count);
}

// comp	-	comparison function which returns ​a negative integer value if
// the first argument is less than the second, a positive integer value if the
// first argument is greater than the second and zero if the arguments are
// equivalent.
int cmp_detail_count_asc(const void *a, const void *b) {
  detail *det_a = *(detail **)a;
  detail *det_b = *(detail **)b;

  if (det_a->count < det_b->count) {
    return -1;
  } else if (det_a->count > det_b->count) {
    return 1;
  } else {
    return 0;
  }
}
 // descending
 // ascending 
int cmp_detail_count_des(const void *a, const void *b) {
  return cmp_detail_count_asc(b, a);
}

int cmp_detail_name_asc(const void *a, const void *b) {
  detail *det_a = *(detail **)a;
  detail *det_b = *(detail **)b;

  return strcmp(det_a->name, det_b->name);
}

int cmp_detail_name_des(const void *a, const void *b) {
  return cmp_detail_name_asc(b, a);
}

int cmp_detail_id_asc(const void *a, const void *b) {
  detail *det_a = *(detail **)a;
  detail *det_b = *(detail **)b;

  return strcmp(det_a->id, det_b->id);
}

int cmp_detail_id_des(const void *a, const void *b) {
  return cmp_detail_id_asc(b, a);
}