#include "myreadline.h"
#include <stdlib.h>
#include "mystr.h"
#include <stdio.h>


char *getstr(char *p_str) {
    char *ptr = (char *)calloc(1, sizeof(char));
    char buf[81] = {0};
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0){
            free(ptr);
            ptr = NULL;
            break;
                }
                if (n == 0){
                        scanf("%*c");
                }
                else{
                        len += mystrlen(buf);
                        ptr = (char *)realloc(ptr, len + 1);
                        ptr = mystrcat(ptr, buf);
                }
        }
        while (n > 0);
        return ptr;
}

