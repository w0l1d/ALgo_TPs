//
// Created by W0L1D on 1/21/2022.
//

#ifndef PRACTICE_STRUCTURES_H
#define PRACTICE_STRUCTURES_H

typedef struct {
    unsigned year:12;
    unsigned month:4;
    unsigned day:5;
}Date;

unsigned char *modules[3][16];


typedef struct nt {
    unsigned val:5;
    struct nt *rat;
}Note;


typedef struct {
    unsigned char *nom;
    unsigned char *prenom;
    unsigned char cin[9]; //format XY123456\0
    unsigned char cne[11]; //format X123456789\0
    Date naiss;
    unsigned reserve:3;
    unsigned annee_univ:3;
}Student;



#endif //PRACTICE_STRUCTURES_H
