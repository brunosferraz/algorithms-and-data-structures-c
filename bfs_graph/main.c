#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct graph {
   int V;
   int A;
   int **adj;
} Graph;

// Inicializa um grafo ja alocado pelo usuario.
void inicializar(Graph *G, unsigned nvertices) {
   G->V = nvertices;
   G->A = 0;
   G->adj = (int **)malloc(sizeof(int *) * G->V);
   for (unsigned v = 0; v < G->V; v++)
      G->adj[v] = (int *)malloc(sizeof(int) * G->V);
}

// Desaloca toda memoria alocada pelas funcoes publicas.
void destroi(Graph *G) {
   for (unsigned v = 0; v < G->V; v++)
      free(G->adj[v]);
   free(G->adj);
   G->V = G->A = 0;
}

// Adiciona um arco nao orientado.
void adiciona_arco(Graph *G, unsigned v, unsigned w) {
   if (G->adj[v][w] == 0 && G->adj[w][v] == 0) {
      G->adj[v][w] = 1;
      G->adj[w][v] = 1;
      G->A++;
   }
}

// Calcula e imprime a distancia de cada vertice a partir do verticeInicial.
void bfs(Graph *G, unsigned verticeInicial) {
   int vis[G->V];
   int distance[G->V];

   for (unsigned v = 0; v < G->V; v++)
      vis[v] = 0;

   queue q;
   initialize(&q);
   push(&q, verticeInicial);
   vis[verticeInicial] = 1;
   distance[verticeInicial] = 0;

   while (!empty(&q)) {
      unsigned v = front(&q);
      pop(&q);
      printf("%u %u\n", v, distance[v]);

      for (unsigned w = 1; w < G->V; w++)
         if (G->adj[v][w] == 1)
            if (vis[w] == 0) {
               vis[w] = 1;
               distance[w] = distance[v] + 1;
               push(&q, w);
            }
   }
   destroy(&q);
}

int main() {
   unsigned i, j, vertices, verticeInicial;
   Graph g;

   scanf("%u", &vertices);
   inicializar(&g, vertices + 1);

   while (1) {
      scanf("%d,%d", &i, &j);
      if (!i && !j)
         break;
      adiciona_arco(&g, i, j);
   }
   scanf("%u", &verticeInicial);

   printf("Origem da busca: %d\n", verticeInicial);
   printf("Vertices alcancados e distancias:\n");
   bfs(&g, verticeInicial);

   destroi(&g);
}
