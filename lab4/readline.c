#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>

#define BUFFER_SIZE 20
#define FORMAT_STR ("%19[^\n]s")

size_t mystrlen(const char *s) {
    size_t res = 0;
    while (*s) {
        ++s; // lllggghhh'\0'
        ++res;
    }
    return res;
}

int myreadline(char *p_str, char **ppstr) {
    printf("%s", p_str);

    int size = BUFFER_SIZE;
    int curSize = 0;
    char *str = malloc(BUFFER_SIZE * sizeof(char));

    if (str == NULL) {
        printf("Error of malloc in readline");
        return EOF;
    }

    str[0] = 0;
    int str_ended = 0;
    int t;
    do {
        // lfkjjhdjghjd25451248________________________
        t = scanf(FORMAT_STR, str + curSize);
        if (t == EOF) {
            *ppstr = str;
            return EOF;
        }
        str_ended = str[curSize] == 0;
        curSize += mystrlen(str + curSize);
        if (curSize + BUFFER_SIZE >= size) {
            size += BUFFER_SIZE;
            str = realloc(str, sizeof(char) * size);
        }

    } while (!str_ended);

    *ppstr = str;
    char c;
    scanf("%c", &c);
    return curSize;
}

void remove_duplicates(char *str) {
    if (str == NULL) {
        return;
    }
    int len = mystrlen(str);
    if (len == 0) {
        return;
    }

    int idx = 1;

    char last_char = str[0];
    int j = 1;

    // str = "  abc   de   "

    while (idx < len) {
        if (str[idx] == last_char) {
            while (str[idx] == last_char && idx < len) {
                idx++;
            }
        }

        if (idx < len) {
            last_char = str[idx];
            str[j] = str[idx];
            j++;
            idx++;
        }
    }

    str[j] = 0;

    // if (j > 0 && str[j - 1] ) {
    //   str[j - 1] = 0; // fixing last remaining space
    // }
}

int my_isspace(char c) {
    return c == ' ' || c == '\t';
}

void strip_string(char *str) {
    if (str == NULL) {
        return;
    }
    int len = mystrlen(str);
    int idx = 0;
    while (my_isspace(str[idx]) && idx < len) {
        idx++;
    }

    int last_char_was_space = 0;
    int j = 0;

    if (idx + 1 == len) {
        str[0] = 0;
    } else {
        // str = "  abc   de   "

        while (idx < len) {
            if (my_isspace(str[idx]) && last_char_was_space) {
                while (my_isspace(str[idx]) && idx < len) {
                    idx++;
                }
            }

            if (idx < len) {
                last_char_was_space = my_isspace(str[idx]);
                str[j] = last_char_was_space ? ' ' : str[idx];
                j++;
                idx++;
            }
        }
    }
    str[j] = 0;

    if (j > 0 && my_isspace(str[j - 1])) {
        str[j - 1] = 0;
    }
}

void my_task() {
    char *str;
    int t = 0;
    do {
        t = myreadline("input string:", &str);
        if (t > 0 && str != NULL) {
            printf("before: \"%s\"\n", str);
            strip_string(str);
            printf("after:  \"%s\"\n", str);
            remove_duplicates(str);
            printf("my task:  \"%s\"\n", str);
            free(str);
        }
    } while (t != EOF && str != NULL); // if (str) === if (str != NULL)
}

int main() {
  time_t t0 = time(0);
  my_task();
  time_t t1 = time(0);
  double time_in_seconds = difftime(t1, t0);
  return 0;
}
