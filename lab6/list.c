#include <stdlib.h>
#include <stdio.h>

#include "list.h"

List *list_new() {
    return (List *) calloc(1, sizeof(List));
}

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

    if (data == ' ' && list->tail && list->tail->data == ' ') {
        return 0;
    }

    Item *ptr = (Item *) malloc(sizeof(Item));
    if (!ptr) {
        return 1;
    }
    ptr->data = data;
    ptr->next = NULL;
    if (!list->head) {
        list->head = ptr;
        list->tail = ptr;
    } else {
        list->tail->next = ptr;
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
