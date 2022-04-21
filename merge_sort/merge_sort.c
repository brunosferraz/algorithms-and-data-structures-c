#include <stdio.h>

// Funcao auxiliar do merge sort
void merge(int vetor[], int aux[], int imin, int imid, int imax) {
   for (int i = imin; i <= imax; i++)
      aux[i] = vetor[i];

   int i = imin, j = imid + 1, k = imin;

   while (i <= imid && j <= imax) {
      if (aux[i] < aux[j])
         vetor[k++] = aux[i++];
      else
         vetor[k++] = aux[j++];
   }

   while (i <= imid)
      vetor[k++] = aux[i++];
   while (j <= imax)
      vetor[k++] = aux[j++];
}

// Recebe um vetor, vetor auxiliar, indice minimo e maximo. Ordena por merge sort
void mergeSort(int vetor[], int aux[], int imin, int imax) {
   if (imin >= imax)
      return;

   int imid = imin + ((imax - imin) / 2);

   mergeSort(vetor, aux, imin, imid);
   mergeSort(vetor, aux, imid + 1, imax);

   merge(vetor, aux, imin, imid, imax);
}