#include "list.h"
#include <stdio.h>
#include "input_help.h"

Item *get_end(Item *item, int *len) {
    *len = 1;
    // если значения нет, вернём null
    if (!item) {
        return NULL;
    }
    // 
    Item *word_start = item;
    while (word_start->next != NULL && word_start->next->data != ' ') {
        word_start = word_start->next;
        (*len)++;
    }
    return word_start;
}

Item *next_word(Item *item, int first_call) {
    if (!item) {
        return NULL;
    }

    if (first_call && item && item->data != ' ') {
        return item;
    }

    Item *word_start = item;
    while (word_start && word_start->data != ' ') {
        word_start = word_start->next;
    }

    if (!word_start) {
        return NULL;
    }

    return word_start->next;
}

Item *rotate_n(List *list, Item *start, Item *end, int len, int n) {
    // расчёт значения, на которое сдвигаем список
    n = n % len; // len 99, n = 100 -> n = 1
    
    // если n == 0, то сдвига нет
    if (n == 0) {
        return start;
    }
    
    // присваиваем текущему указателю значение, с которого будет сдвиг
    Item *current = start;
    // уменьшаем n и пока оно не ноль, идём по списку 
    while (n-- > 0) {
        current = current -> next;
    }

    current->prev->next = end->next;

    Item *before_start = start->prev;

    if (start->prev == NULL) {
        list->head = current;
    } else {
        start->prev->next = current;
    }
    start->prev = end;

    if (end->next == NULL) {
        list->tail = current->prev;
    } else {
        end->next->prev = current->prev;
    }
    end->next = start;
    current->prev = before_start;

    return current;
}

void task( List *list, int n) {
    if (!list) {
        return;
    }

    Item *word_start = list->head;
    int len = 0;

    int first_call = 1;
    while ((word_start = next_word(word_start, first_call))) {
        first_call = 0;
        //printf("start:");
        //items_print(word_start);

        Item *tmp = get_end(word_start, &len);
        //printf("%d end:", len);


        //items_print(tmp);
        word_start = rotate_n(list, word_start, tmp, len, n);
        //list_print(list);
    }
}

int main() {
    int n;
    List *list = list_new();
    char c;
    input_int(&n, 0, 1000, "Input N:");
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            list_print(list);
            task(list, n);
            list_print(list);

            list_delete(list);
            list = list_new();
            // input_int(&n, 0, 1000, "Input N:");
        } else {
            list_push_back(list, c);
        }
    }
    list_delete(list);
    return 0;
}
