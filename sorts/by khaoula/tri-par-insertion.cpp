#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fct-pointeur.cpp"  
#include "fct-tableau.cpp"  
	
	void tri_par_insertion_tab(TAB *tableau)
{
int i,j,cle;
	for(i=1;i<(tableau->nb_elm-1);i++)
	{
		cle=tableau->tab[i];
		printf("\n cle=%d",cle);
		j=i-1;
		while((j>=0)&&(cle<tableau->tab[j]))
		{
			tableau->tab[j+1]=tableau->tab[j];
			affiche_TAB(tableau);
			j=j-1;
		}
	
	tableau->tab[j+1]=cle;
	}
}
void echange_insertion(int *a,int *b)
{
int tmp;
	tmp= *a;
	*a =*b;
	*b=tmp;
}
PList *tri_par_insertion_pt(PList* liste)
{
	PList *pt1,*pt2,*pt;
	int tmp;
	pt1=liste;
	 printf("\n 1 pt1\n");
	afficher_plist(pt1);
	for(pt1=pt1->svt;pt1;pt1=pt1->svt)
	{
	printf("\n 2pt1\n");
	afficher_plist(pt1);
	pt2=pt1;
	printf("\n 3 pt2 \n");
	afficher_plist(pt2);
	tmp=pt1->val;
	printf("\n cle=%d",tmp);
	while((pt2->prc->val)>(pt2->val ))
	{//(pt2->prc)&&(tmp->val<pt2->val )

echange_insertion(&(pt2->prc->val),&(pt2->val));
afficher_plist(pt2);
pt2=pt2->prc;
	if(!pt2->prc) {break;}
	  

	
	}
	printf("\n 98 pt2 \n");
//		
//		
//	afficher_plist(pt2);
//	if(!pt2->prc){ pt2->val=tmp;}
//	
//else	pt2->svt->val=tmp;
//	
//		printf("\n 99 pt2 \n");
//	afficher_plist(pt2);
	
}
return((PList*)liste);
}

	
	
	

int main()
{
	TAB *tab=createTab();
	inserer_queue(tab, 9);
	inserer_queue(tab, 7);
	inserer_queue(tab, 3);
	inserer_queue(tab, 1);
	inserer_queue(tab, 14);
	affiche_TAB(tab);
	printf("\n");
	tri_par_insertion_tab(tab);
	affiche_TAB(tab);
	printf("\n");
	
	PList* liste=inserer_queue_PList(liste,9) ;
 liste=inserer_queue_PList(liste,8) ;
 liste=inserer_queue_PList(liste,3) ;
liste=inserer_queue_PList(liste,4) ;
 liste=inserer_queue_PList(liste,1) ;
 afficher_plist(liste);
 printf("\n");
 liste=tri_par_insertion_pt(liste);
 afficher_plist(liste);
}
