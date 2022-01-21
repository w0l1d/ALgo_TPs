#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// definir la structure List
typedef struct PtList 
{
    int val;
    struct PtList *svt;
    struct PtList *prc;
}PList;


// la fct creer liste 
PList * creer_liste(int elem)
{ 
// declarer une variable de type pt
PList* NE;
// allocation de la memoire
NE=(PList*)malloc(sizeof(PList));
//si il y a un probleme d'allocation 
if(!NE)
 	return((PList*)NULL);//retourner null
 	
//si l'allocatin est bien passer
//initialisation
 NE->val=elem; 
 NE->svt=NULL;
 NE->prc=NULL;
 //retourner l'element de type PList
  return((PList*)NE);
}//fin fct 

//inserer en queue de la List
PList *inserer_queue_PList(PList *list, int val) {
    PList *ne;
    ne = creer_liste(val);

    //cas ou la liste n'existe pas
    if(!list)
    return((PList*) ne);
    

    PList *pt = NULL;
    for(pt = list; pt->svt; pt = pt->svt);
	ne->prc = pt;
    pt->svt = ne;
    
    
    return ((PList*) list);

}

//fct taille liste
int taille_pliste(PList *list)
{ // declaration d'un pt
    PList *pt;
    // initialiser la variable compt a zero
    int compt=0;
    //cas ou la iste n'existe pas
    if(!list)
    { printf("liste n'existe pas !! \n");
        return((int)-2);
    }
// si la liste existe
    pt=list;
//tant que pt est != de null
    while(pt)
    {
// incrementer le compteur
        compt++;
        pt=pt->svt;
    }
    return((int)compt);
}//fin fct

// Fct affiche tout les element de la liste
void afficher_plist(PList *list)
{
    // declaration des variable
    PList *pt;//pour parcourir la liste
    int compt;// donner les positions des elements
    //list n'exist pas
    if (!list)
       exit(-1) ;
    //Liste existe
    pt=list;
    while(pt)//tant que ot n'est pas null
    {
        printf("%d\t", pt->val);
        pt=pt->svt;
    }
   printf("\n");
}//fin fct

//fct retourne le dernier element
	PList* dernier_elm(PList* liste)
	{
	//list n'exist pas
	if (!liste)
	   exit(-1) ;
	//Liste existe
	
	PList *pt=liste;
	
	while(pt->svt)
	pt=pt->svt;
	return((PList*)pt);
	}

		

	



