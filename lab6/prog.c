#include "list.h"
#include <stdio.h>
#include "input_help.h"

// abcde -> cdeab
Item *get_end(Item *item) {
    if (!item) {
        return NULL;
    } 

    Item *word_start = item;
    while (word_start->next != NULL && word_start->next->data != ' ') {
        word_start = word_start -> next;
    }

    return word_start;
}

Item *next_word(Item *item) {
    if (!item) {
        return NULL;
    }

    Item *word_start = item;
    while (word_start && word_start->data != ' ') {
        word_start = word_start -> next;
    }

    if (!word_start) {
        return NULL;
    }

    return word_start->next; 
}

void task(const List *list, int n) {
    if (!list) {
        return;
    }

     Item *word_start = list->head;

     // skip spaces
     while(word_start && word_start )
        printf("start:");
        items_print(word_start);
        
        Item *tmp = get_end(word_start);
        printf("end:");
        items_print(tmp);
     while ((word_start = next_word(word_start))) {
        printf("start:");
        items_print(word_start);
        
        Item *tmp = get_end(word_start);
        printf("end:");
        items_print(tmp);
     }
}

int main() {
    int n;
    input_int(&n, 0, 1000, "Input N:");

    List *list = list_new();
    
    char c;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            list_print(list);
            task(list, n);
            //list_print(list);
            list_delete(list);
            list = list_new();
        } else {
            list_push_back(list, c);
        }
    }

    
    



    // List *l = list_new();
    // list_insert(l, 10);
    // list_print(l);
    // list_insert(l, 20);
    // list_print(l);
    // list_insert(l, 30);
    // list_print(l);
    // list_push_back(l, 40);
    // list_print(l);
    // list_insert(l, 35);
    // list_print(l);
    // list_insert(l, 5);
    // list_print(l);
    // list_remove(l, 20);
    // list_print(l);
    // list_push_back(l, 45);
    // list_print(l);
     list_delete(list);
    return 0;
}
