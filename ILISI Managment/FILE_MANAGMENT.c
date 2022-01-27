//
// Created by W0L1D on 1/21/2022.
//
#include <stdio.h>
#include "Student_Managment.c"


void print_student(Student *std) {
    printf("\nStudent info \n"
           "nom = %s\n"
           "prenom = %s\n"
           "cin = %s\n"
           "cne = %s\n"
           "reserve = %x\n"
           "annee universitaire = %x\n",
           std->nom, std->prenom, std->cin,
           std->cne, std->reserve, std->annee_univ);
}


void print_dossier(Dossier *doss) {
    printf("\nDossier info \n");
    print_student(doss->student);
    int i,j,nbr_annee;
    nbr_annee = doss->student->annee_univ;
    nbr_annee += doss->student->reserve?1:0;
    for (i = 0; i < nbr_annee; ++i) {
        printf("Annee %d\n",i+1);
        show_notes:
        for (j = 0; j < 16; ++j) {
            printf("[%d]=%f", j+1, doss->notes[i][j]->normal);
            if (doss->notes[i][j]->normal < 12)
                printf("|%f", doss->notes[i][j]->ratt);
            printf("  ");
        }
        printf("\n");
        if (doss->student->reserve-1 == i) {
            printf("Annee %i de reserve\n",++i);
            goto show_notes;
        }
    }
}
int main() {
    FILE *f;
    f=fopen("P:\\Study\\ILISI\\S1\\ALgo\\practice\\ILISI Managment\\students.txt","r");
    Dossier *doss;

    while ((doss = readDossier(f)) != NULL) {
        print_dossier(doss);

    }
    fclose(f);
    return 0;
}

