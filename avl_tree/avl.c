#include "avl.h"

#include <stdlib.h>

void inicializar(avl* arvore) {
   arvore->raiz = 0;
}

void destruir_privado(node* p) {
   if (p) {
      destruir_privado(p->esq);
      destruir_privado(p->dir);
      free(p);
   }
}

void destruir(avl* arvore) {
   destruir_privado(arvore->raiz);
}

node* rotEE(node* A) {
   node* B = A->esq;
   A->esq = B->dir;
   B->dir = A;
   A->bal = 0;
   B->bal = 0;
   return B;
}

node* rotDD(node* A) {
   node* B = A->dir;
   A->dir = B->esq;
   B->esq = A;
   A->bal = 0;
   B->bal = 0;
   return B;
}

node* rotED(node* A) {
   node* B = A->esq;
   node* C = B->dir;
   B->dir = C->esq;
   C->esq = B;
   A->esq = C->dir;
   C->dir = A;
   if (C->bal == -1) {
      A->bal = 1;
      B->bal = 0;
      C->bal = 0;
   } else if (C->bal == 1) {
      A->bal = 0;
      B->bal = -1;
      C->bal = 0;
   } else {
      A->bal = 0;
      B->bal = 0;
   }
   return C;
}

node* rotDE(node* A) {
   node* B = A->dir;
   node* C = B->esq;
   B->esq = C->dir;
   C->dir = B;
   A->dir = C->esq;
   C->esq = A;
   if (C->bal == -1) {
      A->bal = 0;
      B->bal = 1;
      C->bal = 0;
   } else if (C->bal == 1) {
      A->bal = -1;
      B->bal = 0;
      C->bal = 0;
   } else {
      A->bal = 0;
      B->bal = 0;
   }
   return C;
}

node* inserir_privado(node* p, int data, int* mudouAltura) {
   if (!p) {
      node* novo = (node*)malloc(sizeof(node));
      novo->data = data;
      novo->bal = 0;
      novo->dir = novo->esq = 0;
      *mudouAltura = 1;
      return novo;
   } else if (data < p->data) {
      p->esq = inserir_privado(p->esq, data, mudouAltura);
      if (*mudouAltura)
         p->bal -= 1;
   } else if (data > p->data) {
      p->dir = inserir_privado(p->dir, data, mudouAltura);
      if (*mudouAltura)
         p->bal += 1;
   } else
      return p;

   if (*mudouAltura) {
      if (p->bal == 0)
         *mudouAltura = 0;

      if (p->bal == -2) {
         *mudouAltura = 0;
         if (p->esq && p->esq->bal == -1)
            return rotEE(p);
         if (p->esq && p->esq->bal == 1)
            return rotED(p);
      }

      if (p->bal == 2) {
         *mudouAltura = 0;
         if (p->dir && p->dir->bal == 1)
            return rotDD(p);
         if (p->dir && p->dir->bal == -1)
            return rotDE(p);
      }
   }
   return p;
}

void inserir(avl* arvore, int data) {
   int mudouAltura = 0;

   arvore->raiz = inserir_privado(arvore->raiz, data, &mudouAltura);
}

node* max(node* p) {
   if (!p->dir)
      return p;
   else
      return max(p->dir);
}

node* rotEEremove(node* B, int* mudouAltura) {
   node* A = B->esq;
   B->esq = A->dir;
   A->dir = B;
   if (A->bal == 0) {
      A->bal = 1;
      B->bal = -1;
      *mudouAltura = 0;
   } else { // A->bal == -1
      A->bal = 0;
      B->bal = 0;
      *mudouAltura = 1;
   }
   return A;
}

node* rotDDremove(node* B, int* mudouAltura) {
   node* A = B->dir;
   B->dir = A->esq;
   A->esq = B;
   if (A->bal == 0) {
      A->bal = -1;
      B->bal = 1;
      *mudouAltura = 0;
   } else { // b->>bal == -1
      A->bal = 0;
      B->bal = 0;
      *mudouAltura = 1;
   }
   return A;
}

node* rotEDremove(node* A, int* mudouAltura) {
   *mudouAltura = 1;
   return rotED(A);
}

node* rotDEremove(node* A, int* mudouAltura) {
   *mudouAltura = 1;
   return rotDE(A);
}

node* remover_privado(node* p, int data, int* mudouAltura) {
   if (p) {
      if (data < p->data) {
         p->esq = remover_privado(p->esq, data, mudouAltura);
         if (*mudouAltura)
            p->bal += 1;
      } else if (data > p->data) {
         p->dir = remover_privado(p->dir, data, mudouAltura);
         if (*mudouAltura)
            p->bal -= 1;
      } else {
         if (!p->dir) {
            node* novo = p->esq;
            free(p);
            *mudouAltura = 1;
            return novo;
         } else if (!p->esq) {
            node* novo = p->dir;
            free(p);
            *mudouAltura = 1;
            return novo;
         } else {
            node* novo = max(p->esq);
            p->data = novo->data;
            p->esq = remover_privado(p->esq, novo->data, mudouAltura);
            if (*mudouAltura)
               p->bal += 1;
         }
      }
   }

   if (*mudouAltura) {
      if (p->bal == -2) {
         if (p->esq && p->esq->bal == 1)
            return rotEDremove(p, mudouAltura);
         else
            return rotEEremove(p, mudouAltura);
      }

      if (p->bal == 2) {
         if (p->dir && p->dir->bal == -1)
            return rotDEremove(p, mudouAltura);
         else
            return rotDDremove(p, mudouAltura);
      }

      if (p->bal != 0)
         *mudouAltura = 0;
   }

   return p;
}

void remover(avl* arvore, int data) {
   int mudouAltura = 0;

   arvore->raiz = remover_privado(arvore->raiz, data, &mudouAltura);
}

node* teto_privado(node* p, int dado) {
   if (!p) {
      return NULL;
   } else if (dado < p->data) {
      node* n = teto_privado(p->esq, dado);
      if (n)
         return n;
      else
         return p;
   } else if (dado > p->data)
      return teto_privado(p->dir, dado);
   else
      return p;
}

node* piso_privado(node* p, int dado) {
   if (!p) {
      return NULL;
   } else if (dado < p->data)
      return piso_privado(p->esq, dado);
   else if (dado > p->data) {
      node* n = piso_privado(p->dir, dado);
      if (n)
         return n;
      else
         return p;
   } else
      return p;
}

int teto(avl* arvore, int dado, int* teto_dado) {
   node* c = teto_privado(arvore->raiz, dado);
   if (c) {
      *teto_dado = c->data;
      return 1;
   }
   return 0;
}

int piso(avl* arvore, int dado, int* piso_dado) {
   node* f = piso_privado(arvore->raiz, dado);
   if (f) {
      *piso_dado = f->data;
      return 1;
   }
   return 0;
}
