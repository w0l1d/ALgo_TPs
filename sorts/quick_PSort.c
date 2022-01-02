//
// Created by W0L1D on 12/31/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>




typedef struct cel {
    int val;
    struct cel *svt;
}Cellule;


typedef struct flist {
    Cellule *first;
    Cellule *last;
}FList;

Cellule * getCel(Cellule *list, int pos) {
    while (list) {
        if(pos-- == 1)
            return ((Cellule*) list);
        list = list->svt;
    }
    return ((Cellule*) NULL);
}


void xchange(Cellule* a, Cellule *b) {
    int tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}



Cellule *createCel(int val) {
    Cellule *ne = NULL;
    ne = (Cellule*) malloc(sizeof(Cellule));
    if (!ne) {
        printf("\nErreur d'allocation de memoire\n");
        exit(-1);
    }
    ne->val = val;
    ne->svt = NULL;
    return ((Cellule*) ne);
}

Cellule *insert_arrayToList(Cellule *list, int *array, unsigned int n) {

    // si le tableau des valeur est vide
    if (!n)     return ((Cellule*) list);

    int i = 0;
    if (!list)
        list = createCel(array[i++]);

    Cellule *curr = list;

    //deplacer a la fin de la liste pour inserer en queue
    while(curr->svt)     curr=curr->svt;



    for (; i < n; ++i) {
        curr->svt = createCel(array[i]);
        curr = curr->svt;
    }
    return ((Cellule*) list);
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
Cellule* partition_PRapide(Cellule *list, Cellule *pivot)
{
    if (!list)
        return ((Cellule*) pivot);

    if (!(list->svt)) {
        if (list->val > pivot->val)
            pivot->svt = list;
        else {
            list->svt = pivot;
            pivot = list;
        }
        return ((Cellule*) pivot);
    }

    Cellule *curr = list;
    Cellule *l1, *l2, *tmp;
    l1 = l2 = NULL;
    while(curr) {
        if (pivot->val > curr->val) {
            tmp = l1;
            l1 = curr;
            curr = curr->svt;
            l1->svt = tmp;
        } else {
            tmp = l2;
            l2 = curr;
            curr = curr->svt;
            l2->svt = tmp;
        }
    }

    if (!l1) {
        l1 = pivot;
        goto trait_l2;
    }

    tmp = l1->svt;
    l1->svt = NULL;

    l1 = partition_PRapide(tmp, l1);
    if (!l1) {
        l1 = pivot;
        goto trait_l2;
    }
    curr = l1;
    while(curr->svt)
        curr = curr->svt;

    curr->svt = pivot;

    trait_l2:
    if (!l2)
        goto end_prog;
    tmp = l2->svt;
    l2->svt = NULL;
    l2 = partition_PRapide(tmp, l2);

    end_prog:
    pivot->svt = l2;
    return ((Cellule*) l1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
Cellule* tri_PRapide(Cellule* list)
{
    if (list)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        Cellule *tmp = list->svt;
        list->svt = NULL;
        list = partition_PRapide(tmp, list);
    }
    return ((Cellule*) list);
}

void aff_List(Cellule *list) {
    //Tableau n'existe pas
    if (!list) printf("\nListe est vide\n");

    printf("\n");
    while (list) {
        printf("%d  ", list->val);
        list = list->svt;
    }
    printf("\n");
}
void main() {
    int n = 8;
    int arr[8] = {5,9,1,3,7,0,4, 8,};


    Cellule *list = NULL;
    list = insert_arrayToList(list, arr, n);

    clock_t tic = clock();

    aff_List(list);
    printf("\n\n");
    list = tri_PRapide(list);

    aff_List(list);
    printf("\n\n");
    clock_t toc = clock();

    printf("Elapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);


}



