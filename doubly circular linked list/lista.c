#include "lista.h"

#include <stdlib.h>

void inicializa(lista* l, int (*cmp)(lista_item i1, lista_item i2)) {
   lista_no* n = (lista_no*)malloc(sizeof(lista_no));
   n->ant = n->prox = l->sentinela = n;
   l->quantidade = 0;
   l->compara = cmp;
}

void destroi(lista* l) {
   while (!vazia(l))
      retira(l, elemento(primeiro(l)));
   free(l->sentinela);
}

int vazia(lista* l) {
   return l->sentinela->prox == l->sentinela;
}

void insere(lista* l, lista_item item) {
   lista_no* n = (lista_no*)malloc(sizeof(lista_no));
   n->item = item;

   lista_iterador it;
   for (it = primeiro(l); !acabou(it) && l->compara(elemento(it), item) == -1; proximo(&it))
      ;

   n->prox = it.p;
   n->ant = it.p->ant;
   n->ant->prox = n;
   it.p->ant = n;
   l->quantidade++;
}

void retira(lista* l, lista_item item) {
   lista_iterador it = primeiro(l);

   while (!acabou(it)) {
      if (l->compara(item, elemento(it)) == 0) {
         lista_no* n = it.p;
         n->prox->ant = n->ant;
         n->ant->prox = n->prox;

         proximo(&it);
         free(n);
         l->quantidade--;
      } else
         proximo(&it);
   }
}

lista_iterador primeiro(lista* l) {
   lista_iterador it;
   it.l = l;
   it.p = l->sentinela->prox;
   return it;
}

lista_iterador ultimo(lista* l) {
   lista_iterador it;
   it.l = l;
   it.p = l->sentinela->ant;
   return it;
}

lista_item elemento(lista_iterador i) {
   return i.p->item;
}

int proximo(lista_iterador* i) {
   if (!acabou(*i)) {
      i->p = i->p->prox;
      return 1;
   }
   return 0;
}

int anterior(lista_iterador* i) {
   if (!acabou(*i)) {
      i->p = i->p->ant;
      return 1;
   }
   return 0;
}

int acabou(lista_iterador i) {
   return i.p == i.l->sentinela;
}