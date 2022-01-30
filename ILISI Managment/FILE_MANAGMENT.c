//
// Created by W0L1D on 1/21/2022.
//
#include <stdio.h>
#include "Student_Managment.c"




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
            printf("[%d]=%f", j+1, doss->notes[i][j]);
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
    int ord;
    Dossier *doss[3];
    printf("\nEntrer l'ordre de tri des etudiants (0:alphabetique, 1:merite) : ");
    scanf("%d", &ord);
    while ((ord != 0) && (ord !=1)) {
        printf("\n0 -> alphabetique\n1 -> merite\nRentrer l'ordre de tri des etudiants : ");
        scanf("%d", &ord);
    }

    (ord)? orgDossiers_merite(f, doss):orgDossiers_alpha(f, doss);

    main_menu(doss);
    fclose(f);
    return 0;
}

