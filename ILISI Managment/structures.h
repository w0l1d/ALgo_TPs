//
// Created by W0L1D on 1/21/2022.
//

#ifndef PRACTICE_STRUCTURES_H
#define PRACTICE_STRUCTURES_H

#define DELIM ';'



const char STUDENT_PATTERN[] = "%30[^;];%30[^;];"
                               "%8[A-Za-z0-9];%10[A-Za-z0-9];"
                               "%d;%d;%d;%d;%d\n";


typedef struct {
    unsigned year:12;
    unsigned month:4;
    unsigned day:5;
}Date;



typedef struct {
    char *nom; // max 30
    char *prenom; // max 30
    char *cin; //max 8, format XY123456\0
    char *cne; //max 10, format X123456789\0
    Date naiss;
    unsigned reserve:3;
    unsigned annee_univ:3;
}Student;



typedef struct ds {
    Student *student;
    float notes[4][16];
    float moy[4];
    unsigned inf12:5; // nombre de module avec 12 > note >= 10
    unsigned inf10:1; // 1 si il a au moins une note < 10
    struct ds *svt;
}Dossier;




#endif //PRACTICE_STRUCTURES_H
