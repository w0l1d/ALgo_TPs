//
// Created by W0L1D on 12/20/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_to_reel.c"
#include "B_arbre_horiz_Pt.c"



/********************************
 * int is_operator(const char c)
 * Verifie le character donne si il est un oprateur arithmetique
 * @param exp
 * @return valeur lie a l'operateur sinon -1
 *
 */
int is_operator(const char c) {
    switch (c) {
        case PS: return((int) PS_val);
        case NS: return((int) NS_val);
        case MS: return((int) MS_val);
        case DS: return((int) DS_val);
    }
    return ((int) -1);
}


/*************************************
 * char* is_float(char *exp, int *test)
 * verifie si le debut to chaine est un reel
 * @param exp chaine de characters
 * @param test valeur a retourner
 * 1 si le debut du chaine est un reel correct
 * -1 si ce reel est nulle
 * 0 si c'est pas un reel ou entier
 * @return chaine de characters apres passer le characters traites
 */
char* is_float(char *exp, int *test) {
    double rst;
    exp = trans_CharToNum(exp, &rst, test);
    return ((char*) exp);
}



/***************************************************************
 * int valid_exp(char *exp)
 * @param exp expression mathematics comme chaine de characters
 * @return nombre des operateurs et operands de l'expression math
 * si elle est valide, -1 sinon
 */
int valid_exp(char *exp) {
    int i = 0, test, tmp = 0;

    if (!exp)      return ((int) -1);
    if (!(*exp))   return ((int) -1);

    while(*exp)
    {
        if ( (i++)%2 ) {
            test = is_operator(*exp);
            if(test == -1) return ((int) -1);
            if (test == 3) tmp = 1;
            exp++;
        } else {
            exp = is_float(exp, &test);
            if (!test) return ((int) -1);
            if ((test == -1) && tmp) return ((int) -1);
            tmp = 0;
        }
    } // fin while(*exp)
    return ((int) i);
}


/*********************************************************
 * double *trans_exp_parts(char *exp, int *rst_size)
 * tranformer l'expression math vers un tableau des reel
 * contient les opérateurs et operands par ordre donnee
 * @param exp expression mathematics
 * @param rst_size nombre des operations et operands
 * @return tableau des reel
 * rang pair contient les operands
 * rang impair contient les operations
 */
double *trans_exp_parts(char *exp, int *rst_size) {
    int i = 0, test, size;
    size = valid_exp(exp);
    if (size == -1)  return ((double*) NULL);
    *rst_size = size;

    double num, *exptr = (double*)malloc(sizeof(double) * size);
    while (*exp) {
        if ((i++)%2) {
            test = is_operator(*exp);
            exptr[i-1] = test;
            exp++;
        } else {
            exp = trans_CharToNum(exp, &num, &test);
            exptr[i-1] = num;
        }
    } // fin while (*exp)
    return ((double*) exptr);
}


/***************************************************
 * Node* trans_exptr_Arbre(double *exptr, int size)
 * transferer le tableau vers un arbre
 * @param exptr  les elements de expression mathematique
 * @param size la taille du tableau
 * @return arbre de l'expression math
 */
Node* trans_exptr_Arbre(double *exptr, int size)
{
    int i, cpt, tmp, opr[2] = {0, 0};

    if (size == 1) return((Node*) create_NodePt(exptr[0], 0));


    for (i = 1; i < size-1; i +=2)
        opr[((exptr[i] == NS_val) || (exptr[i] == PS_val))?0:1]++;

    Node * ne = NULL;
    if (opr[0])
    {
        tmp = (opr[0]+1)/2;
        cpt = 0;
        for (i = 1; i < size-1; i += 2)
        {
            if ((exptr[i] == NS_val) || (exptr[i] == PS_val))
            {
                cpt++;
                if (cpt == tmp) { cpt = i; break; }
            }
        }
        ne = create_NodePt(exptr[cpt], 1);

        ne->gch = trans_exptr_Arbre(exptr, cpt);
        ne->drt = trans_exptr_Arbre(exptr+cpt+1, size-cpt-1);
    }
    else if (opr[1])
    {
        tmp = (opr[1]+1)/2;
        cpt = 0;
        for (i = 1; i < size-1; i += 2)
        {
            if ((exptr[i] == MS_val) || (exptr[i] == DS_val))
            {
                cpt++;
                if (cpt == tmp) { cpt = i; break; }
            }
        }
        ne = create_NodePt(exptr[cpt], 1);

        ne->gch = trans_exptr_Arbre(exptr, cpt);
        ne->drt = trans_exptr_Arbre(exptr+cpt+1, size-cpt-1);
    } // fin else if (opr[1])

    return ((Node*) ne);
}

/***********************************************
 * double calc_opr(double a, double b, int op)
 * fait l'operation op qui convient entre a et b
 * @param a premier operand
 * @param b deuxieme operand
 * @param op code de l'operation
 * @return resultat si op est correct, 0 sinon
 */
double calc_opr(double a, double b, int op) {
    switch(op) {
        case PS_val: return ((double) a+b);
        case NS_val: return ((double) a-b);
        case MS_val: return ((double) a*b);
        case DS_val: return ((double) a/b);
    }
    return ((double) 0);
}


/**********************************
 * calcule la resultat de l'expression d'arbre
 * @param root arbre a calculer
 * @return resultat du calcule
 */
double calc_arbre(Node *root) {
    if (!root)   return ((double) 0);
    if (root->type) {
        double a = calc_arbre(root->gch),
                b = calc_arbre(root->drt),
                rst = calc_opr(a,b,(int)root->info);
        return ((double) rst);
    }
    return ((double) root->info);
}




void main() {
    char exp[50] = "1+--5";

//    printf("\nEntrer l'expression: ");
//    scanf("%[^\n]s", exp);



    int test, tmp;


    printf("\n************\n");

    printf("expression : %s\n", exp);

    double rst,
            *exptr = trans_exp_parts(exp, &tmp);

    if (!exptr) {
        printf("\nError : Expression invalide\n");
        return;
    }
    printf("\nTrans to arbre\n");

    Node* node = trans_exptr_Arbre(exptr,tmp);

    printf("\nfin Trans to arbre11\n");
    affiche_infixer(node);


    printf("\n\n");

    affiche_arbre_Real(node);
    printf("\nfin Trans to arbre\n");

    rst = calc_arbre(node);
    printf("resultat de l'expression : %lf", rst);

}
