#include <stdio.h>

void swap(int v[], int i, int j) {
   int temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

int partition(int arr[], int imin, int imax) {
   int i = imin,

       j = imax + 1;

   while (1) {
      while (arr[++i] < arr[imin])
         if (i == imax)
            break;

      while (arr[imin] < arr[--j])
         if (j == imin)
            break;

      if (i >= j)
         break;
      swap(arr, i, j);
   }
   swap(arr, imin, j);

   return j;
}

void quicksort(int arr[], int imin, int imax) {
   if (imax <= imin)
      return;
   int i = partition(arr, imin, imax);
   quicksort(arr, imin, i - 1);
   quicksort(arr, i + 1, imax);
}
