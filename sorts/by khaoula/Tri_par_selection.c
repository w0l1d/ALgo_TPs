#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fct-pointeur.cpp"  
#include "fct-tableau.cpp" 


int chercher_min_TAB(TAB *tableau, int indice)
{
	int i,min=indice;
	for(i=indice+1;i<(tableau->nb_elm-1);i++)
	{
		if(tableau->tab[i]<tableau->tab[min])
		min=i;
	}
return((int)min);
}

void echange(int *a,int *b)
{
int tmp;
	tmp= *a;
	*a =*b;
	*b=tmp;
}
void Tri_par_selection_TAB(TAB *tableau)
{
	int i,min;
	for(i=0;i<tableau->nb_elm-1;i++)
	{
		min=chercher_min_TAB(tableau,i);
		printf("\n les min=%d",tableau->tab[min]);
		if (min!=i)
		echange(&tableau->tab[i],&tableau->tab[min]);
		affiche_TAB(tableau);
	}	
}

//*********************************pt********************************

PList *chercher_min_liste(PList *liste)
{
	PList *tmp,*min_pt=liste;
	tmp=liste;
	while(tmp)
	{
		if(tmp->val < min_pt->val)
		min_pt=tmp;
		tmp=tmp->svt;
	}
return((PList*)min_pt);
}

PList *Tri_par_selection_pt(PList *liste)
{
	PList *tmp,*min_pt;
	for(tmp=liste;tmp->svt;tmp=tmp->svt)
		{ 
		min_pt=chercher_min_liste(tmp);
		printf("\n le min=  %d ",min_pt->val);
			printf("\n le tmp=  %d ",tmp->val);
		if(tmp!=min_pt)
		
		echange(&tmp->val,&min_pt->val);
		afficher_plist(liste);
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
		Tri_par_selection_TAB(tab);
		affiche_TAB(tab);
		printf("\n");
		printf("\n Tri_par_selection avec poiteur \n\n");
		 
	PList *liste=NULL;
	liste=inserer_queue_PList(liste,9) ;
	
	 liste=inserer_queue_PList(liste,8) ; 
	 liste=inserer_queue_PList(liste,3) ; 
	liste=inserer_queue_PList(liste,4) ; 
	 liste=inserer_queue_PList(liste,1) ;
	afficher_plist(liste);
	 printf("\n");
	 liste=Tri_par_selection_pt(liste);
	 afficher_plist(liste);
}
			
			
	
	
	


	
