#ifndef AVL_H
#define AVL_H

struct node_ {
   int data;
   char bal;
   struct node_ *dir, *esq;
};

typedef struct node_ node;

typedef struct {
   node* raiz;
} avl;

// funções públicas

void inicializar(avl* arvore); // inicializa uma árvore já alocada pelo usuário
void destruir(avl* arvore);    // desaloca toda memória alocada pelas funções públicas

void inserir(avl* arvore, int data); // insere data na árvore, sem repetição

int teto(avl* arvore, int dado, int* teto_dado); // Se o teto existir, retorna 1 e em teto_dado o
                                                 // teto de dado. Caso contrário, retorna 0 (falso).
int piso(avl* arvore, int dado, int* piso_dado); // Se o piso existir, retorna 1 e em piso_dado o
                                                 // piso de dado. Caso contrário, retorna 0 (falso).

#endif