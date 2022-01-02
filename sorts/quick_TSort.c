//
// Created by W0L1D on 12/31/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>




void xchange(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void aff_Array(int *arr, int n)
{
    //Tableau n'existe pas
    if (!arr) return;

    int i;
    printf("\n");
    for(i = 0; i < n; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}


/**********************************************************************
 * place l'élément de pivot à sa position correcte dans un tableau trié,
 * et place tous plus petit (plus petit que pivot) à gauche du pivot
 * et tous les grands éléments à droite de pivot
 * @param arr tableau des element
 * @param low indice du premier du element
 * @param high indice du dernier du element
 * @return position du pivot
 */
int partition_TRapide(int *arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    // indice du petit element et indique la position correct du pivot
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        // si l'element courant est < au pivot
        if (arr[j] < pivot)
        {
            i++; // incrementer l'indice de l'element inferieur
            xchange(arr + i, arr + j);
        }
    }
    xchange(arr + i + 1, arr + high);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void tri_TRapide(int *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition_TRapide(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        tri_TRapide(arr, low, pi - 1);
        tri_TRapide(arr, pi + 1, high);
    }
}


void main() {
    int n = 96;
    int arr[96] = {5,9,1,3,7,0,4, 8,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0,
                   1,7, 6, 5, 6, 3, 7, 0};



    clock_t t;
    t = clock();


    clock_t tic = clock();

    tri_TRapide(arr, 0, n-1);

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    aff_Array(arr, n);
//    t = clock() - t;
//    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//
//    printf("\n\ntime token %f, %ld.\n", time_taken, t);

}



