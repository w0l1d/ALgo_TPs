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


/****************************
 * is_chiffre_num(char ch)
 * verifies si un char est chiffre numerique
 * @param ch character
 * @return 1 si ch est chiffre,0 sinon
 */
int is_chiffre_num(char ch) {
    return ((int)
    ('0' <= ch) && (ch <= '9')
    );
}

/**************
 * int to_Num(char ch)
 * transforme un char vers un chiffre
 * @param ch character
 * @return chiffre correspondent,
 * -1 si ch n'est pas un chiffre
 */
int to_Num(char ch) {
    if (is_chiffre_num(ch))  return ((int) ch - '0');
    return ((int) -1);
}


/***************************
 * char* trait_sign(char *ch, int *s)
 * retourne un signe si de ch[0] dans s
 * @param ch entier comme chaine
 * @param s signe trouve
 * @return suivant du chaine
 */
char* trait_sign(char *ch, int *s) {
    *s =  1;
    if (*ch == NS) { *s = -1; ch++; }
    else if (*ch == PS) ch++;
    return((char*) ch);
}



/*********************
 * char* trait_int(double *num, char *ch)
 * ransforme un entier du chaine ch
 * @param num entier tranformee
 * @param ch chaine de caracter
 * @return suivant apres l'entier
 */
char* trait_int(double *num, char *ch) {
    *num = 0;
    while(is_chiffre_num(*ch)) {
        (*num) = (*num)*10 + (double)to_Num(*ch);
        ch++;
    }
    return ((char*) ch);
}

/*****************************
 * void trait_Point(char **ch)
 * traite le points du reel
 * @param ch
 * @return
 */
char* trait_Point(char *ch) {
    return (*ch == PT)? ++ch: ch;
}




/*****************************************
 * char* trait_reel(double *num, char *ch)
 * traite la partie decimal du reel
 * @param num nombre transforme
 * @param ch chaine de characters
 * @return suivant du chaine apres decimal
 */
char* trait_reel(double *num, char *ch) {
    double pow = 1, reel;
    while(is_chiffre_num(*ch)) {
        reel = ((double)to_Num(*ch)) * (pow /= 10);
        *num = (*num) + reel;
        ch++;
    }
    return ((char*) ch);
}


/********************************************************
 * char* trans_CharToNum(char *c, double *rst, int *test)
 * transforme une chaine de characters vers reel
 * @param c reel en chaine de characters
 * @param rst resultat du transformation
 * @param test l'etat du transformation,
 * 0 char incorrect, -1 si rst == 0, 1 operation bien faite
 * @return suivant de reel dans la chaine donnee
 */
char* trans_CharToNum(char *c, double *rst, int *test) {
    *rst = 0;  *test = 1;
    int signe;
    c = trait_sign(c, &signe);

    if (!is_chiffre_num(*c) && *c != PT) {
        *test = 0;
        return ((char*) c);
    }
    c = trait_int(rst, c);
    c = trait_Point(c);
    c = trait_reel(rst, c);
    (*rst) *= (double)signe;

    if (!(*rst)) *test = -1;

    return ((char*) c);
}

