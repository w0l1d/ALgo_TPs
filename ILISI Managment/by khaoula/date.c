//date.c
#include <stdio.h>
#include <stdlib.h>
#define mod4(x) (x)%4 
//tableau de 12 elements represente le nombre des jours de chaque mois 
int tab[12] ={31,28,31,30,31,30,31,31,30,31,30,31};


typedef struct date {
int jour;
int mois;
int annee;
}date;



int Date_Valide(date date)
{  

if((date.annee<1901)||(date.annee>2010))
{printf("annee non valide!! \n" );
return((int)0);
}
// 1<=mois<=12
if((date.mois<1)||(date.mois>12))
{printf("mois non valide!! \n"
        " mois entre 1 et 12\n" );
return((int)0);
}
// si mois=2 et l'annee est biss
// 1<=jour<=29
if ((date.mois==2)&&(mod4(date.annee)==0))
  { if ((date.jour<0)||(date.jour>29))
	{printf("jour non valide!!\n "
	" jour entre 0 et 29 \n" );
	return((int)0);
	}
   } 
// 1<=jour<= 28 ou 30 ou 31 selon le mois
else if((date.jour<0)||(date.jour>tab[date.mois-1]))
{printf("jour non valide!! \n"
        " jour entre 0 et %d \n",tab[date.mois-1] );
return((int)0);
}
//LA DATE EST VALIDE
return((int)1);
}

//fct qui lue une date
date scan_date() {
date d;
do
{
printf("\n date (jj/mm/aaaa): \n");
scanf("%d/%d/%d", &d.jour, &d.mois, &d.annee);
}while(!Date_Valide(d));
return ((date)d);
}
//fctt qui affiche une date

void print_date(date d) {
printf("\n %d/%d/%d\n", d.jour, d.mois, d.annee);

} 

