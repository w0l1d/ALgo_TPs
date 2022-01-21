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

    printf("\nDEBUT partition : ");
    printf("\npivot = %d, debut = %d, fin = %d", pivot, low, high);
    aff_Array(arr, high+1);

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

    printf("\nFIN partition : ");
    printf("\npivot = %d", i+1);
    aff_Array(arr, high+1);

    return (i + 1);
}


/**********************************************************************
 * la fonction principal du trie rapide
 * @param arr tableau des element a trie
 * @param low indice du premier du element
 * @param high indice du dernier du element
 * @return rien
 */
void tri_TRapide(int *arr, int low, int high)
{
    if (low < high)
    {

        printf("\nDEBUT fonction principal TRapide()\n");
        printf("debut = %d, fin = %d\n", low, high);
        aff_Array(arr, high+1);

        //pi est l'indice du pivot
        // arr[pi] est dans l'emplacement correct
        int pi = partition_TRapide(arr, low, high);

        // trie separement les elements
        tri_TRapide(arr, low, pi - 1);
        tri_TRapide(arr, pi + 1, high);

        printf("\nFIN fonction principal TRapide()\n");
        printf("debut = %d, fin = %d", low, high);
        aff_Array(arr, high+1);

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


    clock_t tic = clock();

    tri_TRapide(arr, 0, n-1);

    clock_t toc = clock();

    printf("\n\nElapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);



}



