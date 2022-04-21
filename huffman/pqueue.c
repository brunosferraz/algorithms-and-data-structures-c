#include "pqueue.h"

#include <stdio.h>

void initialize(pqueue *q, int (*menor_igual_maior)(Item i1, Item i2)) {
   q->size = 0;
   q->menor_igual_maior = menor_igual_maior;
}

void swap(pqueue *q, int pai, int filho) {
   void *aux = q->array[pai];
   q->array[pai] = q->array[filho];
   q->array[filho] = aux;
}

void fixUp(pqueue *q, int k) {
   while (k > 0 && q->menor_igual_maior(q->array[k / 2], q->array[k]) == 1) {
      swap(q, k, k / 2);
      k = k / 2;
   }
}

void fixDown(pqueue *q, int k) {
   while (2 * k <= q->size - 1) {
      int j = 2 * k;
      if (j < q->size - 1 && q->menor_igual_maior(q->array[j], q->array[j + 1]) == 1)
         j++;
      if (q->menor_igual_maior(q->array[k], q->array[j]) <= 0)
         break;
      swap(q, k, j);
      k = j;
   }
}

void insert(pqueue *q, void *data) {
   q->array[q->size++] = data;
   fixUp(q, q->size - 1);
}

void *removeMin(pqueue *q) {
   void *data = q->array[0];
   swap(q, 0, --q->size);
   fixDown(q, 0);
   return data;
}

int size(pqueue *q) {
   return q->size;
}
