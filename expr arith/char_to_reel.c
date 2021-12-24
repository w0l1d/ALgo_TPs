//
// Created by W0L1D on 12/20/2021.
//
#include<stdio.h>
#include<stdlib.h>

#define PS '+'
#define PS_val 0
#define NS '-'
#define NS_val 1
#define MS '*'
#define MS_val 2
#define DS '/'
#define DS_val 3

#define PT '.' //signe point '.'
#define LB '\n' //retour a la ligne '\n'



int is_chiffre_num(char ch) {
    return ((int)
    ('0' <= ch) && (ch <= '9')
    );
}

int to_Num(char ch) {
    if (is_chiffre_num(ch))
        return ((int) ch - '0');
    return ((int) -1);
}

int trait_sign(char **ch) {
    if (**ch == NS)
    {
        (*ch)++;
        return ((int) -1);
    }
    if (**ch == PS)
        (*ch)++;
    return((int) 1);
}


void trait_int(double *num, char **ch) {
    *num = 0;
    int tmp = 0;
    while(is_chiffre_num(**ch))
    {
        (*num) = (*num)*10 + (double)to_Num(**ch);
        (*ch)++;
    }
}

void trait_Point(char **ch) {
    if (**ch == PT)
        (*ch)++;
}


void trait_reel(double *num, char **ch) {
    double pow = 1, reel;
    while(is_chiffre_num(**ch)) {
        reel = ((double)to_Num(**ch)) * (pow /= 10);
        *num = (*num) + reel;
        (*ch)++;
    }
}



char* trans_CharToNum(char *c, double *rst, int *test) {
    *rst = 0;
    *test = 1;
    int signe;

    signe = trait_sign( &c);
    if (!is_chiffre_num(*c) && *c != PT) {
        *test = 0;
        return ((char*) c);
    }
    trait_int(rst, &c);
    trait_Point(&c);
    trait_reel(rst, &c);
    (*rst) *= (double)signe;

    return ((char*) c);
}

