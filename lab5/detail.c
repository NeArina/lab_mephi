#include "detail.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myreadline.h"

detail *create_detail(const char *id, const char *name, int count) {
  detail *result =
      (detail *)malloc(sizeof(detail));  // выдедяем память под будущую деталь
                                         // (размер известен(лежит в detail.h))

  if (!result) {  // если память не удалось выделить (malloc(sizeof(detail)))
    return NULL;  // вернем в этом случае NULL
  }

  strncpy(
      result->id, id,
      8);  // скопируем id в буфер определённого размера (result->id), длина 8
  (result->id)[8] = 0;  // запишем в конец терминированный нуль

  int name_len = strlen(name);  // узнаем длину name'а
  result->name =
      (char *)malloc(sizeof(char) * (name_len + 1));  // выделим под name память
  strncpy(result->name, name,
          name_len);  // скопируем name в буфер result->name длиной name_len
  (result->name)[name_len] = 0;  // запишем в конце ноль

  result->count = count;  // result->count присвоим count

  return result;  // вернём получившуюся деталь
}

void free_detail(detail *det) {  // освободим деталь
  free(det->name);  // освободим отдельно имя, так как выделяли под него память
  free(det);  // освободим память под всё остальное
}

void print_detail(detail *det) {  // печать детали
  printf("Detail: id = %s, name = %s, count = %d\n", det->id, det->name,
         det->count);
}

// comp	-	comparison function which returns ​a negative integer value if
// the first argument is less than the second, a positive integer value if the
// first argument is greater than the second and zero if the arguments are
// equivalent.

// отсортировать по возрастанию два поля из разных деталей
int cmp_detail_count_asc(const void *a, const void *b) {
  // printf("using cmp_detail_count_asc\n");
  detail *det_a =
      *(detail **)a;  // разыменование(чтобы не писать везде звёздочку) ->
                      // *(detail ** (указание на деталь и указание на
                      // элемент(реальный тип)))
  detail *det_b = *(detail **)b;
  // сравнение и возвращение результатов
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
  // printf("using cmp_detail_count_des\n");
  return cmp_detail_count_asc(b, a);
}

// strcmp() - посимвольное сравнение строк
int cmp_detail_name_asc(const void *a, const void *b) {
  // printf("using cmp_detail_name_asc\n");
  detail *det_a = *(detail **)a;
  detail *det_b = *(detail **)b;

  return strcmp(det_a->name, det_b->name);
}

int cmp_detail_name_des(const void *a, const void *b) {
  // printf("using cmp_detail_name_des\n");
  return cmp_detail_name_asc(b, a);
}

// отсортировать по убыванию два поля из разных деталей
int cmp_detail_id_asc(const void *a, const void *b) {
  // printf("using cmp_detail_id_asc\n");
  detail *det_a = *(detail **)a;
  detail *det_b = *(detail **)b;

  return strcmp(det_a->id, det_b->id);
}

int cmp_detail_id_des(const void *a, const void *b) {
  // printf("using cmp_detail_id_des\n");
  return cmp_detail_id_asc(b, a);
}

detail *detail_from_str(const char *str) {
  // printf("from str: %s\n", str);
  char *str_copy = (char *)calloc(
      strlen(str) + 1, sizeof(char));  // выделим память под копию строки
  strcpy(str_copy, str);  // скопируем строку str в буфер str_copy

  /* get the first token */
  // 'e'
  // "e"
  char *id = strtok(str_copy, ";");  // найдём ; в строке и возмём первый токен
  char *name =
      strtok(NULL, ";");  // найдём следующий токен до второго ; (строчка
                          // осталась в буфере, так как по умолчанию static)
  char *count = strtok(NULL, ";");  // возьмём последнее слово в строке

  int c = atoi(count);  // сделаем ASCII в int

  // printf("%s %s %d\n", id, name, c);
  // разбили и теперь можно сделать деталь
  detail *new_det = create_detail(id, name, c);
  // print_detail(new_det);

  free(str_copy);  // очистим память, выделенную под копию строки
  return new_det;  // вернуть новую деталь
}

