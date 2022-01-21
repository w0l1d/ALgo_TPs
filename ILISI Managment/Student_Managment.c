//
// Created by W0L1D on 1/21/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"



Student* getStudent(FILE *fl) {
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

