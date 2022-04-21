#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node_ {
   int data;
   struct node_ *dir, *esq;
   unsigned size;
} node;

node *inserir(node *p, int dados) {
   if (!p) {
      node *n = (node *)malloc(sizeof(node));
      n->data = dados;
      n->dir = n->esq = NULL;
      n->size = 1;
      return n;
   } else if (dados < p->data) {
      p->esq = inserir(p->esq, dados);
   } else if (dados > p->data) {
      p->dir = inserir(p->dir, dados);
   } else
      p->data = dados;

   // Tamanho da subarvore
   p->size = 1;
   if (p->dir)
      p->size += p->dir->size;
   if (p->esq)
      p->size += p->esq->size;

   return p;
}
node *max_node(node *p) {
   if (!p->dir)
      return p;
   else
      return max_node(p->dir);
}

node *min_node(node *p) {
   if (!p->esq)
      return p;
   else
      return min_node(p->esq);
}

void destruir(node *p) {
   if (p) {
      destruir(p->esq);
      destruir(p->dir);
      free(p);
   }
   return;
}

void pos_order(node *p, void (*process)(int dado)) {
   if (p) {
      pos_order(p->esq, process);
      pos_order(p->dir, process);
      process(p->data);
   }
   return;
}

void pre_order(node *p, void (*process)(int dado)) {
   if (p) {
      process(p->data);
      pre_order(p->esq, process);
      pre_order(p->dir, process);
   }
   return;
}

void in_order(node *p, void (*process)(int dado)) {
   if (p) {
      in_order(p->esq, process);
      process(p->data);
      in_order(p->dir, process);
   }
   return;
}

node *remove_no(node *p, int dados) {
   if (!p)
      return NULL;
   else if (dados < p->data)
      p->esq = remove_no(p->esq, dados);
   else if (dados > p->data)
      p->dir = remove_no(p->dir, dados);
   else {
      if (!p->dir) {
         node *n = p->esq;
         free(p);
         return n;
      } else if (!p->esq) {
         node *n = p->dir;
         free(p);
         return n;
      } else {
         node *n = max_node(p->esq);
         p->data = n->data;
         p->esq = remove_no(p->esq, n->data);
         return p;
      }
   }

   p->size = 1;
   if (p->dir)
      p->size += p->dir->size;
   if (p->esq)
      p->size += p->esq->size;

   return p;
}

void in_level(node *p, void (*process)(int dado)) {
   if (p) {
      queue q;
      initialize(&q);
      push(&q, p);
      while (!empty(&q)) {
         p = front(&q);
         process(p->data);
         pop(&q);

         if (p->esq)
            push(&q, p->esq);
         if (p->dir)
            push(&q, p->dir);
      }
      destroy(&q);
   }
}

void print(int dado) {
   printf(" %d", dado);
}

node *floor_no(node *p, int dado) {
   if (!p) {
      return NULL;
   } else if (dado < p->data)
      return floor_no(p->esq, dado);
   else if (dado > p->data) {
      node *n = floor_no(p->dir, dado);
      if (n)
         return n;
      else
         return p;
   } else
      return p;
}

node *ceiling_no(node *p, int dado) {
   if (!p) {
      return NULL;
   } else if (dado < p->data) {
      node *n = ceiling_no(p->esq, dado);
      if (n)
         return n;
      else
         return p;
   } else if (dado > p->data)
      return ceiling_no(p->dir, dado);
   else
      return p;
}
unsigned size(node *p) {
   if (p)
      return p->size;
   return 0;
}

node *select_node(node *p, unsigned k) {
   if (!p)
      return 0;
   unsigned t = size(p->esq);
   if (t > k)
      return select_node(p->esq, k);
   else if (t < k)
      return select_node(p->dir, k - t - 1);
   else
      return p;
}

int rank_node(int dado, node *p) {
   if (!p)
      return -1;
   else if (p->data > dado)
      return rank_node(dado, p->esq);
   else if (p->data < dado)
      return size(p->esq) + rank_node(dado, p->dir) + 1;
   else
      return size(p->esq);
}

int main() {
   int n, a;
   int dado = 7;
   scanf("%d", &n);

   node *raiz = NULL;

   for (int i = 0; i < n; i++) {
      scanf("%d", &a);
      raiz = inserir(raiz, a);
   }

   in_level(raiz, print);
   printf("\n");

   printf("Size: %d\n", raiz->size);
   // raiz = remove_no(raiz, 15);
   printf("Size: %d\n", raiz->size);
   // raiz = remove_no(raiz, 0);
   printf("Size: %d\n", raiz->size);

   printf("rank_node:%d \n", rank_node(11, raiz));

   destruir(raiz);

   return 0;
}