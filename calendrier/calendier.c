//
// Created by W0L1D on 12/19/2021.
//

#include <stdio.h>

#define mod4(x) (x%4)
#define mod7(x) (x)%7
#define div4(x) (x)/4


//structure utiliser pour stocker le jour le mois et l annee saisi par l utilisateur
typedef struct dt
{
    int jour ;// entier pour stocker les jours
    int mois ;// entier pour stocker le mois
    int annee ;// entier pour stocker l'année
}Date;//structure Date


/**********************************************************
 * Nb_Jour_Annees()
 * nombre de jour passe dans les annee precedents
 * @param date
 * @return entier represente nombre des jours de 1901 jusqu'à l'annee saisi
 *          par l'utilisateur
 *
 *******************************************/
int Nb_Jour_Annees(Date date ) {
    return((int)((date.annee-1901)*365+div4(date.annee-1901)) );
}

/**********************************************************
 * Nb_Jour_Mois(Date date)
 * nombre de jour passe dans les mois precedent dans l'année courant
 * @param date
 * @return entier represente le nombre des jours du mois 1 jusqu'à le mois saisi
 *          par l'utilisateur
*******************************************/
int Nb_Jour_Mois(Date date)
{
    int mois=date.mois-1, mois_jr;
    float tmp = 0;
    if (mois < 9)     tmp = 0.5f;
    // variable mois pour stocker le nombres des jours
    if (mois == 1)    mois_jr = 31;
    else
    {
        mois_jr = 30 * mois + (((float)mois)/2 - tmp);
        if((mois > 1) && mod4(date.annee)) mois_jr--;
    }

    return((int)mois_jr);
}

/**********************************************************
 * Nb_Jour(Date date)
 * nombre de jour entre 1-1-1901 et @date
 * @param date
 * @return entier represente nombre des jours Du 1-1-1901 jusqu'à la date saisi
 * par l'utilisateur
 ********************************************/
int Nb_Jour(Date date)
{
    int jour;
    jour=date.jour-1 + Nb_Jour_Mois(date)+Nb_Jour_Annees(date);
    return((int)jour);
}


/**********************************************************
 * Date_Valide(Date date)
 * valide la date entrer par l'utilisateur
 * @param date
 * @return  1 si la date est valide, 0 sinon
 *
 *******************************************/

int Date_Valide(Date date)
{

// taableau de 12 elements represente le nombre des jours de chaque mois
    const unsigned int tab[12] ={31,28,31,30,31,30,31,31,30,31,30,31};

    // 1901<=annee<=2099
    if((date.annee<1901)||(date.annee>2099))
    {
        printf("annee non valide!! \n"
            " annee entre 1901 et 2099" );
        return((int)0);
    }
    // 1<=mois<=12
    if((date.mois<1)||(date.mois>12))
    {
        printf("mois non valide!! \n"
               " mois entre 1 et 12" );
        return((int)0);
    }
    // si mois=2 et l'année est bissextile
    // 1 <= jour <= 29
    int bsx = (mod4(date.annee)? 0:1) + 28;

    if (date.mois==2)
    {
        if ((date.jour < 0) || (bsx < date.jour))
        {
            printf("jour non valide!!\n "
                " jour entre 0 et %d", bsx );
            return((int)0);
        }
    }


    // 1<=jour<= 28 ou 30 ou 31 selon le mois
    else if((date.jour<0)||(tab[date.mois-1] < date.jour ))
    {
        printf("jour non valide!!"
               " jour entre 0 et %d",tab[date.mois-1] );
        return((int)0);
    }
    //LA DATE EST VALIDE
    return((int)1);

}



/**********************************************************
 * DATE(Date date)
 * afficher le jour de la date saisi	par l'utilisateur
 * @param date
 * @return rien
 ********************************************/
void DATE(Date date)
{
    const char tab_jour[7][9] ={"mardi\0","mercredi\0","jeudi\0","vendredi\0","samedi\0","dimanche\0","lundi\0"};

    int decalage;//entier pour stocker le nombre de decalage
    if(Date_Valide(date))//tester si la date est valide
    {
        decalage=mod7(Nb_Jour(date));
        // Trouver le jour
        printf ("c'est un %s.", tab_jour[decalage]);
    }
}

int main()
{
    Date date;

    // demander a l'utillisateur d'entrer la date
    printf("entrer la date (jour mois Annee) :");
    //recuperer la date
    scanf("%d%d%d", &(date.jour), &(date.mois), &(date.annee));getchar();
    DATE(date);
}
