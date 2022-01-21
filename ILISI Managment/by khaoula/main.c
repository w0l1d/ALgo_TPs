//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "promotion-pt.c"
void main() 
{
	char ch;
	promotion *pro =init_promotion_pt();
	etudiant e,r;
	char nom[64];
	do 
	{
	printf("\n--------------------------------\n"
		"1: ajouter un nouvel etudiant \n"	
		"2: Afficher tous les etudiants \n"	
		"3: Afficher les etudiants admis \n"	
		"4: Recherche par matricule on affiche le premier trouve \n"	
		"5: Moyenne generale d'un etudiant (avec maticule) \n"	
		"6: Recherche par nom \n"	
		"7: Afficher les etudiants majorants \n"	
		"8: Trier les etudiants \n "	
		"9: Afficher les etudiants qui ont au moins deux notes inferieure a 10 \n"	
		"10: Saisir un nouvel etudiant en l'ajoutant a la bonne place(par nom)\n"	
		"0: Quitter\n"
		"\n--------------------------------\n");

	printf(">> ");
	scanf("%d%*c", &ch);//getchar();

	
	switch (ch)
	{	
	case 1:
		e = scan_etudiant();
		pro=add_etudiant_pt(e, pro);
		
		break;
	case 2:
		pro= print_promotion_pt(pro);
		break;
	case 3:
		print_admis_pt(pro);
		break;
	
	case 6:
		printf("nom: ");
		gets(nom);
		chercher_nom(nom, pro);
		break;

	case 7:
		print_maj_pt(pro);
		break;
//	case 8:
//tri_alpha_qsort(&r);
//break;
//case 9:
//print_refus(&r);
//break;
//case 10:
//e = scan_etudiant();
//add_etudiant(&e, &r);
//break;
}
} while(ch);

}
