#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void inicializar(Graph *G, unsigned nvertices) {
   G->V = nvertices;
   G->A = 0;
   G->ciclo = 0;
   G->adj = (Node **)malloc(sizeof(Node *) * G->V);
   G->in = (int *)malloc(sizeof(int) * G->V);
   G->out = (int *)malloc(sizeof(int) * G->V);
   G->order = (int *)malloc(sizeof(int) * G->V);

   for (unsigned v = 0; v < G->V; v++) {
      G->adj[v] = NULL;
      G->in[v] = 0;
      G->out[v] = 0;
      G->order[v] = 0;
   }
}

void destroi(Graph *G) {
   for (unsigned v = 0; v < G->V; v++) {
      while (G->adj[v]) {
         Node *l = G->adj[v];
         G->adj[v] = G->adj[v]->next;
         free(l);
      }
   }
   free(G->adj);
   free(G->in);
   free(G->out);
   free(G->order);
   G->V = G->A = 0;
}

void imprimir(Graph *G) {
   for (unsigned v = 1; v < G->V; v++)
      printf("%d [%d,%d]\n", G->order[v], G->in[G->order[v]], G->out[G->order[v]]);
}

int ehCiclico(Graph *G) {
   return G->ciclo;
}

void adiciona_arco(Graph *G, unsigned v, unsigned w) {
   Node *l = (Node *)malloc(sizeof(Node));
   l->w = w;
   l->next = G->adj[v];
   G->adj[v] = l;
   G->A++;
}

void dfs_private(Graph *G, int vis[], unsigned v, int *time, int *count) {
   G->in[v] = ++*time;
   G->order[++*count] = v;
   vis[v] = GRAY;

   for (Node *n = G->adj[v]; n != NULL; n = n->next) {
      if (vis[n->w] == GRAY)
         G->ciclo = 1;
      if (vis[n->w] == WHITE)
         dfs_private(G, vis, n->w, time, count);
   }

   vis[v] = BLACK;
   G->out[v] = ++*time;
}

void dfs(Graph *G) {
   int vis[G->V];
   int time = 0, count = 0;

   for (unsigned v = 1; v < G->V; v++)
      vis[v] = WHITE;
   for (unsigned v = 1; v < G->V; v++)
      if (vis[v] == WHITE)
         dfs_private(G, vis, v, &time, &count);
}
