#ifndef MYSORT_H
#define MYSORT_H

#include <stdlib.h>

void sort1(void *base, size_t nitems, int (*compar)(const void *, const void *));

#endif