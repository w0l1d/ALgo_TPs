//
// Created by W0L1D on 1/3/2022.
//




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fct-pointeur.cpp"
#include "fct-tableau.cpp"

//pour trouver le petit element dans un tableau
//comparer a chaque fois 2elements a la position i et i+1  
//supprimer le plus grand et passer au elements a la position i+2 et i+3 ( ordre avant supp)
void triTournoi1(TAB *t,int i)
{
    int nbComp=0;//compter le nombre supp
    while(t->nb_elm-nbComp >= 1) // repeter jusqu a avoir un seul element dans le tableau
    {i=i%(t->nb_elm-1);//pour avoir un indice entre zero et nb-elm-1
        nbComp++;
        if(t->tab[i] <= t->tab[i+1])
        {
            supprimer_position(t, i+2);
            affiche_TAB(t);
        }

        else
        {
            supprimer_position(t, i+1);
            affiche_TAB(t);
        }


    }
}

void triTournoi(TAB *t)
{TAB *tmp= createTab();//creer un tableau tmp pour trouver le plus petit element a chaque tour
    int nbComp = 0,//nb de comparaisons effectuees
    nbComp1= 0;
    int nbelm = t->nb_elm,// nb d element initial
    nbtmp;
    int i,j,l=0;// a partir de la position l dans le tableau principal les elements 
    // n'est pas encore trie
    while(l<=t->nb_elm-1)//tanque l <= a nombre elements du tableau principal 

    { int nb=(int)((t->nb_elm-l)/2);//le nombres des couples dans le tableau principal
        i=l;//commancer par l indice l (la partie n'est pas encore trie) 
        nbComp = 0;//nombre des tour dans le tableau principal
        nbComp1= 0;//nombre des tour dans le tableau tmp
        l++;
        while(nbComp<nb)

        {
            printf("\n  i =%d\n",i );
            nbComp++;printf("\n  nbComp =%d\n",nbComp );//nombre des tour dans le tableau principal
//pour trouver le petit element dans le tableau principal avec la mth tournoi il faut
//comparer a chaque fois 2elements a la position i et i+1  
//inserer le plus petit dans le tableau tmp  
//et passer a la comparaison des elements a la position i+2 et i+3 ( ordre avant supp)
            if(t->tab[i] <= t->tab[i+1])
            { inserer_queue(tmp,t->tab[i]);// inserer dans tableau tmp 

                affiche_TAB(tmp);
            }

            else
            {	inserer_queue(tmp,t->tab[i+1]);// inserer dans tableau tmp 

                affiche_TAB(tmp);
            }

            i=i+2;//pour passer a la 2eme comparaison
        }
        if(i==t->nb_elm-1)	inserer_queue(tmp,t->tab[i]);//nombre impair dans le tableau principal

        printf("\n le tableau tmp \n" );
        affiche_TAB(tmp);


        while(tmp->nb_elm > 1 ) // boucler jusqu a vider le tableau tmp
        {						//garder que le petit element
            triTournoi1(tmp,l);affiche_TAB(tmp);

        }
        printf("\n le tableau tmp \n" );
        affiche_TAB(tmp);
        // chercher la position de l element le plus petit 
        int pos=rechercher_elem(*t,tmp->tab[0])-1;
        if((pos%2)==1) //la position du petit element est impair dans le tableau principal(a droite) 
        {supprimer_position(t, pos+1); //le suprimer du tableau principale
            if(l<t->nb_elm-l-1)//pour ne pas avoir une boucle infini si on un qu un seul element
                inserer_position(t, t->tab[pos-1],  pos+1);
            //inserer l element a gauche a sa place
        }
        else //position pair dans le tableau principal (a gauche)
        {supprimer_position(t, pos+1);//le suprimer du tableau principale 
            if(l<t->nb_elm-l-1)
                inserer_position(t, t->tab[pos],  pos+1);
            //inserer l element a droite a sa place
        }

        inserer_position(t, tmp->tab[0], l);
        //inserer l element (le plus petit dans le tableau a la position l
        printf("\n tableau principal \n" );
        affiche_TAB(t);
        //si on a inserer un element pour faire la comparaison il faut le supprimer 
        //pour continuer a comparer le rester du tableau a partir de la position l
        if(nbelm != t->nb_elm)
            supprimer_position(t, pos+2); affiche_TAB(t);
        tmp=createTab();//vider le tableau tmp 

    }
}


/*programme  principal */
int main ( )
{
    TAB *tab=createTab();
    inserer_queue(tab, 19);inserer_position(tab,71,1);inserer_position(tab,8,1);
    inserer_position(tab,-88,1);
    inserer_position(tab,88,1);inserer_position(tab,87,1);inserer_position(tab,-87,1);
    inserer_position(tab,85,1);inserer_position(tab,-86,1);
    inserer_position(tab,81,1);inserer_position(tab,-81,1);


    clock_t tic = clock();

    affiche_TAB(tab);
    printf("\n");
    triTournoi(tab);

    affiche_TAB(tab);
    printf("\n\n");
    clock_t toc = clock();

    printf("Elapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);



}

