//
// Created by W0L1D on 12/31/2021.
//

#include <stdio.h>
#include <stdlib.h>


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

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition_TRapide(int *arr, int low, int high)
{
    int pivot = arr[(low + high)/2]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
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
    int n = 7;
    int arr[7] = {5,9,1,3,7,0,4};

    tri_TRapide(arr, 0, n-1);
}



