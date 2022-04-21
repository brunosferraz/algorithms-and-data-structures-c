/* Recebe um vetor, chave e seu tamanho. Devolve um valor menor ou igual
 a chave, caso contrario devolve 0 */
int binarySearch(int vetor[], int chave, int tam) {
   int imax = tam - 1;
   int imin = 0, imid;
   int primeiroMid = 0;

   while (imin <= imax) {
      imid = imin + ((imax - imin) / 2);

      if (chave == vetor[imid])
         return vetor[imid];
      else if (chave < vetor[imid])
         imax = imid - 1;
      else {
         imin = imid + 1;
         primeiroMid = vetor[imid];
      }
   }

   if (vetor[imid] < chave)
      return vetor[imid];
   else if (primeiroMid < chave)
      return primeiroMid;
   else
      return 0;
}