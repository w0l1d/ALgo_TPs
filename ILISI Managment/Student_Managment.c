//
// Created by W0L1D on 1/21/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "error_msg.h"

Dossier *initDossier(Student *st) {
    Dossier *ds;
    ds = (Dossier*) malloc(sizeof(Dossier));
    if (!ds) {
        printf(ERROR_ALL_MEM_DOSSIER);
        exit(-1);
    }
    ds->student = st;
    return ((Dossier*)ds);
}

Note *init_Note(float normal, float ratt) {
    Note *nt = (Note*) malloc(sizeof(Note));
    if (!nt) {
        printf(ERROR_ALL_MEM_NOTE);
        exit(-1);
    }
    nt->normal = normal;
    nt->ratt = ratt;
    return ((Note*) nt);
}

Student* readStudent(FILE *fl) {
    Student *stud = (Student*) malloc(sizeof(Student));
    char nom[25],prenom[30], cin[15], cne[15];
    unsigned int day, month, year, res, an_unv;
    fscanf(fl, STUDENT_PATTERN,
           nom, prenom, cin, cne, &day,
           &month, &year,
           &res, &an_unv);
    stud->nom =(unsigned char*) strdup(nom);
    stud->prenom =(unsigned char*) strdup(prenom);
    stud->cin =(unsigned char*) strdup(cin);
    stud->cne =(unsigned char*) strdup(cne);
    stud->naiss.day = day;
    stud->naiss.month = month;
    stud->naiss.year = year;
    stud->reserve = res;
    stud->annee_univ = an_unv;

    return ((Student*)stud);
}

Dossier *readDossier(FILE *fl) {
    Student *stud = readStudent(fl);
    Dossier *ds = initDossier(stud);
    int ind = 0, //index to current Note
    i, j;
    float n1, n2; // n1->note normal; n2->note du rattrapage
    int nbr_notes = 16*3;
    if (stud->reserve) nbr_notes+=16;
    while(ind < nbr_notes) {
        fscanf(fl, "%f;",&n1);
        (n1 < 12)?
            fscanf(fl, "%f;",&n2)
            :
            (n2 = 0);
        i = ind / 16; // line index
        j = ind % 16; // column index
        ds->notes[i][j] = init_Note(n1, n2);
        ind++;
    }
    return ((Dossier*) ds);
}

