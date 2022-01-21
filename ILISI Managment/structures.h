//
// Created by W0L1D on 1/21/2022.
//

#ifndef PRACTICE_STRUCTURES_H
#define PRACTICE_STRUCTURES_H

#define DELIM ';'

typedef struct {
    unsigned year:12;
    unsigned month:4;
    unsigned day:5;
}Date;

unsigned char *modules[3][16];

const char STUDENT_PATTERN[] = "%30[^;]s;%30[^;]s;"
                               "%8[A-Za-z0-9]s;%10[A-Za-z0-9]s;"
                               "%d;%d;%d;%d;%d\n";
const char NOTE_PATTERN[] = "%f,%f;";


typedef struct {
    unsigned char *nom;
    unsigned char *prenom;
    unsigned char *cin; //format XY123456\0
    unsigned char *cne; //format X123456789\0
    Date naiss;
    unsigned reserve:3;
    unsigned annee_univ:3;
}Student;


typedef struct nt {
    unsigned val:5;
    struct nt *rat;
}Note;

typedef struct {
    unsigned char student;
    Note *notes[4][16];
}Dossier;




#endif //PRACTICE_STRUCTURES_H
