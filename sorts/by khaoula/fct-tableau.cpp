#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
# define max_elm  35
typedef struct
{
int tab[max_elm];
int nb_elm;
}TAB;

///***************************************fct tableau******************************************************

//la fct creer TABLEAU 
TAB* createTab()
{
    TAB *tab = (TAB*) malloc(sizeof(TAB)); // allocation de la memoire
    tab->nb_elm = 0;  // initialiser le nombre des element a 0
    if (!tab)  //si tab n'existe pas 
    {
        printf("Erreur de location de la memoire");
        exit(-1);//sortir du prog
    }
    return ((TAB*)tab) ;
}//fin fct createTab

 
// fct inserer un elemet en queue 
int inserer_queue(TAB *tab, int val)
{
    //tab n'exist pas
    if (!tab) return ((int)-1);
    //Liste est saturee
    if (max_elm == tab->nb_elm) return((int)-2);
    // inserer dans la fin du tableau
    tab->tab[tab->nb_elm++] = val;
    return((int) 1); 
}//fin fct inserer_queue

// fct affiche le contenu de la liste 
int affiche_TAB(TAB *tab)
{     int i ;
    //liste n'exist pas
    if (!tab) return((int) -1);
    // Liste est vide
    if (!tab->nb_elm) return((int)0) ;
	// boucle pour afficher elementpar element
    for (i = 0; i < tab->nb_elm; ++i)
       {
		 printf("\t %d", tab->tab[i]);
       }
       printf("\n");
}


/// fct inserer un elemet a une posotion donnee
int inserer_position(TAB *liste, int val, int pos)
{ int i;
    //liste n'exist pas
    if (!liste) return ((int)-1);
    //Liste est saturee
    if (max_elm == liste->nb_elm) return((int) -2);
    //position non valide
    if ((pos < 1) || (liste->nb_elm+1 < pos)) return((int)-3) ;
    //sinon
	pos--;// pour trouver l'indice
	//faire une boucle pour decaler les elemet du tableau
    for( i = liste->nb_elm; i > pos; --i)
        liste->tab[i] = liste->tab[i-1];
    // inserer le nouveau element
    liste->tab[pos] = val;
    //incrementer le nombre des elemet
    liste->nb_elm++;

    return ((int)1);
}//fin fct inserer_position



// fct qui supprime  l'element qui se trouve dans une position p donnee 
int supprimer_position(TAB *liste, int pos)
{ int i ;
    //liste n'exist pas
    if (!liste) return((int)-1) ;
    //position non valide
    if ((pos < 1) || ((liste->nb_elm)+ 1< pos)) return((int)-3) ;
    //faire une boucle pour decaler les elemet du tableau
    for( i = pos-1; i < liste->nb_elm; i++)
        liste->tab[i] = liste->tab[i+1];
   // decrementer le nombre d'element
    liste->nb_elm--;
    return((int)1) ;//supprition effectuer
}// fin fct supprimer_position



 /// rechercher si un element existe dans la liste  
int rechercher_elem(TAB liste,int elem)
{int i;
// verifier si la liste est vide
 if(liste.nb_elm==0)
   { // printf("\n liste vide !!");
     return((int)0);
   }
   //boucle pour comparer chaque element de la liste avec la valeur entree
for(i=0;i<liste.nb_elm;i++)
 {   if (liste.tab[i]==elem)// trouver le 1er element = val
      {
	  //afficher sa position 
       return ((int)(i+1));
	  }
 }//fin fct

//element n'esxiste pas dans la liste 
return ((int)-4);

}//fin fct


