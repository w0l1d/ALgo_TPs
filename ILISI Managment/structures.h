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

char *modules[3][16];

const char STUDENT_PATTERN[] = "%30[^;];%30[^;];"
                               "%8[A-Za-z0-9];%10[A-Za-z0-9];"
                               "%d;%d;%d;%d;%d\n";

const char NOTE_PATTERN[] = "%f;%f;";


typedef struct {
    char *nom; // max 30
    char *prenom; // max 30
    char *cin; //max 8, format XY123456\0
    char *cne; //max 10, format X123456789\0
    Date naiss;
    unsigned reserve:3;
    unsigned annee_univ:3;
}Student;


typedef struct nt {
    float normal;
    float ratt;
}Note;

typedef struct ds {
    Student *student;
    Note *notes[4][16];
    struct ds *svt;
}Dossier;




#endif //PRACTICE_STRUCTURES_H
