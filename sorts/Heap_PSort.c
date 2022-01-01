//
// Created by W0L1D on 12/31/2021.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct cel {
    int val;
    struct cel *svt;
}Cellule;


Cellule * getCel(Cellule *list, int pos) {
    while (list) {
        if(pos-- == 1)
            return ((Cellule*) list);
        list = list->svt;
    }
    return ((Cellule*) NULL);
}

/*void xchange(Cellule *list, int a, int b) {
    Cellule *aCel = getCel(list, a),
            *bCel = getCel(list, b);
    int tmp = aCel->val;
    aCel->val = bCel->val;
    bCel->val = tmp;
}*/

void xchange(Cellule* a, Cellule *b) {
    int tmp = a->val;
    a->val = b->val;
    b->val = tmp;
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
void aff_List2(Cellule *list, int n) {
    //Tableau n'existe pas
    if (!list) printf("\nListe est vide\n");

    printf("\n");
    while (list && n--) {
        printf("%d  ", list->val);
        list = list->svt;
    }
    printf("\n");
}


// To tExtracte a subtree rooted with node i which is
// an index in arr[]. n is size of heap
/*******
 *
 * @param list
 * @param n
 * @param i
 */
void lExtracte(Cellule *list, int n, int i) {
    printf("\n******Start Heapify******\n"
           "n = %d, i = %d ",
           n, i);
    aff_List2(list, n);
    printf("*****************\n");



    int largest = i; // Initialize largest as root
    int l = 2 * i; // left = 2*i
    int r = 2 * i + 1; // right = 2*i + 1


    if (l > (n+1) && r > (n+1))
        return;

    // Recursively lExtracte the affected sub-tree
    if (l < (n+1))
        lExtracte(list, n, l);
    if (r < (n+1))
        lExtracte(list, n, r);


    Cellule *largestCel = getCel(list, largest);

    // If left child is larger than root
    Cellule * leftCel= getCel(list, l);
    if (l < (n+1) && leftCel->val > largestCel->val) {
        largest = l;
        largestCel = leftCel;
    }

    // If right child is larger than largest so far
    Cellule *rightCel= getCel(list, r);
    if (r < (n+1) &&  rightCel->val > largestCel->val) {
        largest = r;
        largestCel = rightCel;
    }
    // If largest is not root
    if (largest != i) {
        xchange(getCel(list, i), largestCel);
    }

    printf("\n******End Heapify******\n"
           "n = %d, i = %d ",
           n, i);
    aff_List2(list, n);
    printf("*****************\n");
}

// main function to do heap sort
void trie_LExtraction(Cellule *list, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 ; i > 1; i--)
        lExtracte(list, n, i);

    printf("\n******HeapSort******\n"
           "n = %d, i = -1",
           n);
    aff_List2(list, n);
    printf("*****************\n");
    // One by one extract an element from heap
    for (int i = n ; i > 0; i--) {
        // Move current root to end
        xchange(list, getCel(list, i));


        // call max tExtracte on the reduced heap
        lExtracte(list, i, 1);

        printf("\n******HeapSort******\n"
               "n = %d, i = %d",
               n, i);
        aff_List2(list, n);
        printf("*****************\n");
    }
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

Cellule *insert_arrayToList(Cellule *list, int *array,unsigned int n) {

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


void main() {
    int n = 7;
    int arr[7] = {5,9,1,3,7,0,4};

    Cellule *list = NULL;
    list = insert_arrayToList(list, arr, n);

    trie_LExtraction(list, n);
}



