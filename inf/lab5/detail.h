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
detail *detail_from_str(const char *str);
char *detail_to_str(const detail *d);
detail *rand_detail();
detail **rand_detail_array(int n);
void free_detail_array(detail **arr, int size);
void print_detail_array(detail **arr, int size);

detail **read_details_from_file(int *size, const char *filename);
int write_to_file(detail **arr, int size, const char *filename);

// comarators
// descending
// ascending
int cmp_detail_count_asc(const void *a, const void *b);
int cmp_detail_count_des(const void *a, const void *b);
int cmp_detail_name_asc(const void *a, const void *b);
int cmp_detail_name_des(const void *a, const void *b);
int cmp_detail_id_asc(const void *a, const void *b);
int cmp_detail_id_des(const void *a, const void *b);


#endif
