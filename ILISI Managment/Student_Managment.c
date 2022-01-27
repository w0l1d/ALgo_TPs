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
    int nbr_annee;
    nbr_annee = ds->student->annee_univ;
    nbr_annee += (ds->student->reserve)?1:0;

    return ((float) ds->moy[nbr_annee-1]);
}

int A_Reussi(Dossier *ds) {
    return (ds->inf12 < 4) && !(ds->inf10) && (getMoyenne(ds) > 12);
}


Dossier *insertDossier(Dossier *list, Dossier *ds) {
    if (!list)
        return ((Dossier*) ds);
    // X est l'etudiant a insere
    // U est l'etudiant en tete de la liste
//    if(((getMoyenne(ds) > getMoyenne(list)) && A_Reussi(ds)) // si X a reussi et il a une moyenne > Y
//    || (!A_Reussi(list) && A_Reussi(ds)) // si X a reussi et Y non
//       || (!A_Reussi(ds) && !A_Reussi(list) && (getMoyenne(ds) >= 12) && (getMoyenne(list) < 12))
//          || (!A_Reussi(ds) && !A_Reussi(list) && (getMoyenne(ds) >= 12) && (getMoyenne(list) >= 12) && !ds->inf10))
    if(
            (A_Reussi(ds) && ((getMoyenne(ds) > getMoyenne(list)) || !A_Reussi(list)))
       || (!A_Reussi(ds)
            && !A_Reussi(list)
            && (getMoyenne(ds) >= 12)
            && ((getMoyenne(list) < 12)) || ((getMoyenne(list) >= 12) && !ds->inf10)
            )
            )
    {

        ds->svt = list;
        return ((Dossier *) ds);

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

Note *init_Note(float normal) {
    Note *nt = (Note*) malloc(sizeof(Note));
    if (!nt) {
        printf(ERROR_ALL_MEM_NOTE);
        exit(-1);
    }
    nt->normal = normal;
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
    ind2 = 0, // indique l'annee actuel
    i, j;
    float note, moyen; // n1->note normal; n2->note du rattrapage
    int nbr_annee = stud->annee_univ;
    nbr_annee += (stud->reserve)?1:0;
    do {
        moyen = 0;
        for (ind = 0; ind < 16; ind++) {
            //statistique des notes seuelement pour la dernier annees
            if (nbr_annee == 1)
                if (note < 12) {
                    if (note < 10)
                        ds->inf10 = 1;
                    else
                        ds->inf12++;
                }

            fscanf(fl, "%f;", &note);

            i = ind / 16; // line index // annee du note
            j = ind % 16; // column index // module du note
            ds->notes[i][j] = note;
            moyen += note;
        }
        moyen /= 16;
        ds->moy[ind2++] = moyen;

        fscanf(fl, "%*[\n];");
    } while(--nbr_annee);

    return ((Dossier*) ds);
}

void orgDossiers(FILE *f, Dossier *ds[3]) {
    Dossier *tmp;

    while ((tmp = readDossier(f)))
        ds[tmp->student->annee_univ-1] = insertDossier(ds[tmp->student->annee_univ-1], tmp);
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


void Menu() {
    printf(
            "\n******************************************\n"
            "***********Statistiques Menu**************\n"
            "******************************************\n"
            "1-> tous les etudiants"
            "2-> les etudiant ayant reussi"
            "3-> les etudiant ayant des notes entre 10 et 12"
            "4-> les etudiant ayant des notes < 10"
            "5-> les etudiant n'ayant pas des notes < 10, mais ont echoues"
            );



}
