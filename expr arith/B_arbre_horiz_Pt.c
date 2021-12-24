//
// Created by W0L1D on 11/23/2021.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node {
    unsigned type:1; // 0 pour operande, 1 pour operation
    double info; //information du noeud
    struct Node *drt; //pointeur sur le fils droit
    struct Node *gch; //pointeur sur le fils gauche
}Node;



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









///**********************************************************************************
/***********************************************************************************
 * Nom : void affiche_prefixer(Node *root)
 *             Affiche Prefixer récursivement les elements de l'arbre
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 * Sortie : rien
 */
void affiche_prefixer(Node *root)
{
    if (!root)
        return;

    printf("%lf\t", root->info);
    affiche_prefixer(root->gch);
    affiche_prefixer(root->drt);

}






//**********************************************************************************
/***********************************************************************************
 * Nom : void affiche_infixer(Node *root)
 *             Affiche Infixer récursivement les elements de l'arbre
 *
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *
 * Sortie : rien
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



//**********************************************************************************
/***********************************************************************************
 * Nom : int profondeur_arbrePt(Node *root)
 *             calcule récursivement la profondeur de l'arbre
 *
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *
 * Sortie : int la profondeur dans l'arbre
 */
int profondeur_arbrePt(Node *root) {
    if (!root)
        return 0;
    int drt = profondeur_arbrePt(root->drt) + 1;
    int gch = profondeur_arbrePt(root->gch) + 1;
    return (drt>gch)? drt : gch;
}


//**********************************************************************************
/***********************************************************************************
 * Nom : void largeur_par_niveau_arbrePt(Node *root , int *niveaux, int ligne)
 *             calcule récursivement les largeurs d'arbre pour chaque niveau
 *             largeur : le nombre de neoud dans chaque niveau
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *          int *niveaux : largeur pour chaque niveau
 *                        initialise à {0,0,...}
 *                        eventielement contient les largeur de chaque
 *          int ligne : le niveau du noeud courant
 * Sortie : rien
 */
void largeur_par_niveau_arbrePt(Node *root , int *niveaux, int ligne) {
    if (!root)
        return;

    (*(niveaux + ligne))++;
    largeur_par_niveau_arbrePt(root->gch, niveaux, ++ligne);
    largeur_par_niveau_arbrePt(root->drt, niveaux, ligne);
}




//**********************************************************************************
/***********************************************************************************
 * Nom : int largeur_max_arbrePt(Node *root)
 *             Cherche récursivement la largeur maximal de l'arbre
 *
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *
 * Sortie : int la largeur maximal dans l'arbre
 */
int largeur_max_arbrePt(Node *root) {
    if (!root)
        return ((int) 0);
    int prof = profondeur_arbrePt(root);
    return ((int) pow(2, prof-1));
}




//**********************************************************************************
/***********************************************************************************
 * Nom : int max_val_arbrePt(Node *root)
 *             Cherche récursivement la valeur maximal
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 * Sortie : int la valeur maximal dans l'arbre
 */
int max_val_arbrePt(Node *root) {
    if (!root->drt)
        return root->info;
    return max_val_arbrePt(root->drt);
}



//**********************************************************************************
/***********************************************************************************
 * Nom : Node *max_noeud_arbrePt(Node *root)
 *             Cherche récursivement le Node avec la valeur maximal
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 * Sortie : Node* pointeur sur le noeud maximal
 */
Node *max_noeud_arbrePt(Node *root) {
    if (!root)
        return ((Node*) NULL);
    if (!root->drt)
        return root;
    return max_noeud_arbrePt(root->drt);
}


//**********************************************************************************
/***********************************************************************************
 * Nom : int min_val_arbrePt(Node *root)
 *             Cherche récursivement la valeur minimal
 *
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *
 * Sortie : int la valeur minimal dans l'arbre
 */
int min_val_arbrePt(Node *root) {
    if (!root->gch)
        return root->info;
    return min_val_arbrePt(root->gch);
}




//**********************************************************************************
/***********************************************************************************
 * Nom : Node *min_noeud_arbrePt(Node *root)
 *             Cherche récursivement le Node avec la valeur minimal
 *
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *
 * Sortie : Node* pointeur sur le noeud minimal
 */
Node *min_noeud_arbrePt(Node *root) {
    if (!root)
        return ((Node*) NULL);
    if (!root->gch)
        return root;
    return min_noeud_arbrePt(root->gch);
}





//**********************************************************************************
/***********************************************************************************
 * Nom : int largeur_arbrePt(Node *root, const int *niveaux, int profondeur)
 *             cherche la largeur maximal d'arbre donnee
 *             largeur : le nombre de neoud maximal dans un niveau
 *
 * Entree : const int *niveaux : la largeur d'arbre pur chaque niveau
 *          int profondeur : profondeur maximale de l'arbre
 *
 * Sortie : entier represent la largeur de l'arbre
 */
int largeur_arbrePt(Node *root, const int *niveaux, int profondeur) {
    if (!root)
        return 0;
    int i,
    max = *niveaux;
    for (i = 0; i < profondeur; i++)
        if (max < *(niveaux+i))
            max = *(niveaux+i);
    return ((int) max);
}


//**********************************************************************************
/***********************************************************************************
 * Nom : int size_arbrePt(Node *root)
 *             calcule récursivement la taille d'un arbre donnee
 * Entree : Node *root: l'arbre sur lequel on applique le traitement
 * Sortie : int : entier represente la taille de l'arbre
 */
int size_arbrePt(Node *root)
{
    if (!root)
        return ((int) 0);

    int dt = size_arbrePt(root->gch),
    gch = size_arbrePt(root->drt);
    return ((int) dt + gch + 1);
}





//**********************************************************************************
/***********************************************************************************
 * Nom : void assign_val_to_Mtx(Node *root, int *matrice, int cols,
 *                              int line, int col, int ss)
 *             attribue les noeuds dans l'arbre
 *             au champs correspondent dans la matrice
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 *          int *matrice : ou on attribue les valeur des noeuds
 *          int cols : nombre de colonnes de la matrice
 *          int line : ligne courant
 *          int col : colonne courant
 *          int ss : deplacement du colonne du fils par apport au parent
 * Sortie : rien
 */
void assign_val_to_Mtx(Node *root, double *matrice, int cols, int line, int col, int ss) {
    if (!root)
        return;
    *((matrice+(line*cols))+col) = root->info;

    assign_val_to_Mtx(root->drt, matrice, cols, line + 1, col + ss, ss/2);
    assign_val_to_Mtx(root->gch, matrice, cols, line + 1, col - ss, ss/2);

}



//**********************************************************************************
/***********************************************************************************
 * Nom : void affiche_arbre_Real(Node *root)
 *             afficher l'arbre comme arbre reel verticalement
 * Entree : Node *root : l'arbre sur lequel on applique le traitement
 * Sortie : rien
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


