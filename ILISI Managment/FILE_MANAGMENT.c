//
// Created by W0L1D on 1/21/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int main() {
    FILE *f;
    f=fopen("P:\\Study\\ILISI\\S1\\ALgo\\practice\\ILISI Managment\\students.txt","r");

    Student *std;

    while ((std = readStudent(f)) != NULL) {
        print_student(std);
    }
    fclose(f);
    return 0;
}

