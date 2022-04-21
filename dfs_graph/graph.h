#ifndef GRAPH_H
#define GRAPH_H

#define WHITE 0
#define GRAY  1
#define BLACK 2

typedef struct node {
   int w;
   struct node *next;
} Node;

typedef struct graph {
   int V;
   int A;
   int ciclo;
   int *in, *out, *order;
   Node **adj;
} Graph;

// Inicializa um grafo ja alocado pelo usuario
void inicializar(Graph *G, unsigned nvertices);

// Desaloca toda memoria alocada pelas funcoes publicas
void destroi(Graph *G);

// Adiciona um arco orientado de v para w
void adiciona_arco(Graph *G, unsigned v, unsigned w);

// Calcula a rotulacao e ordem de visita de cada vertice. E tambem a presenca de ciclos.
void dfs(Graph *G);

// Imprime os vertices em ordem de visita.
void imprimir(Graph *G);

// Retorna 1 caso o grafo contenha ciclos, 0 caso contrario.
int ehCiclico(Graph *G);

#endif