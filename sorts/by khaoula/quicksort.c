#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fct-pointeur.cpp"  
#include "fct-tableau.cpp" 

void echange(int *a,int *b)
{
int tmp;
	tmp= *a;
	*a =*b;
	*b=tmp;
}

int partition_TAB(TAB *tableau,int gauche,int droit)
{
	int pivot;
	
	pivot=tableau->tab[gauche];
	printf("\n  pivot =%d\n",pivot);
	while(gauche<droit)
    {
		echange(&tableau->tab[gauche],&tableau->tab[droit]);
			affiche_TAB(tableau);
		while(tableau->tab[gauche]<= pivot && (gauche <= droit))
		gauche++;	affiche_TAB(tableau);
		while((tableau->tab[droit])>pivot && (gauche <= droit))
		droit--;	affiche_TAB(tableau);
	}
	return((int)droit);
}
		
void quicksort_TAB(TAB *tableau,int gauche,int droit)
{	
	int elm;
	if(gauche<droit)
	{
		elm=partition_TAB(tableau,gauche, droit);
		affiche_TAB(tableau);
 		quicksort_TAB(tableau,gauche,elm-1);
		quicksort_TAB(tableau,elm+1,droit);
		
	}

}

//*********************************pt********************************

PList *partition_pt(PList*tete, PList*queue, int pivot)	
 {
    int sorted = 1;
    PList *gauche = tete, *droit = queue;
    while (gauche != droit)
    {
        while (gauche->val < pivot) gauche = gauche->svt;
        while ((droit->val >= pivot)
                &&
                (droit != gauche))
            droit = droit->prc;
        if (gauche != droit)
        {
            echange(&gauche->val, &droit->val);
            sorted = 0;
        }
    }
    if (sorted == 1)
        return((PList*)tete->svt);
    return((PList*)gauche);
	    
 }
	
	void quicksort_pt(PList*tete, PList*queue)
	{
	    PList *pt;
	    int pivot;
	    if (tete != queue)
	    {
	       if (tete->val < tete->svt->val)
		   pivot = tete->svt->val;
	      else   pivot = tete->val;
	        pt = partition_pt(tete, queue, pivot);
	        quicksort_pt(tete, pt->prc);
	        quicksort_pt(pt, queue);
	    }
	}


		
		

int main()
{
	TAB *tab=createTab();
	inserer_queue(tab, 1);
	inserer_queue(tab, 9);
	inserer_queue(tab, 3);
	inserer_queue(tab, 3);
	inserer_queue(tab, 7);
	affiche_TAB(tab);
	printf("\n");
	quicksort_TAB(tab,0,(tab->nb_elm-1));
	affiche_TAB(tab);
	printf("\n");
	
//	PList* liste=NULL;
//	liste=inserer_queue_PList(liste,71) ;
// liste=inserer_queue_PList(liste,8) ;
// liste=inserer_queue_PList(liste,3) ;
//liste=inserer_queue_PList(liste,4) ;
// liste=inserer_queue_PList(liste,1) ;
// afficher_plist(liste);
// printf("\n");
//
// quicksort_pt(liste,dernier_elm(liste));
// afficher_plist(liste);
}
		
	

