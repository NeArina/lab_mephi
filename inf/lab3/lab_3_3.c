#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
void input_int(int *x, int min_x, int max_x, char *prompt) {
    char *end;
    int t;
    int tmp;
    do {
        char buffer[200];
        printf("%s", prompt);
        t = scanf("%s", buffer);
        tmp = strtol(buffer, &end, 10);
        if (t == EOF) {
            printf("error read, EOF\n");
        }  else if (t == 0) {
            printf("input not a string O_o\n");
            scanf("%*[^\n]");
        } else if (*end != 0) {
            printf("not an int? try again\n");
        } else if (!(min_x <= tmp && tmp <= max_x)) {
            printf("the value must be between %d and %d\n", min_x, max_x);
        }
    } while (!(min_x <= tmp && tmp <= max_x) || *end != 0);
    *x = tmp;
}

void input_double(double *x, char *prompt) {
    printf("%s", prompt);
    double t;
    do {
        t = scanf("%lf", x);
        if (t == EOF) {
            printf("error read\n");
        } else if (t == 0) {
            printf("input not number\n");
            scanf("%*[^\n]");
        }
    } while (t <= 0);
}

double *read_array(int *size) {
    int n = -1;
    while (n <= 0) {
        input_int(&n, 0, INT_MAX, "enter array's length: ");
    }
    *size = n;
    double *arr = (double *) malloc(n * sizeof(double));
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &arr[i]);
    }
    return arr;
}

void print_array(double *arr, int size) {
    if (arr == NULL) {
        printf("NULL\n");
    } else if (size == 0) {
        printf("EMPTY\n");
    } else {
        for (int i = 0; i < size; ++i) {
            printf("a[%d] = %lf\n", i, arr[i]);
        }
    }
}

int is_decimal_larger(double x) {
    double integer_part;
    double decimal_part = modf(fabs(x), &integer_part);
    long a = (long) integer_part;
    long long b = 0;
    long digit = 0;
    decimal_part += DBL_EPSILON * 10;
    while (decimal_part > 1000 * DBL_EPSILON) {
        decimal_part *= 10;
        digit = (long) decimal_part;
        decimal_part -= digit;
        b = b * 10 + digit;

        if (b > a) {
            return 1;
        }
    }
    return a < b;
}

double *my_task(double **arr_old, int *size, int *new_size) {
    double *arr = *arr_old;
    double *new_arr = malloc(*size * sizeof(double));
    int i = 0, j = 0;
    while (i < *size) {
        if (is_decimal_larger(arr[i])) {
            new_arr[j] = arr[i];
            j++;
            for (int k = i; k < *size - 1; k++) {
                arr[k] = arr[k + 1];
            }
            (*size)--;
        } else {
            i++;
        }
    }
    *new_size = j;
    if (*new_size > 0) {
        new_arr = (double *) realloc(new_arr, *new_size * sizeof(double));
    } else {
        free(new_arr);
        new_arr = NULL;
    }
    if (*size > 0) {
        arr = (double *) realloc(arr, *size * sizeof(double));
    } else {
        free(arr);
        arr = NULL;
    }
    *arr_old = arr;
    return new_arr;
}

double *insert_elem(double *arr, int *size, int *length) {
    double m;
    int n;
    input_int(&n, 0, INT_MAX, "input index = ");

    input_double(&m, "value = ");

    if (n > *size) {
        n = *size;
    }
    if (*size + 1 > *length) {
        *length *= 2;
        arr = (double *) realloc(arr, *length * sizeof(double));
    }
    if (n < *size) {
        (*size)++;
        for (int j = *size - 1; j > n; --j) {
            arr[j] = arr[j - 1];
        }
        arr[n] = m;
    } else {
        arr[*size] = m;
        (*size)++;
    }
    return arr;
}

double *delete_elem(double *arr, int *size, int *length) {
    int index_elem;
    input_int(&index_elem, 0, *size-1, "input index = ");
    for (int i = index_elem; i < *size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --(*size);
    if (*size <= *length / 2 && *length > 1) {
        *length = *length / 2;
        arr = (double *) realloc(arr, *length * sizeof(double));
    }
    return arr;
}

int main(void) {
    int size;
    double *arr = read_array(&size);
    if (arr == NULL && size != -1) {
        printf("memory allocation error\n");
        return 2;
    }
    print_array(arr, size);
    int length = size;
    double *new_arr = NULL;
    int new_size;
    int stop = 0;
    int cmd = 0;
    while (!stop) {
        printf("Commands:                 \n \
    0 - end the program               \n \
    1 - print current array           \n \
    2 - do the task and print results \n \
    3 - insert by index               \n \
    4 - delete by index               \n");
        input_int(&cmd, 0, 4, "");
        switch (cmd) {
            case 0:
                stop = 1;
                break;
            case 1:
                print_array(arr, size);
                break;
            case 2:
                if (arr == NULL) {
                    printf("array is empty, cannot execute my task\n");
                } else {
                    new_arr = my_task(&arr, &size, &new_size);
                    printf("Original array, after:\n");
                    print_array(arr, size);
                    printf("\n");
                    printf("New array, after:\n");
                    print_array(new_arr, new_size);
                    printf("\n");
                }
                break;
            case 3:
                arr = insert_elem(arr, &size, &length);
                break;
            case 4:
                if (arr == NULL) {
                    printf("array is empty, cannot execute my task\n");
                } else {
                    arr = delete_elem(arr, &size, &length);
                }
                break;
            default:
                printf("wrong cmd number\n");
        }
    }
    free(arr);
    free(new_arr);
    return 0;
}
