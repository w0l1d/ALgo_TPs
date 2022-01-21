#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fct-pointeur.cpp"  
#include "fct-tableau.cpp"  




// la fonction qui permi de faire un echange entre deux variable

void echange(int *a,int *b)
{
int tmp;
	tmp= *a;
	*a =*b;
	*b=tmp;
}

void tri_a_bulle_TAB(TAB *tableau)
{ 
	int i,j;
	char trie;
while(!trie)
		for(i=(tableau->nb_elm-1);i>=0;i--)
		{
			trie=1;
			for(j=0;j<i;j++)	
			{
				if(tableau->tab[j+1]<tableau->tab[j])
				{
					echange(&(tableau->tab[j]),&(tableau->tab[j+1]));
				 	trie=0;
			 	}
			 	
			 	affiche_TAB(tableau);
	
			}
		
			
		}
	
}

PList *tri_a_bulle_pt(PList *liste)
{	
	PList *pt1,*pt2;
	char ptrie=0;
	while(!ptrie)
	{ 
	
	for(pt1=dernier_elm(liste);pt1->prc;pt1=pt1->prc)
		{	ptrie=1;
		 
		for(pt2=liste;pt2!=pt1;pt2=pt2->svt)
		{
			if((pt2->svt->val)<pt2->val)
			{	 
			echange(&(pt2->svt->val),&(pt2->val));
			ptrie=0;
			}
		
		}
			
		}
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
	tri_a_bulle_TAB(tab);
	affiche_TAB(tab);
	printf("\n");
	
	
PList* liste=inserer_queue_PList(liste,9) ;
 liste=inserer_queue_PList(liste,8) ;
 liste=inserer_queue_PList(liste,3) ;
liste=inserer_queue_PList(liste,4) ;
 liste=inserer_queue_PList(liste,1) ;
 afficher_plist(liste);
 printf("\n");
 liste=tri_a_bulle_pt(liste);
 afficher_plist(liste);
}

