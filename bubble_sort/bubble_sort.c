void swap(int v[], int i, int j) {
   int temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

void bubble(int vetor[], int n) {
   int trocou;
   int i = 0;
   do {
      trocou = 0;
      for (int j = n - 1; j > i; j--) {
         if (vetor[j - 1] > vetor[j]) {
            swap(vetor, j - 1, j);
            trocou = 1;
         }
      }
      i++;
   } while (trocou && i < n);
}