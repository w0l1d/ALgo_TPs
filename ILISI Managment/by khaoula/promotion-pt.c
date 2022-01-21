#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.c"

typedef struct promotion {
etudiant etu;
struct promotion *svt;
} promotion;


promotion *init_promotion_pt()
 {
	promotion *pro;
	pro=(promotion*)malloc(sizeof(promotion));
	if(!pro) 
	{
		printf("erreur !!");
		exit(-1);
	}
	pro=NULL;
return ((promotion*)pro);
}

//nombre des etudiants dans une promotion
int nb_etudiant_pro_pt(promotion *pro)
{
	int nbr=0;
	promotion *pt;
	pt=pro;
	while(pt)
	{
		nbr++;
		pt=pt->svt;
	}
	return((int)nbr);
}

//creer nouveau elm
promotion *creer_elm(etudiant e)
 {
	promotion *NE;
	NE=(promotion*) malloc(sizeof(promotion));
	NE->etu=e;
	NE->svt=NULL;	
return ((promotion*)NE);
}

//Afficher tous les etudiants
promotion *print_promotion_pt(promotion *pro) 
{
	promotion *pt;
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	pt=pro;
	while(pt)
	{ 
	print_etudiant(pro->etu); printf("--\n");
	pt=pt->svt;
	}
	return((promotion*)pro);
}
		

//Ajout a fin de la liste
promotion *add_etudiant_pt(etudiant e, promotion *pro)
{
	promotion *pt,*NE;
	NE=creer_elm(e);
	
	//si la liste est vide (1er element)
	if(!pro) { ;pro=NE;//return ((promotion*)pro);
	}
	//il existe au moins un element
	else 
	{
		while(pt->svt) pt=pt->svt;
		pt->svt=NE;
		;
	}	
	pro=print_promotion_pt(pro);return ((promotion*)pro);
}
	


//Etudiants admis
void print_admis_pt(promotion *pro) 
{
	promotion *pt;
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	pt=pro;
	while(pt)
	{
	 if (((pt->etu.moy) >=12.0)&&(nb_des_note_inf(&pro->etu)<4))
		{
	 	print_etudiant(pro->etu);
	 	printf("--\n");
	 	pt=pt->svt;
		}
	}
}

//Etudiants echoue (moy<12)
void print_echoue1_pt(promotion *pro) 
{
	promotion *pt;
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	pt=pro;
	while(pt)
	{
	 if ((pt->etu.moy) < 12.0)
		{
	 	print_etudiant(pro->etu);
	 	printf("--\n");
	 	}
	pt=pt->svt;
	}
}

//Etudiants echoue meme si la moy>12)
void print_echoue2_pt(promotion *pro) 
{
	promotion *pt;
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	pt=pro;
	while(pt)
	{
	 if (((pt->etu.moy) >= 12.0)&&(nb_des_note_inf(&pro->etu)>4))
		{
	 	print_etudiant(pro->etu);
	 	printf("--\n");
	 	}
	pt=pt->svt;
	}
}

//afficher le majorant

void print_maj_pt(promotion *pro) 
{
	promotion *pt,*NE;
	
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	NE=pt=pro;
	NE->svt=NULL;
	while(pt)
	{
	 if (((pt->etu.moy) >= 12.0)&&(nb_des_note_inf(&pro->etu)<=4))
		{
	 	if((pt->etu.moy)>(NE->etu.moy))
	 	free(NE);
	 	NE=pt;
	 	NE->svt=NULL;
	 
		}
	pt=pt->svt;
	}
	print_etudiant(NE->etu);
}

//chercher un etudiant par son nom

void chercher_nom(char nom[64] , promotion *pro) 
{
	promotion *pt;
	if(!pro) 
	{
		printf("liste vide!!");
		return;
	}
	pt=pro;
	while(pt)
	{
	if (!strcmp(pt->etu.nom, nom))
	{
		print_etudiant(pt->etu);
		break;
	}
	pt=pt->svt;
 	}
	printf("etudiant non trouve !\n");
	return;
}	

