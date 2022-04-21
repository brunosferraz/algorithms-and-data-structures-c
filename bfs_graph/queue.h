#ifndef QUEUE_H
#define QUEUE_H

typedef int T;

typedef struct qnode_ {
   T data;
   struct qnode_ *next;
} qnode;

typedef struct {
   unsigned size;
   qnode *first, *last;
} queue;

void initialize(queue *q);

void destroy(queue *q);

T front(queue *q);

void push(queue *q, T data);

void pop(queue *q);

int empty(queue *q);

#endif