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


// To tExtracte a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void tExtracte(int *arr, int n, int i)
{
    printf("\n******Start Heapify******\n"
           "n = %d, i = %d ",
           n, i);
    aff_Array(arr, n);
    printf("*****************\n");
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        xchange(arr + i, arr + largest);

        // Recursively tExtracte the affected sub-tree
        tExtracte(arr, n, largest);
    }

    printf("\n******End Heapify******\n"
           "n = %d, i = %d ",
           n, i);
    aff_Array(arr, n);
    printf("*****************\n");
}

// main function to do heap sort
void trie_TExtraction(int *arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        tExtracte(arr, n, i);

    printf("\n******HeapSort******\n"
           "n = %d, i = -1",
           n);
    aff_Array(arr, n);
    printf("*****************\n");
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        xchange(arr, arr + i);


        // call max tExtracte on the reduced heap
        tExtracte(arr, i, 0);

        printf("\n******HeapSort******\n"
               "n = %d, i = %d",
               n, i);
        aff_Array(arr, n);
        printf("*****************\n");
    }
}



void main() {
    int n = 7;
    int arr[7] = {5,9,1,3,7,0,4};

    trie_TExtraction(arr, n);
}



