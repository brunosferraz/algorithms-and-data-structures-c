// Implementação de Max heap

#include <stdio.h>

#define MAX 20

void swap(int v[], int pai, int filho) {
   int aux = v[pai];
   v[pai] = v[filho];
   v[filho] = aux;
}

void fixDown(int heap[], int k, int heapsize) {
   while (2 * k < heapsize - 1) {
      int j = 2 * k + 1;
      if (j < heapsize - 1 && heap[j] < heap[j + 1])
         j++;
      if (heap[k] >= heap[j])
         break;
      swap(heap, k, j);
      k = j;
   }
}

void heapSort(int v[], int size) {
   for (int i = size / 2; i >= 0; i--)
      fixDown(v, i, size);

   while (size > 1) {
      swap(v, 0, size - 1);
      size--;
      fixDown(v, 0, size);
   }
}

int main() {
   int v[8] = {10, 9, 8, 7, 6, 5, 4, 3};
   heapSort(v, 8);

   for (int i = 0; i < 8; i++) 
      printf("%d ", v[i]);  
}