#include "list.h"

#include <stdio.h>
#include <stdlib.h>

List *list_new() { return (List *)calloc(1, sizeof(List)); }

void list_delete(List *list) {
  Item *ptr = list->head, *ptr_prev;
  while (ptr) {
    ptr_prev = ptr;
    ptr = ptr->next;
    free(ptr_prev);
  }
  free(list);
}

void items_print(const Item *ptr) {
  printf("\"");
  while (ptr) {
    printf("%c", ptr->data);
    ptr = ptr->next;
  }
  printf("\"\n");
}

void list_print(const List *list) {
  printf("\"");
  Item *ptr = list->head;
  while (ptr) {
    printf("%c", ptr->data);
    ptr = ptr->next;
  }
  printf("\"\n");
}

int list_push_back(List *list, char data) {
  if (data == '\t') {
    data = ' ';
  }

  Item *ptr = list->head;

  if (ptr == NULL && data == ' ') {  // !list->head
    return 0;
  }
  Item *new_item = (Item *)malloc(sizeof(Item));

  if (!new_item) {
    return 1;
  }
  new_item->next = NULL;
  new_item->data = data;

  if (ptr == NULL) {
    list->head = new_item;
  } else {
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    if (data == ' ' && ptr->data == ' ') {
      free(new_item);
    } else {
      ptr->next = new_item;
    }
  }

  return 0;
}

void remove_last_space(List *list) {
  Item *ptr = list->head;
  while (ptr && ptr->next && ptr->next->next != NULL) {
    ptr = ptr->next;
  }
  if (ptr && ptr->next && ptr->next->data == ' ') {
    free(ptr->next);
    ptr->next = NULL;
  }
}