// преобразовать деталь в строчку для записи в файл
char *detail_to_str(const detail *d) {
  char *s = (char *)calloc(8 + strlen(d->name) + 20 + 2 + 2,
                           sizeof(char));  // count len + ; * 2 + \n + '\0'
  sprintf(s, "%s;%s;%d\n", d->id, d->name, d->count);
  return s;
}

// генерация детали на рандомных значениях
detail *rand_detail() {
  char id[9];
  for (int i = 0; i < 8; i++) {
    id[i] = '0' + rand() % 10;  // с нуля до 9
  }
  id[8] = 0;  // записать в конце терминальный нуль

  int len = rand() % 50 + 5;  // генерация длины от 5 до 54
  char *name = (char *)calloc(
      len + 1, sizeof(char));  // выделение памяти под строчку длиной len()
  for (int i = 0; i < len; i++) {  // добавление в массив букв от a до z
    name[i] = 'a' + rand() % 26;
  }
  name[len] = 0;  // добавить в канце терминальный нуль

  int count = 10 + rand() % 500;  // генерация count от 10 до 509

  return create_detail(
      id, name,
      count);  // вернуть созаднную деталь на основе сгенерированных данных
}

detail **rand_detail_array(int n) {
  detail **arr =
      calloc(n, sizeof(detail *));  // (detail **), потому что массив, выделяем
                                    // память на основе данных о детали
  for (int i = 0; i < n; i++) {
    arr[i] = rand_detail();  // добавить в массив сгенерированную деталь,
                             // генерировать n раз
  }

  return arr;  // вернуть массив из деталей
}

void free_detail_array(detail **arr, int size) {
  if (arr == NULL ||
      size <=
          0) {  // проверить на пустоту массива или на положительность размера
    return;
  }

  for (int i = 0; i < size; i++) {
    free_detail(arr[i]);  // очистить каждую деталь
  }

  free(arr);  // очистить массив
}

void print_detail_array(detail **arr, int size) {
  if (arr == NULL || size <= 0) {
    return;
  }

  for (int i = 0; i < size; i++) {
    print_detail(arr[i]);  // напечатать деталь массива
  }
}

detail **read_details_from_file(int *size, const char *filename) {
  FILE *fp = fopen(filename, "r");  // открыть файл на чтение
  if (fp == NULL) {  // если не удалось это сделать
    // oi oi
    printf("error opening input\n");
    return NULL;  // вернуть null
  }
  char *line = NULL;
  size_t len = 0;

  detail **arr = calloc(
      1,
      sizeof(
          detail *));  // выделить память под массив на основе данных о детали

  if (arr == NULL) {  // если не удалось выделить память, так как не удалось
                      // прочитать детали из файла
    // oi oi
    printf("error calloc in read_details_from_file\n");
    return NULL;
  }

  int arr_capacity = 1;  // сколько вмещвется в массив
  int arr_count = 0;     // подсчёт длины массива

  while (!feof(fp)) {   // если не end of file
    line = getstr(fp);  // прочитать readline'ом строчку
    printf("getline: %s\n", line);  // напечатать
    if (!line || strlen(line) < 3) {
      free(line);  // освободить память под строчку
      continue;
    }
    detail *d = detail_from_str(line);  // сделать из строки деталь
    free(line);  // освободить память под строчку
    if (arr_count + 1 >
        arr_capacity) {  // если длина массива превышает вместимость
      arr_capacity *= 2;  // вместимость увеличить в два раза
      arr = realloc(arr,
                    arr_capacity * sizeof(detail *));  // перевыделить память
    }
    arr[arr_count++] = d;  // записать в массив деталь
  }

  fclose(fp);  // закрыть файл

  arr = realloc(
      arr,
      arr_count * sizeof(detail *));  // fit to the real size (реальный размер)

  *size = arr_count;  // изменить size на реальный размер массива
  return arr;  // вернуть массив
}

int write_to_file(detail **arr, int size, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    // oi oi
    printf("error opening output\n");
    return 1;  // NOT OK
  }

  for (int i = 0; i < size; i++) {
    char *tmp = detail_to_str(arr[i]);
    fprintf(fp, "%s", tmp);
    free(tmp);
  }

  fclose(fp);
  return 0;  // OK
}