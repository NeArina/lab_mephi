#include <stdio.h>

#include "input_help.h"
#include "list.h"

Item *rotate(List *list, Item *pre, Item *start, Item *end, int n) {
  int length = 1;
  Item *current = start;
  while (current != end) {
    current = current->next;
    length++;
  }

  int d = n % length;  // normalaise n so that 0 <= n < length now
  if (d == 0) {
    return end;
  }
  // pre -> start -> ... -> x -> y -> ... -> end -> z -> ...
  // pre -> y -> ... -> end -> start -> ... -> x -> z -> ...
  Item *x = start;
  Item *z = end->next;

  while (--d > 0) {
    x = x->next;
  }
  Item *y = x->next;

  if (pre) {
    pre->next = y;
  } else {
    list->head = y;
  }
  end->next = start;
  x->next = z;

  return x;
}

void mytask(List *list, int n) {
  Item *pre = NULL;
  Item *start = list->head;
  Item *end = NULL;

  // empty list
  if (!start) {
    return;
  }

  // // if first char is a space
  // if (start->data == ' ') {
  //   pre = start;
  //   start = start->next;
  // }

  end = start;
  while (end->next && end->next->data != ' ') {
    end = end->next;
  }

  // do the rotation
  end = rotate(list, pre, start, end, n);

  while (end->next && end->next->next) {
    pre = end->next;  // next space
    start = pre->next;
    end = start;
    while (end->next && end->next->data != ' ') {
      end = end->next;
    }
    // do the task
    end = rotate(list, pre, start, end, n);
  }
}

int main() {
  int n;

  int res = input_int(&n, 0, 1000, "Input N:");
  if (res == EOF) {
    return 0;
  }

  List *list = list_new();
  char c;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      remove_last_space(list);
      list_print(list);
      mytask(list, n);
      list_print(list);
      list_delete(list);
      list = list_new();
      res = input_int(&n, 0, 1000, "Input N:");
      if (res == EOF) {
        break;
      }
    } else {
      list_push_back(list, c);
    }
  }
  list_delete(list);
  return 0;
}
