#include <stdio.h>
#include <string.h>

#include "lista.h"

int compare(lista_item i1, lista_item i2) {
   if (i1 < i2)
      return -1;
   else if (i1 > i2)
      return 1;
   else
      return 0;
}

int main() {
   lista l;
   char comando[12];
   char e[2];

   inicializa(&l, compare);

   while (scanf("%s", comando) != EOF) {
      if (strcmp(comando, "insere") == 0) {
         scanf("%s", e);
         insere(&l, e[0]);
      } else if (strcmp(comando, "remove") == 0) {
         scanf("%s", e);
         retira(&l, e[0]);
      } else if (strcmp(comando, "crescente") == 0) {
         if (vazia(&l))
            printf("vazia\n");
         else {
            lista_iterador it = primeiro(&l);
            printf("%c", elemento(it));
            proximo(&it);
            while (!acabou(it)) {
               printf(" %c", elemento(it));
               proximo(&it);
            }
            printf("\n");
         }
      } else if (strcmp(comando, "decrescente") == 0) {
         if (vazia(&l))
            printf("vazia\n");
         else {
            lista_iterador it = ultimo(&l);
            printf("%c", elemento(it));
            anterior(&it);
            while (!acabou(it)) {
               printf(" %c", elemento(it));
               anterior(&it);
            }
            printf("\n");
         }
      }
   }

   destroi(&l);

   return 0;
}