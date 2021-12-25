//
// Created by W0L1D on 11/23/2021.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


    typedef struct Node {
        unsigned type:1; // 0 pour operand, 1 pour operation
        double info; //information du noeud
        struct Node *drt; //pointeur sur le fils droit
        struct Node *gch; //pointeur sur le fils gauche
    }Node;


/*******************************************
 * traduit le code : l'operation --> symbole
 * @param op code de l'operation
 * @return characters correspond au op, ? sinon
 */
char num_to_opr(const int op) {
    switch (op) {
        case PS_val: return((char) PS);
        case NS_val: return((char) NS);
        case MS_val: return((char) MS);
        case DS_val: return((char) DS);
    }
    return ((char) '?');
}


//**********************************************************************************
/***********************************************************************************
 * Nom : Node* create_NodePt(int val)
 *             Insert recursivement un element dans
 *             l'arbre dans la position correcte
 * Entree : int val : la valeur du nouveau noeud
 * Sortie : Node* : pointeur sur le noeud cree
 */

    /*********************************************
     * Node* create_NodePt(double val, unsigned int type)
     * cree et initialise le noeud
     * @param val valeur du noeud
     * @param type type du noeud
     * @return noeud cree
     */
    Node* create_NodePt(double val, unsigned int type)
    {
        Node *ne = (Node*) malloc(sizeof(Node));
        if (!ne)
        {
            printf("\n\n Erreur d'allocation de memoire\n");
            exit(0);
        }
        ne->drt = ne->gch = NULL;
        ne->info = val;
        ne->type = type;
        return ((Node*) ne);
    }




/********************************************************************************
 * void affiche_infixer(Node *root)
 * Affiche infixer des noeud
 * @param root arbre a affcher
 */
void affiche_infixer(Node *root)
{
    if (!root)
        return;
    affiche_infixer(root->gch);
    if (root->type == 0)
        printf("%.0lf", root->info);
    else
        printf("%c", num_to_opr((int)root->info));
    affiche_infixer(root->drt);
}



/****************************************************
 * int profondeur_arbrePt(Node *root)
 * calcule récursivement la profondeur de l'arbre
 * @param root arbre a traiter
 * @return int la profondeur d'arbre
 */
int profondeur_arbrePt(Node *root) {
    if (!root)
        return 0;
    int drt = profondeur_arbrePt(root->drt) + 1;
    int gch = profondeur_arbrePt(root->gch) + 1;
    return (drt>gch)? drt : gch;
}


/*********************************************************************
 * void largeur_par_niveau_arbrePt(Node *root , int *niveaux, int ligne)
 *  calcule récursivement les largeurs d'arbre pour chaque niveau
 *  largeur : le nombre de neoud dans chaque niveau
 * @param root arbre a traiter
 * @param niveaux largeur pour chaque niveau, initialise à {0,0,...}
 * @param ligne le niveau du noeud courant
 */
void largeur_par_niveau_arbrePt(Node *root , int *niveaux, int ligne) {
    if (!root)
        return;

    (*(niveaux + ligne))++;
    largeur_par_niveau_arbrePt(root->gch, niveaux, ++ligne);
    largeur_par_niveau_arbrePt(root->drt, niveaux, ligne);
}






/************************************************************************************
 * void assign_val_to_Mtx(Node *root, int *matrice,
 *                          int cols, int line,
 *                          int col, int ss)
 *             attribue les noeuds dans l'arbre
 *             au champs correspondent dans la matrice
 * @param root arbre a traiter
 * @param matrice ou on attribue les valeur des noeuds
 * @param cols nombre de colonnes de la matrice
 * @param line ligne courant
 * @param col colonne courant
 * @param ss deplacement du colonne du fils par apport au parent
 */
void assign_val_to_Mtx(Node *root, double *matrice,
                       int cols, int line,
                       int col, int ss) {
    if (!root)
        return;
    *((matrice+(line*cols))+col) = root->info;

    assign_val_to_Mtx(root->drt, matrice, cols, line + 1, col + ss, ss/2);
    assign_val_to_Mtx(root->gch, matrice, cols, line + 1, col - ss, ss/2);

}



/*******************************
 * void affiche_arbre_Real(Node *root)
 * afficher l'arbre comme arbre reel verticalement
 * @param root arbre a afficher
 */
void affiche_arbre_Real(Node *root) {
    int prof = profondeur_arbrePt(root);
    int segma = 0;
    int tmp;
    for (int i = 0; i < prof; ++i) {
        tmp = (int)pow(2, i);
        segma+=tmp;
    }

    double matrice[prof][segma];
    double *pt = (double *) matrice;

    for (int i = 0; i < prof; ++i)
        for (int j = 0; j < segma; ++j)
            matrice[i][j] = -99;

    assign_val_to_Mtx(root, pt, segma,  0, (segma/2), (segma/2+1)/2);

    printf("\n*******************************\n");
    for (int i = 0; i < prof; ++i) {
        for (int j = 0; j < segma; ++j) {
            if (matrice[i][j] == -99)
                printf("    ");
            else
                printf("%2.1lf", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n*******************************\n");
}


