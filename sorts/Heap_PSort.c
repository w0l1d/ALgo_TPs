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



Cellule * getCel(Cellule *list, int pos) {
    while (list) {
        if(pos-- == 1)
            return ((Cellule*) list);
        list = list->svt;
    }
    return ((Cellule*) NULL);
}

void padding(char ch,int n) {
    int i;
    for (i=0;i<n;i++)
        putchar(ch);
}

void structur(Cellule *arbre,int level,int indice,int nbr)
{
    if (indice>=nbr+1)
    {
        padding('\t',level);
        puts("~");
    }
    else {
        structur(arbre,level+1,2*indice+1,nbr);
        padding( '\t',level);
        printf("%d\n",getCel(arbre, indice)->val);
        structur(arbre,level+1,indice*2,nbr);
    }
}



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
 * creer un max-heap: arbre dont la chaque noeud est superieur a ses fils
 * @param list
 * @param n
 * @param i
 */
void lExtracte(Cellule *list, int n, int i) {
    printf("\n******Start Heapify******\n"
           "n = %d, i = %d\n",
           n, i);
    structur(list, 0, 1, n);
    printf("*****************\n");

    int largest = i; // Initialize largest as root
    int l = 2 * i; // left = 2*i
    int r = 2 * i + 1; // right = 2*i + 1

    Cellule *largestCel = getCel(list, largest);
    // If left child is larger than root
    Cellule *leftCel= getCel(list, l);
    if (l < (n+1) && leftCel->val > largestCel->val) {
        largestCel = leftCel;
        largest = l;
    }

    // If right child is larger than largest so far
    Cellule *rightCel= getCel(list, r);
    if (r < (n+1) &&  rightCel->val > largestCel->val) {
        largestCel = rightCel;
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        xchange(getCel(list, i), largestCel);

        // Recursively lExtracte the affected sub-tree
        lExtracte(list, n, largest);
    }

    printf("\n******End Heapify******\n"
           "n = %d, i = %d \n",
           n, i);
    structur(list, 0, 1, n);
    printf("*****************\n");
}

// main function to do heap sort
void trie_LExtraction(Cellule *list, int n) {
    int i;

    // Build heap (rearrange array)
    for (i = n / 2 ; i > 0; i--)
        lExtracte(list, n, i);

    printf("\n******HeapSort******\n"
           "n = %d, i = -1\n",
           n);
    structur(list, 0, 1, n);
    printf("*****************\n");
    // One by one extract an element from heap
    for (i = n-1 ; i > 1; i--) {
        // Move current root to end
        xchange(list, getCel(list, i+1));


        // call max tExtracte on the reduced heap
        lExtracte(list, i, 1);

        printf("\n******HeapSort******\n"
               "n = %d, i = %d\n",
               n, i);
        structur(list, 0, 1, n);
        printf("*****************\n");
    }

    xchange(list, getCel(list, i+1));
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
    if (!n)  return ((Cellule*) list);

    int i = 0;
    //initilaiser la liste si elle est vide
    list = (!list)? createCel(array[i++]):list;

    Cellule *curr = list;

    //deplacer a la fin de la liste pour inserer en queue
    while(curr->svt)     curr=curr->svt;


    //inserer chaque element en queue
    for (; i < n; ++i) {
        curr->svt = createCel(array[i]);
        curr = curr->svt;
    }
    return ((Cellule*) list);
}


void main() {
    int n = 8;
    int arr[8] = {5,9,1,3,7,0,4, 8/*,
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
                   1,7, 6, 5, 6, 3, 7, 0*/};


    Cellule *list = NULL;
    list = insert_arrayToList(list, arr, n);


    clock_t tic = clock();

    trie_LExtraction(list, n);

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);



    printf("\n******AFFICHAGE Final******\n");
    structur(list, 0, 1, n);
    printf("*****************\n");
}



