//
// Created by W0L1D on 12/20/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_to_reel.c"
#include "B_arbre_horiz_Pt.c"





int is_oprator(const char *exp) {
    char c = exp[0];
    switch (c) {
        case PS: return((int) PS_val);
        case NS: return((int) NS_val);
        case MS: return((int) MS_val);
        case DS: return((int) DS_val);
    }
    return ((int) -1);
}



char* is_float(char *exp, int *test) {
    double rst;
    exp = trans_CharToNum(exp, &rst, test);
    return ((char*) exp);
}




int valid_exp(char *exp) {
    int i = 0, test;

    if (!exp)
        return ((int) -1);
    if (!(*exp))
        return ((int) -1);
    while (*exp) {

        if ((i++)%2) {
            test = is_oprator(exp);
            if(test == -1) return ((int) -1);
            exp++;
        } else {
            exp = is_float(exp, &test);
            if (!test) {
                return ((int) -1);
            }
        }
    }
    return ((int) i);
}



double *trans_exp_parts(char *exp, int *rst_size) {
    int i = 0, test, size;

    size = valid_exp(exp);

    if (size == -1)
        return ((double*) NULL);

    *rst_size = size;

    double num,
            *exptr = (double*)malloc(sizeof(double) * size);

    while (*exp) {
        if ((i++)%2) {
            test = is_oprator(exp);
            exptr[i-1] = test;
            exp++;
        } else {
            exp = trans_CharToNum(exp, &num, &test);
            exptr[i-1] = num;
        }
    }

    printf("\nTranslation finished\n\n");

    return ((double*) exptr);
}

Node* trans_exptr_Arbre(double *exptr, int size) {
    int i, cpt, tmp,
        opr[2] = {0, 0};

    Node * ne = NULL;
    if (size == 1) {
        ne = create_NodePt(exptr[0], 0);
        return((Node*) ne);
    }


    for (i = 1; i < size-1; i +=2)
        opr[((exptr[i] == NS_val) || (exptr[i] == PS_val))?0:1]++;

    if (opr[0]) {
        tmp = (opr[0]+1)/2;
        cpt = 0;
        for (i = 1; i < size-1; i += 2) {
            if ((exptr[i] == NS_val) || (exptr[i] == PS_val)) {
                cpt++;
                if (cpt == tmp) {
                    cpt = i;
                    break;
                }
            }
        }
        ne = create_NodePt(exptr[cpt], 1);

        ne->gch = trans_exptr_Arbre(exptr, cpt);
        ne->drt = trans_exptr_Arbre(exptr+cpt+1, size-cpt-1);
        return ((Node*) ne);

    } else if (opr[1]) {
        tmp = (opr[1]+1)/2;
        cpt = 0;
        for (i = 0; i < size; i++) {
            if ((exptr[i] == MS_val) || (exptr[i] == DS_val)) {
                cpt++;
                if (cpt == tmp) {
                    cpt = i;
                    break;
                }
            }
        }
        ne = create_NodePt(exptr[i], 1);
        ne->gch = trans_exptr_Arbre(exptr, size/2);
        ne->drt = trans_exptr_Arbre(exptr+cpt+1, size/2);
        return ((Node*) ne);

    }
    ne = create_NodePt(*exptr, 0);
    return ((Node*) ne);
}




void main() {
    char exp[50];

    printf("\nEntrer l'expression: ");
    scanf("%[^\n]s", exp);



    int tmp;
    double *exptr = trans_exp_parts(exp, &tmp);


    printf("\n************\n");

    printf("\nTrans to arbre\n");

    Node* node = trans_exptr_Arbre(exptr,tmp);

    affiche_infixer(node);
    printf("\nfin Trans to arbre\n");


}
