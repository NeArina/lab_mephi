#ifndef MYSORT_H
#define MYSORT_H

#include <stdlib.h>

#include "detail.h"

void myqsort(detail **arr, int n, int (*cmp)(const void *, const void *));
void sort_selection(detail **arr, int size,
                    int (*cmp)(const void *, const void *));

#endif