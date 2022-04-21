#include <stdio.h>

#include "graph.h"

int main() {
   unsigned i, j, vertices;
   Graph g;

   scanf("%u", &vertices);
   inicializar(&g, vertices + 1);

   while (1) {
      scanf("%d,%d", &i, &j);
      if (!i && !j)
         break;
      adiciona_arco(&g, i, j);
   }

   dfs(&g);

   imprimir(&g);

   if (ehCiclico(&g))
      printf("aciclico: nao\n");
   else
      printf("aciclico: sim\n");

   destroi(&g);
}
