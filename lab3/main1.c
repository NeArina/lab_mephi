#include <stdio.h>
#include "head1.h"
#include <stdlib.h>

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
      printf("Commands:               \n \
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
