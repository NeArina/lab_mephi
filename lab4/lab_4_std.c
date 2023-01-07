#include <ctype.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// выполнение собственного задания
char *remove_duplicates(char *str) {
  // выделяем память под результирующую строку
  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  // если строка нулевая
  if (str == NULL) {
    return NULL;  // возвращаем ноль
  }
  // находим длину строки
  int len = strlen(str);  // len
  // если длина ноль, результирующей строке присвоим ноль и вернём ноль
  if (len == 0) {
    result[0] = 0;
    return result;
  }

  int idx = 1;
  char last_char = str[0];
  result[0] = str[0];
  int j = 1;

  while (idx < len) {
    if (str[idx] == last_char) {
      while (str[idx] == last_char && idx < len) {
        idx++;
      }
    }

    if (idx < len) {
      last_char = str[idx];
      result[j] = str[idx];
      j++;
      idx++;
    }
  }

  result[j] = 0;
  return result;
}
// общий смысл: убрать лишнюю табуляцию и пробелы, оставив 1 пробел м/у словами
char *strip_string_tok(char *str) {
  char *str_copy = (char *)calloc(strlen(str) + 1, sizeof(char));
  strcpy(str_copy, str);

  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  int j = 0;

  char *token;

  /* get the first token */
  // 'e'
  // "e"
  token = strtok(str_copy, " \t\n");
  // если есть первое слово
  if (token) {
    strcpy(result + j, token);  //
    j += strlen(token);         //
    result[j++] = ' ';          //
  }
  /* walk through other tokens */
  while (token) {
    // printf(" %s\n", token);
    token = strtok(NULL, " \t\n");

    if (token) {
      strcpy(result + j, token);
      j += strlen(token);
      result[j++] = ' ';
    }
  }
  if (j > 0 && result[j - 1] == ' ') {
    result[j - 1] = 0;
  }
  // освобождаем память, выделенную под копию строки
  free(str_copy);
  // возвращаем результирующую строку
  return result;
}

// char *strip_string(char *str) {
//   if (str == NULL) {
//     return NULL;
//   }

//   char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
//   // calloc(n, n_per_one) -> n * n_per_one
//   // calloc(10, 1 + 1) -> 20
//   // calloc(10 + 1, 1) -> 11

//   int len = strlen(str); // len
//   int idx = 0;
//   while (isspace(str[idx]) && idx < len) {
//     idx++;
//   }

//   int last_char_was_space = 0;
//   int j = 0;

//   if (idx + 1 == len) {
//     result[0] = 0;
//   } else {
//     // str = "  abc   de   "
//     while (idx < len) {
//       if (isspace(str[idx]) && last_char_was_space) {
//         while (isspace(str[idx]) && idx < len) {
//           idx++;
//         }
//       }
//       if (idx < len) {
//         last_char_was_space = isspace(str[idx]);
//         result[j] = last_char_was_space ? ' ' : str[idx];
//         j++;
//         idx++;
//       }
//     }
//   }
//   result[j] = 0;

//   if (j > 0 && isspace(result[j - 1])) {
//     result[j - 1] = 0; // fixing last remaining space
//   }
//   return result;
// }

void my_task() {
  char *str;  // создаем переменную под исходную строку
  char *s1;  // создаём переменную под строку, в которой удалили все пробелы
  char *s2;  // создаём переменную под строку, которую преобразовали после
             // выполнения индивидуального задания
  do {
    // считывание строк
    str = readline("input your string: ");
    // проверка на ненулевую строку
    if (str != NULL) {
      // печать строки, которую считали readline'ом
      printf("before: \"%s\"\n", str);
      // s1 = strip_string(str);
      // меняем строку, убрав табуляцию и лишние пробелы
      s1 = strip_string_tok(str);
      // печать строки, из которой убрали лишние пробелы и табуляцию, оставив 1
      // пробел между словами
      printf("after:  \"%s\"\n", s1);
      // начинаем замерять время выполнения индивидуального задания
      clock_t start = clock();
      // выполнение индивидуального задания и запись в s2
      s2 = remove_duplicates(s1);
      // конец замера времени выполнения индивидуального задания
      clock_t end = clock();
      // подсчёт времени, затраченного на выполнение индивидуального задания
      double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
      // печать времени, которое было затрачено на выполнение индивидуального
      // задания
      printf("time: %.10lf\n", (elapsed_time));
      // печать получившейся строки
      printf("my task:  \"%s\"\n", s2);
      // освобождаем память, выделенную под str, s1, s2
      free(str);
      free(s1);
      free(s2);
    }
  } while (str !=
           NULL);  // if (str) === if (str != NULL) // пока строка не нулевая
}

int main() {
  my_task();
  return 0;
}
