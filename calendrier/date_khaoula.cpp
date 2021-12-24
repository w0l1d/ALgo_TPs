#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// fct a comme entree un entier est retourne le reste de la div de cet entier sur 4
#define mod4(x) (x)%4
// fct a comme entree un entier est retourne le reste de la div de cet entier sur 7
#define mod7(x) (x)%7
// fct a comme entree un entier est retourne le quotient de la div de cet entier sur 4
#define div4(x) (x)/4
// taableau de 12 elements represente le nombre des jours de chaque mois
int tab[12] ={31,28,31,30,31,30,31,31,30,31,30,31};
 //char *tab_jour[] ={"mardi   ","mercredi","jeudi   ","vendredi","samedi  ","dimanche","lundi   "};
//structure utiliser pour stocker le jour le mois et l annee saisi par l utilisateur
typedef struct dt
{
       int jour ;// entier pour stocker les jours
       int mois ;// entier pour stocker le mois
       int annee ;// entier pour stocker l'annee
}Date;//structure Date

/********************************************
 * la foncton initialiser()
 * entree : aucun parametre
 * sorie : un elm de type Date
 * role:elle initialise date.jour,date.mois et date.annee si
 * les caracteres saisi par lutilisateur entre'0' et '9'
 * sinon un afficher un msg d'erreur
 * ( controle seulement est ce que les caracteres est des num
 * ne controle pas la validite de la date(voir fct valide_date())
**********************************************/
Date initialiser(  )
{
    Date date;
 char store=0 ;
 // la variable store initialiser a 0 pour stocker les jours ,1 pour le mois et 3 pour l'annee
 date.jour=date.mois=date.annee=0;// initialiser a 0
 char car_lu ;// caractere lu
 while ((car_lu=getchar() )  != '\n')// repeter jusqu'à car_lu ='\n'
 { if ((car_lu>= '0' )&&(car_lu <= '9' ))// si le car_lu est un chiffre ente 0 et 9
    {
	switch ( store )
        {
        //store =0 stocker dans date.jour
        case 0 :date.jour=((date.jour*10) +(car_lu-'0')); break ;
        //store =1 stocker dans date.mois
        case 1:date.mois =(date.mois*10)+car_lu-'0';  break ;
        //store =2 stocker dans date.annee
        case 2:date.annee=(date.annee*10)+car_lu-'0';break ;
        }
     }
    //si le car_lu est UN '-' inc store pour passer au suivant
	//(car le format utiliser est jour-mois-anneee)
    else if ((car_lu=='-' ) ){store++;  }
    // car_lu n'est pas un chiffre ou '-'
    else
    { printf("caractere invalid ");
    exit(-1);
    }
}
return((Date)date);
}
/**********************************************************
fonction  Nb_Jour_Annees(Date date )
entree :  date de type  Date
sortie: entier represente nombre des jours de 1901 jusqu'à l'annee saisi
 		par l'utilisateur
 		*******************************************/
int Nb_Jour_Annees(Date date )
{
return((int)((date.annee-1901)*365+div4(date.annee-1901)) );
}
/**********************************************************
fonction  Nb_Jour_Mois(Date date)
entree :  date de type  Date
sortie: entier represente nombre des jours du mois 1 jusqu'à le mois saisi
 		par l'utilisateur
 		*******************************************/
int Nb_Jour_Mois(Date date)
{ int mois=0,i;
// variable mois pour stocker le nombres des jours

for(i=0;i<(date.mois-1);i++)
{mois=mois+tab[i];
}
// si on a i-1 sup a 1
if (i-1>1)
//si l'annee esst biss on ajoute un 1
{if(mod4(date.annee)==0) mois++;
}
return((int)mois);
}
/**********************************************************
fonction  Nb_Jour(Date date))
entree :  date de type  Date
sortie: entier represente nombre des jours Du 1-1-1901 jusqu'à la date saisi
 		par l'utilisateur
 		*******************************************/
int Nb_Jour(Date date)
{int jour;
jour=(date.jour-1)+Nb_Jour_Mois(date)+Nb_Jour_Annees(date);
return((int)jour);
}
/**********************************************************
fonction Date_Valide(Date date)
entree :  date de type  Date
sortie: entier represente 1 si la date est valide, 0 sinon
 		*******************************************/

int Date_Valide(Date date)
{
// 1901<=annee<=2099
if((date.annee<1901)||(date.annee>2099))
{printf("annee non vlide!! \n"
        " annee entre 1901 et 2099" );
return((int)0);
}
// 1<=mois<=12
if((date.mois<1)||(date.mois>12))
{printf("mois non vlide!! \n"
        " mois entre 1 et 12" );
return((int)0);
}
// si mois=2 et l'annee est biss
// 1<=jour<=29
if ((date.mois==2)&&(mod4(date.annee)==0))
  { if ((date.jour<0)||(date.jour>29))
	{printf("jour non vlide!!\n "
	" jour entre 0 et 29" );
	return((int)0);
	}
   }
// 1<=jour<= 28 ou 30 ou 31 selon le mois
else if((date.jour<0)||(date.jour>tab[date.mois-1]))
{printf("jour non vlide!!"
        " jour entre 0 et %d",tab[date.mois-1] );
return((int)0);
}
//LA DATE EST VALIDE
return((int)1);

}
/**********************************************************
fonction  DATE(Date date)
entree :  date de type  Date
sortie: rien
role :afficher le jour de la date saisi	par l'utilisateur
 		*******************************************/
void DATE(Date date)
{
    int decalage;//entier pour stocker le nombre de decalage
    if(Date_Valide(date))//tester si la date est valide
    {
        decalage=mod7(Nb_Jour(date));
        // Trouver le jour
        switch ( decalage )
        {
            case 0 : printf ("c'est un Mardi ") ; break ;
            case 1: printf  ("c'est un Mercredi ") ; break ;
            case 2 : printf (" c'est un Jeudi ") ; break ;
            case 3 : printf ("c'est un Vendredi ") ; break ;
            case 4 : printf ("c'est un Samedi ") ; break ;
            case 5 : printf ("c'est un Dimanche ") ; break ;
            case 6 : printf (" c'est un Lundi ") ; break ;
        }
     }
}

int main()
{
Date date;
// demander a l'utillisateur d'entrer la date
printf("entrer la date (jj-m-An) \n "); getch();
//recuperer la date
date=initialiser( );
DATE(date);
}
