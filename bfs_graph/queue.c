#include "queue.h"

#include <stdlib.h>

void initialize(queue *q) {
   q->first = q->last = NULL;
}

void destroy(queue *q) {
   while (!empty(q))
      pop(q);
}

T front(queue *q) {
   if (!empty(q))
      return q->first->data;
   return 0;
}

void push(queue *q, T data) {
   qnode *n = (qnode *)malloc(sizeof(qnode));
   n->data = data;
   n->next = NULL;

   if (q->last)
      q->last->next = n;
   else
      q->first = n;
   q->last = n;
}

void pop(queue *q) {
   if (!empty(q)) {
      qnode *n = q->first;
      q->first = n->next;
      free(n);

      if (q->first == NULL)
         q->last = NULL;
   }
}

int empty(queue *q) {
   return q->first == 0;
}