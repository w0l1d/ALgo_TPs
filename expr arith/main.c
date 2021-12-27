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
        case PS: return((int) PS);
        case NS: return((int) NS);
        case MS: return((int) MS);
        case DS: return((int) DS);
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

    if (!exp)      return ((int) -1); // expression n'existe pas
    if (!(*exp))   return ((int) -1); // expression est vide

    while(*exp)
    {
        //si le tete du chaine est un espace
        if (*exp == BL) {
            exp++;
            continue;
        }
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
    int i = 0, test;
    *rst_size = valid_exp(exp);
    // indique que l'expression est invalide
    if ((*rst_size) == -1)  return ((double*) NULL);


    double num, *exptr = (double*)malloc(sizeof(double) * (*rst_size));
    while (*exp) {
        // espace est lu
        if (*exp == BL) {
            exp++;
            continue;
        }
        if ((i++)%2) //traitement d'operateur
        {
            test = is_operator(*exp);
            if (test != NS) {
                exp++;
                exptr[i-1] = test;
            } else { //si l'operation est la soustraction a-b -> a+-b
                exptr[i-1] = PS;
                //si on a le cas a--b -> a+b
                if (is_operator(*(exp+1)) == NS)
                    exp+=2;
            }

        } else { //traitement d'operand
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

    if (size == 1) return((Node*) create_NodePt(exptr[0]));


    for (i = 1; i < size-1; i +=2)
        opr[((exptr[i] == NS) || (exptr[i] == PS))?0:1]++;

    Node * ne = NULL;
    if (opr[0]) //traitement des operation moins prioritaire +, -
    {
        tmp = (opr[0]+1)/2;
        cpt = 0;
        //position de l'opration au milieu
        for (i = 1; i < size-1; i += 2)
        {
            if ((exptr[i] == NS) || (exptr[i] == PS))
            {
                cpt++;
                if (cpt == tmp) { cpt = i; break; }
            }
        }
        ne = create_NodePt(exptr[cpt]);

        ne->gch = trans_exptr_Arbre(exptr, cpt);
        ne->drt = trans_exptr_Arbre(exptr+cpt+1, size-cpt-1);
    } //traitement des operation plus prioritaire *, /
    else if (opr[1])
    {
        //position de l'opration au milieu
        for (i = 1; i < size-1; i += 2)
        {
            if ((exptr[i] == MS) || (exptr[i] == DS))
                cpt = i;
        }
        ne = create_NodePt(exptr[cpt]);

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
        case PS: return ((double) a+b);
        case NS: return ((double) a-b);
        case MS: return ((double) a*b);
        case DS: return ((double) a/b);
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
    if (root->drt) {
        double a = calc_arbre(root->gch),
                b = calc_arbre(root->drt),
                rst = calc_opr(a,b,(int)root->info);
        return ((double) rst);
    }
    return ((double) root->info);
}




char* scan(char *string) {
    int c; //as getchar() returns `int`
    int i=0, max = 49;

    string = malloc(sizeof(char)*(max+1)); //allocating memory
    while ((string[i++]= getchar()) != LB)
        if (i-1 == max)
            string = realloc(string, (max +=10)*sizeof(char)); //reallocating memory
    string[i-1] = '\0';

    return string;
}


void test1(char exp[]) {

//    printf("\nEntrer l'expression: ");
//    scanf("%[^\n]s", exp);
    int tmp;

    printf("expression : %s\n", exp);

    double rst,
            *exptr = trans_exp_parts(exp, &tmp);

    if (!exptr) {
        printf("\nError : Expression invalide\n");
        return;
    }

    Node* node = trans_exptr_Arbre(exptr,tmp);

    affiche_infixer(node);

    affiche_arbre_Real(node);

    rst = calc_arbre(node);
    printf("resultat de l'expression : %lf", rst);
}

void main() {

    printf("\n\n*****************************************************************");
    printf("\nTest 1 :\n");
    test1("-3.0+-5.2+4.0/3.2*-3.8-5.0");
    printf("\n\n*****************************************************************");
    printf("\nTest 2 :\n");
    test1("-3.0+-5.2+4.0*3.2+3.8/5.0");
    printf("\n\n*****************************************************************");
    printf("\nTest 3 :\n");
    test1("-3.0+-5.2+4.0+3.2+3.8+5.0");

}
