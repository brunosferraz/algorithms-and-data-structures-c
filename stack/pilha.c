#include "pilha.h"

#include <stdlib.h>

void initialize(stack *s) {
   s->top = 0;
}

int empty(stack *s) {
   return (s->top == 0);
}

int full(stack *s) {
   return (s->top == MAX);
}

void push(stack *s, T data) {
   if (!full(s)) {
      s->v[s->top++] = data;
   } else {
      exit(EXIT_FAILURE);
   }
}

int pop(stack *s, T *data) {
   if (!empty(s)) {
      s->top--;
      *data = s->v[s->top];
      return 1;
   } else
      return 0;
}

T top(stack s) {
   if (empty(&s))
      exit(EXIT_FAILURE);
   else
      return s.v[s.top - 1];
}