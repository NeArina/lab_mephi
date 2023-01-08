#include "mystr.h"

#include <stdlib.h>

// собственная реализация нахождения длины строки
size_t mystrlen(const char* s) {
  size_t res = 0;  // присваиваем 0 будущему значению длины строки
  while (*s) {
    ++s;  // lllggghhh'\0'; идём по строке, до признака конца строки
    ++res;  // находим длину строки, после окончания цикла вернём
  }
  return res;  // возвращаем найденную длину строки
}

// собственная реализация нахождения пробелов и табуляции
// функции передаём символ
int my_isspace(char c) {
  return c == ' ' || c == '\t';  // возвращаем или пробел, или табуляцию
}

// собственная реализация копирования строки
char* mystrcpy(char* dest, const char* src) {
  // a = b = 2;
  // b = 2;
  while ((*dest++ = *src++))
    ;  // в dest копируем src
  return dest;
}
// dest = "hello0........."
//              _ = ptr
// s = "abc0"
//      _ = s
char* mystrcat(char* dest, const char* s) {
  char* ptr = dest + mystrlen(dest);  //
  while (*s != '\0') {  // пока не признак конца строки
    *ptr++ = *s++;      //
  }
  *ptr = '\0';  // после выполнения цикла в строке нет признака окончания
                // строки; присвоим признак окон. строки
  return dest;
}
