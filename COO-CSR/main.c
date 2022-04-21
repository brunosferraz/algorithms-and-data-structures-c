#include <stdio.h>
#include <stdlib.h>

#include "csr.h"

int main() {
   int k, max_row = 0;
   int i, j;

   scanf("%d", &k);

   int *v_row = (int *)malloc(k * sizeof(int));
   int *v_col = (int *)malloc(k * sizeof(int));
   int *v_data = (int *)malloc(k * sizeof(int));

   for (int i = 0; i < k; i++) {
      scanf("%d %d %d", &v_row[i], &v_col[i], &v_data[i]);
      if (v_row[i] > max_row)
         max_row = v_row[i];
   }

   int *v_row_csr = (int *)malloc((max_row + 2) * sizeof(int));

   coo_sort(v_row, v_col, v_data, k);
   coo_to_csr(v_row, v_col, v_data, v_row_csr, max_row + 2);

   while (1) {
      scanf("%d %d", &i, &j);
      if (i == -1 && j == -1)
         break;

      printf("(%d,%d) = %d\n", i, j, csr_search(i, j, v_data, v_col, v_row_csr, max_row + 2));
   }

   free(v_row);
   free(v_col);
   free(v_data);
   free(v_row_csr);
}