#ifndef LIST_H
#define LIST_H

typedef struct Item {
    char data;
    struct Item *next;
    struct Item *prev;
} Item;

typedef struct List {
    Item *head;
    Item *tail;
} List;

List *list_new();

void list_delete(List *list);

void list_print(const List *list);

void items_print(const Item *ptr);

int list_push_back(List *list, char data);

// int list_insert(List *list, char data);

// int list_remove(List *list, char data);

#endif
