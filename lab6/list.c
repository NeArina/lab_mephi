#include "list.h"

#include <stdio.h>
#include <stdlib.h>

// создание нового листа и выделение памяти с заполнением нулями calloc()
List *list_new() { return (List *)calloc(1, sizeof(List)); }

// удаление листа
void list_delete(List *list) {
  Item *ptr = list->head, *ptr_prev;
  while (ptr) {
    ptr_prev = ptr;
    ptr = ptr->next;
    free(ptr_prev);
  }
  free(list);
}
/// печать элементов
void items_print(const Item *ptr) {
  printf("\"");
  // пока ptr не 0
  while (ptr) {
    printf("%c", ptr->data);  // печать элемента
    ptr = ptr->next;          // передвигаем на следующий
  }
  printf("\"\n");
}

/// печать листа
void list_print(const List *list) {
  printf("\"");
  // указатель на начало листа
  Item *ptr = list->head;
  // пока указатель не 0
  while (ptr) {
    // печать значения
    printf("%c", ptr->data);
    // сдвиг указателя на следующее значение
    ptr = ptr->next;
  }
  printf("\"\n");
}

// вставка элемента (вставить новый элемент в конец вектора, который увеличивает
// размер вектора на 1)
int list_push_back(List *list, char data) {
  // если tab, заменить на один пробел
  if (data == '\t') {
    data = ' ';
  }
  // если
  if (data == ' ' && list->tail && list->tail->data == ' ') {
    return 0;
  }
  // выделение памяти для указателя
  Item *ptr = (Item *)malloc(sizeof(Item));

  // если указатель
  if (!ptr) {
    return 1;
  }
  //
  ptr->data = data;
  //
  ptr->next = NULL;
  if (!list->head) {
    list->head = ptr;
    list->tail = ptr;
    ptr->prev = NULL;
  } else {
    list->tail->next = ptr;
    ptr->prev = list->tail;
    list->tail = ptr;
  }
  return 0;
}

// int list_insert(List *list, int data) {
//     Item *ptr = list->head, *ptr_prev = NULL;
//     while (ptr && (ptr->data < data)) {
//         ptr_prev = ptr;
//         ptr = ptr->next;
//     }
//     Item *new = (Item *) malloc(sizeof(Item));
//     if (!new) {
//         return 1;
//     }
//     new->data = data;
//     new->next = ptr;
//     if (ptr_prev) {
//         ptr_prev->next = new;
//     } else {
//         list->head = new;
//     }
//     if (!ptr) {
//         list->tail = new;
//     }
//     return 0;
// }

// int list_remove(List *list, int data) {
//     Item *ptr = list->head, *ptr_prev = NULL;
//     while (ptr && ptr->data != data) {
//         ptr_prev = ptr;
//         ptr = ptr->next;
//     }
//     if (!ptr) {
//         return 1;
//     }
//     if (ptr == list->head) {
//         list->head = ptr->next;
//     }
//     if (ptr == list->tail) {
//         list->tail = ptr_prev;
//     }
//     if (ptr_prev) {
//         ptr_prev->next = ptr->next;
//     }
//     free(ptr);
//     return 0;
// }
