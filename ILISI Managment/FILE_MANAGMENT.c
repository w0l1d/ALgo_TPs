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
    FILE *students_File, *modules_File;
    students_File=fopen("P:\\Study\\ILISI\\S1\\ALgo"
                        "\\practice\\ILISI Managment\\students.txt",
                        "r");
    modules_File=fopen("P:\\Study\\ILISI\\S1\\ALgo\\"
                       "practice\\ILISI Managment\\modules.txt",
                       "r");

    int ord;
    Dossier *doss[3] = {NULL, NULL, NULL};
    char *modules[3][16];
    readModules(modules_File, modules);
    fclose(modules_File);

    printf("\nEntrer l'ordre de tri des etudiants (0:alphabetique, 1:merite) : ");
    scanf("%d", &ord);
    while ((ord != 0) && (ord !=1)) {
        printf("\n0 -> alphabetique\n1 -> merite\nRentrer l'ordre de tri des etudiants : ");
        scanf("%d", &ord);
    }

    (ord)?
        orgDossiers_merite(students_File, doss)
    :
        orgDossiers_alpha(students_File, doss);

    fclose(students_File);

    main_menu(doss, modules);

    return 0;
}

