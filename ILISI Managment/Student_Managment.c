//
// Created by W0L1D on 1/21/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "error_msg.h"

#define max(a,b) ( (a > b) ? (a) : (b))

float getMoyenne(Dossier *ds) {
    float moy = 0;
    int nbr_annee;
    nbr_annee = ds->student->annee_univ;
    nbr_annee += (ds->student->reserve)?1:0;
    switch(nbr_annee) {
        case 4: moy += ds->moy[3];
        case 3: moy += ds->moy[2];
        case 2: moy += ds->moy[1];
        case 1: moy += ds->moy[0];
    }
    moy /= nbr_annee;
    return ((float) moy);
}


Dossier *insertDossier(Dossier *list, Dossier *ds) {
    if (!list)
        return ((Dossier*) ds);
    if(getMoyenne(ds) > getMoyenne(list)) {
        ds->svt = list;
        return ((Dossier*) ds);
    }
    list->svt = insertDossier(list->svt, ds);
    return ((Dossier*) list);
}

Dossier *initDossier(Student *st) {
    Dossier *ds;
    ds = (Dossier*) malloc(sizeof(Dossier));
    if (!ds) {
        printf(ERROR_ALL_MEM_DOSSIER);
        exit(-1);
    }
    ds->student = st;
    ds->svt = NULL;
    ds->moy[0] = 0;
    ds->moy[1] = 0;
    ds->moy[2] = 0;
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
    Student *stud = NULL;
    char nom[30],prenom[30], cin[15], cne[15];
    unsigned int day, month, year, res, an_unv;

    //STUDENT_PATTERN = "%30[^;];%30[^;];%8[A-Za-z0-9];%10[A-Za-z0-9];%d;%d;%d;%d;%d\n"
    int rst = fscanf(fl, STUDENT_PATTERN,
                     nom, prenom, cin, cne, &day,
                     &month, &year, &res, &an_unv);

    if (rst == EOF)
        return ((Student*) NULL);

    stud = (Student*) malloc(sizeof(Student));
    stud->nom = (char *) strdup(nom);
    stud->prenom = (char *) strdup(prenom);
    stud->cin = (char *) strdup(cin);
    stud->cne = (char *) strdup(cne);
    stud->naiss.day = day;
    stud->naiss.month = month;
    stud->naiss.year = year;
    stud->reserve = res;
    stud->annee_univ = an_unv;

    return ((Student*)stud);
}


/**
 *
 * @param fl
 * @return
 */
Dossier *readDossier(FILE *fl) {
    Student *stud = readStudent(fl);
    if (!stud)
        return ((Dossier*) NULL);
    Dossier *ds = initDossier(stud);
    int ind, //index to current Note
    ind2 = 0,
    i, j;
    float n1, n2, moyen; // n1->note normal; n2->note du rattrapage
    int nbr_notes = stud->annee_univ;
    nbr_notes += (stud->reserve)?1:0;
    read_notes:
    moyen = ind = 0;
    while(ind < 16) {
        fscanf(fl, "%f;",&n1);
        (n1 < 12)?
            fscanf(fl, "%f;",&n2)
            :
            (n2 = 0);
        i = ind / 16; // line index
        j = ind % 16; // column index
        ds->notes[i][j] = init_Note(n1, n2);
        moyen += max(n1, n2);
        ind++;
    }
    moyen /= 16;
    nbr_notes--;
    ds->moy[ind2++] = moyen;

    fscanf(fl, "%*[\n];");
    if (nbr_notes)
        goto read_notes;

    return ((Dossier*) ds);
}

void orgDossiers(FILE *f, Dossier *ds[3]) {
    Dossier *tmp;

    while ((tmp = readDossier(f)))
        ds[tmp->student->annee_univ] = insertDossier(ds[tmp->student->annee_univ], tmp);
}



void readModules(FILE *f) {

    int modIndex = 0, modsize = 0;
    int i,j;
    char str[100], c;

    while((c=(char)fgetc(f))!=EOF) {

        if (c == DELIM) {
            str[modsize] = '\0';
            i = modIndex/16;
            j = modIndex%16;
            if ((i > 2) || (j > 15)) {
                printf("\n\nerreur les modules stockes depasse le nombre predefini\n");
                printf("\ni = %d, j =%d\n", i, j);
                exit(0);
            }
            modules[i][j] =(char *) strdup(str);
            modIndex++;
            modsize = 0;
            continue;
        }
        str[modsize] = c;
        modsize++;
    }
}
