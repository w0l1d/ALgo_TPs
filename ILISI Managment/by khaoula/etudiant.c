//etudiant.c
#include <stdio.h>
#include <stdlib.h>
#include "date.c"
#define MAXmodule 16

typedef struct etudiant {
char nom[64];
char prenom[64];
char cin[10];
date date_naissance;
float notes[MAXmodule];
float moy;
} etudiant;

//scan etudiant
etudiant scan_etudiant() {
int i;
etudiant e;
printf("Nom :\n  ");

gets(e.nom);

printf("Prenom :\n  ");
//scanf("%s",e.prenom);scanf("%c");
gets(e.prenom);
printf("Date de naissance:\n");
e.date_naissance = scan_date();getchar();
printf("CIN :\n ");
gets(e.cin);getchar();
//initialisation des notes
for (i=0; i<MAXmodule; e.notes[i++]=-1) ;
//initialisation du moyenne
e.moy=-1;
return((etudiant)e) ;
}
//calcule de moyenne
void moyenne(etudiant *e) {
int i;
float s = .0;
for (i=0; i<MAXmodule; i++) {
s += e->notes[i];
}
e->moy=s/MAXmodule;

}

//saisi les notes d un etudiant
void note_etudiant(etudiant *e)
{
	int i;
	for (i=0; i<MAXmodule;i++ ) 
	{
	printf("Note du module %d: ", i+1);
	scanf("%f", e->notes[i]);
	}
	//remplir le champ moy
	 moyenne(e);
}
//afficher un etudiant
void print_etudiant(etudiant e) {
int i;
printf("Nom et Prenom : %s %s\n", e.nom, e.prenom);
printf("Date de naissance: ");
print_date(e.date_naissance);
printf("notes: ");
for (i=0; i<MAXmodule; i++) 
{	if((e.notes[i])==-1) 
	printf("la note du module %d n est pas encore inserer \n",i+1);
	else printf(" module %d = %.2f ",i+1, e.notes[i]);
}
if((e.moy)==-1) 
printf("la moy de l annee n est pas encore dispo \n");
else ("moy de l annee : %.2f  ",e.moy);
printf("\n");
}
//fct calcule nombre des notes de modules inf a 12 et sup a 10
int nb_des_note_inf(etudiant *e)
{ int i,nb=0;
for(i=0;i<MAXmodule;i++)
if((e->notes[i]<12)&&(e->notes[i]>10)) nb++;
}
