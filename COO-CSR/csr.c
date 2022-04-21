#include "csr.h"

#include <stdio.h>

void swap(int v[], int i, int j) {
   int aux = v[i];
   v[i] = v[j];
   v[j] = aux;
}

void fixDown(int v_row[], int v_col[], int v_data[], int k, int size) {
   while (2 * k < size - 1) {
      int j = 2 * k + 1;
      if (j < size - 1 && v_row[j] < v_row[j + 1])
         j++;
      if (v_row[k] >= v_row[j])
         break;
      swap(v_row, k, j);
      swap(v_col, k, j);
      swap(v_data, k, j);
      k = j;
   }
}
void coo_sort(int v_row[], int v_col[], int v_data[], int size) {
   for (int i = size / 2; i >= 0; i--)
      fixDown(v_row, v_col, v_data, i, size);

   while (size > 1) {
      swap(v_row, 0, size - 1);
      swap(v_col, 0, size - 1);
      swap(v_data, 0, size - 1);
      size--;
      fixDown(v_row, v_col, v_data, 0, size);
   }
}

void coo_to_csr(int v_row[], int v_col[], int v_data[], int v_row_csr[], int max_row) {
   v_row_csr[0] = 0;
   int pos = 0;

   for (int row = 1; row < max_row; row++) {
      int qtd = 0;
      for (int j = pos; v_row[j] == row - 1; j++) {
         qtd++;
         pos++;
      }
      v_row_csr[row] = v_row_csr[row - 1] + qtd;
   }
}

int csr_search(int i, int j, int v_data[], int v_col[], int v_row_csr[], int size) {
   if (i >= size - 1 || v_row_csr[i] == v_row_csr[i + 1])
      return 0;

   for (int k = v_row_csr[i]; k < v_row_csr[i + 1]; k++)
      if (v_col[k] == j)
         return v_data[k];

   return 0;
}
