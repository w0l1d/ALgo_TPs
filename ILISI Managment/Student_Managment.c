//
// Created by W0L1D on 1/21/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "structures.h"
#include "error_msg.h"

#define max(a,b) ( (a > b) ? (a) : (b))

//**********************************************************************************
/***********************************************************************************
 * Nom : float getMoyenne(Dossier *ds)
 *             calculer la moyenne
 *
 * Entree : Dossier *ds : la base qui contient les
 						information des etudiants
 *
 * Sortie : un nombre reel : moyenne
 *
 */

float getMoyenne(Dossier *ds) {
    int nbr_annee;
    nbr_annee = ds->student->annee_univ;
    nbr_annee += (ds->student->reserve)?1:0;

    return ((float) ds->moy[nbr_annee-1]);
}


/***********************************************************************************
 * Nom : void print_student(Student *std)
 *             affiche les donnees d'un etudiant
 *
 * Entree : Student *std; etudiant a afficher
 *
 * Sortie : rien
 */
void print_student(Student *std) {
    printf(
            "nom = %s, "
            "prenom = %s, "
            "cin = %s, "
            "cne = %s, "
            "reserve = %x, "
            "annee universitaire = %x\n",
            std->nom, std->prenom, std->cin,
            std->cne, std->reserve, std->annee_univ);
}
//**********************************************************************************
/***********************************************************************************
 * Nom : int A_Reussi(Dossier *ds)
 *             verifier si l etudiant a reussi
 *				on verifiant les conditions
 *
 * Entree : Dossier *ds : la base qui contient les
 						information des etudiants
 *
 * Sortie : un entier : 1 si l etudiant a reussi
 *						0 si l etudiant a echoue
 */

int A_Reussi(Dossier *ds) {
    return (ds->inf12 < 4) && !(ds->inf10) && (getMoyenne(ds) > 12);
}
//**********************************************************************************
/***********************************************************************************
 * Nom : Dossier *insertDossier_Merite(Dossier *list, Dossier *ds)
 *             		inserer une liste d etudiants (1 ou plusieurs)
 					dans une bdd on respectant l ordre de merite
 *
 * Entree : Dossier *ds : la base qui contient les
 						information des etudiants

 *			Dossier *list : la liste des etudiant a inserer
 * Sortie : la nouvelle la base qui contient les
 *			information des etudiants
 */
Dossier *insertDossier_Merite(Dossier *list, Dossier *ds) {
    if (!list)
        return ((Dossier*) ds);
    // X est l'etudiant a insere
    // U est l'etudiant en tete de la liste
//    if(((getMoyenne(ds) > getMoyenne(list)) && A_Reussi(ds)) // si X a reussi et il a une moyenne > Y
//    || (!A_Reussi(list) && A_Reussi(ds)) // si X a reussi et Y non
//       || (!A_Reussi(ds) && !A_Reussi(list) && (getMoyenne(ds) >= 12) && (getMoyenne(list) < 12))
//          || (!A_Reussi(ds) && !A_Reussi(list) && (getMoyenne(ds) >= 12) && (getMoyenne(list) >= 12) && !ds->inf10))
    if(
            (A_Reussi(ds) && ((getMoyenne(ds) > getMoyenne(list)) || !A_Reussi(list)))
            || (!A_Reussi(ds)
                && !A_Reussi(list)
                && (getMoyenne(ds) >= 12)
                && ((getMoyenne(list) < 12)) || ((getMoyenne(list) >= 12) && !ds->inf10)
            )
            )
    {
        ds->svt = list;
        return ((Dossier *) ds);
    }
    list->svt = insertDossier_Merite(list->svt, ds);
    return ((Dossier*) list);
}

//**********************************************************************************
/***********************************************************************************
 * Nom : Dossier *insertDossier_Alpha(Dossier *list, Dossier *ds)
 *             		inserer une liste d etudiants (1 ou plusieurs)
 					dans une bdd on respectant
 					l'ordre alphabetique du nom puis le prenom
 *
 * Entree : Dossier *ds : la base qui contient les
 						informations des etudiants

 *			Dossier *list : la liste des etudiant a inserer
 * Sortie : la nouvelle la base qui contient les
 *			informations des etudiants
 */
Dossier *insertDossier_Alpha(Dossier *list, Dossier *ds) {
    if (!list)
        return ((Dossier*) ds);

    float tmp = strcmp(ds->student->nom, list->student->nom);
    if(tmp <= 0)
    {
        if (!tmp) {
            tmp = strcmp(ds->student->prenom, list->student->prenom);
            if (tmp > 0)
                goto skip;
        }
        ds->svt = list;
        return ((Dossier *) ds);
    }
    skip:
    list->svt = insertDossier_Merite(list->svt, ds);
    return ((Dossier*) list);
}

//**********************************************************************************
/***********************************************************************************
 * Nom : Dossier *initDossier(Student *st)
 *             		initialiser la cellule qui contient
 					les donnees d un etudiant ,ses moyens
 					et ses notes.
 *
 * Entree : Student *st : cellule de type student
 						contient les donnees d un etudiant


 *
 * Sortie : Dossier *ds : la cellule qui contient
 *					les donnees d un etudiant ,ses moyens
 *					et ses notes.
 */

Dossier *initDossier(Student *st) {
    Dossier *ds;
    ds = (Dossier*) malloc(sizeof(Dossier));
    if (!ds) {
        printf(ERROR_ALL_MEM_DOSSIER);
        exit(-1);
    }
    ds->student = st;
    ds->svt = NULL;
    ds->moy[0] = 0;
    ds->moy[1] = 0;
    ds->moy[2] = 0;
    return ((Dossier*)ds);
}
//**********************************************************************************
/***********************************************************************************
 * Nom : Note *init_Note(float normal)
 *             		initialiser la note d un etudiant
 *
 * Entree : float normal : la note a inserer

 *
 * Sortie : Note *nt : la note de l etudiant
 *
 */
Note *init_Note(float normal) {
    Note *nt = (Note*) malloc(sizeof(Note));
    if (!nt) {
        printf(ERROR_ALL_MEM_NOTE);
        exit(-1);
    }
    nt->normal = normal;
    return ((Note*) nt);
}
//**********************************************************************************
/***********************************************************************************
 * Nom : Student* readStudent(FILE *fl)
 *             		lire les donnees d un etudiant
 					depuis le fichier
 *
 * Entree : FILE *fl : le fichier qui contient
 						les donnees des etudiants
 *
 * Sortie : Student *stud : l etudiant lu
 *
 */
Student* readStudent(FILE *fl) {
    Student *stud = NULL;
    char nom[30],prenom[30], cin[15], cne[15];
    unsigned int day, month, year, res, an_unv;

    //STUDENT_PATTERN = "%30[^;];%30[^;];%8[A-Za-z0-9];%10[A-Za-z0-9];%d;%d;%d;%d;%d\n"
    int rst = fscanf(fl, STUDENT_PATTERN,
                     nom, prenom, cin, cne, &day,
                     &month, &year, &res, &an_unv);

    if (rst == EOF)
        return ((Student*) NULL);

    stud = (Student*) malloc(sizeof(Student));
    stud->nom = (char *) strdup(nom);
    stud->prenom = (char *) strdup(prenom);
    stud->cin = (char *) strdup(cin);
    stud->cne = (char *) strdup(cne);
    stud->naiss.day = day;
    stud->naiss.month = month;
    stud->naiss.year = year;
    stud->reserve = res;
    stud->annee_univ = an_unv;

    return ((Student*)stud);
}

int get_annee_actuel(Student *std) {
    return ((int) std->annee_univ - (std->reserve)?0:1);
}


//**********************************************************************************
/***********************************************************************************
 * Nom : Dossier *readDossier(FILE *fl)
 *             		lire tous les informations d un
 					etudiant depuis le fichier fl
					et calculer ses moyens

 *
 * Entree : FILE *fl : le fichier qui contient
 						les donnees des etudiants
 *
 * Sortie : Dossier *ds : la celulle de type Dossier
 *							qui contients tous les info
 *							de l etudiant
 *
 */
Dossier *readDossier(FILE *fl) {
    Student *stud = readStudent(fl);
    if (!stud)
        return ((Dossier*) NULL);
    Dossier *ds = initDossier(stud);
    int ind, //index to current Note
    ind2 = 0, // indique l'annee actuel
    i, j;
    float note, moyen; // n1->note normal; n2->note du rattrapage
    int nbr_annee = stud->annee_univ;
    nbr_annee += (stud->reserve)?1:0;
    do {
        moyen = 0;
        for (ind = 0; ind < 16; ind++) {
            //statistique des notes seuelement pour la dernier annees
            if (nbr_annee == 1)
                if (note < 12) {
                    if (note < 10)
                        ds->inf10 = 1;
                    else
                        ds->inf12++;
                }

            fscanf(fl, "%f;", &note);

            i = ind / 16; // line index // annee du note
            j = ind % 16; // column index // module du note
            ds->notes[i][j] = note;
            moyen += note;
        }
        moyen /= 16;
        ds->moy[ind2++] = moyen;

        fscanf(fl, "%*[\n];");
    } while(--nbr_annee);

    return ((Dossier*) ds);
}
//**********************************************************************************
/***********************************************************************************
 * Nom : void orgDossiers_merite(FILE *f, Dossier *ds[3])
 *             		lire depuis le fichier les donnees des
 *             		etudiants et les organisee selon les promotion
 *
 * Entree : FILE *fl : le fichier qui contient
 *						les donnees des etudiants
 *			Dossier *ds[3]: un tableau de 3 cases de listes
 *			chaque case represente une promotion
 *
 * Sortie : rien
 */
void orgDossiers_merite(FILE *f, Dossier *ds[3]) {
    Dossier *tmp;

    while ((tmp = readDossier(f)) != NULL)
        ds[(int)tmp->student->annee_univ-1] = insertDossier_Merite(ds[(int) tmp->student->annee_univ - 1], tmp);
}

//**********************************************************************************
/***********************************************************************************
 * Nom : void orgDossiers_alpha(FILE *f, Dossier *ds[3])
 *             		lire depuis le fichier les donnees des
 *             		etudiants et les organisee selon les promotion
 *
 * Entree : FILE *fl : le fichier qui contient
 *						les donnees des etudiants
 *			Dossier *ds[3]: un tableau de 3 cases de listes
 *			chaque case represente une promotion
 *
 * Sortie : rien
 */
void orgDossiers_alpha(FILE *f, Dossier *ds[3]) {
    Dossier *tmp;

    while ((tmp = readDossier(f)) != NULL)
        ds[(int)tmp->student->annee_univ-1] = insertDossier_Alpha(ds[(int) tmp->student->annee_univ - 1], tmp);
}


//**********************************************************************************
/***********************************************************************************
 * Nom : void readModules(FILE *f)
 *             		lire lesnoms des modules depuis un fichier
 *
 *
 * Entree : FILE *fl : le fichier qui contient les
 *					 noms des modules des 3 annees
 *
 * Sortie : rien
 *
 */
void readModules(FILE *f) {

    int modIndex = 0, modsize = 0;
    int i,j;
    char str[100], c;

    while((c=(char)fgetc(f))!=EOF) {

        if (c == DELIM) {
            str[modsize] = '\0';
            i = modIndex/16;
            j = modIndex%16;
            if ((i > 2) || (j > 15)) {
                printf("\n\nerreur les modules stockes depasse le nombre predefini\n");
                printf("\ni = %d, j =%d\n", i, j);
                exit(0);
            }
            modules[i][j] =(char *) strdup(str);
            modIndex++;
            modsize = 0;
            continue;
        }
        str[modsize] = c;
        modsize++;
    }
}


/***********************************************************************************
 * Nom : void aff_Menu_Statis()
 *       afficher le menu des statistiques disponible
 *
 * Entree : rien
 * Sortie : rien
 */
void aff_Menu_Statis() {
    printf(
            "\n******************************************\n"
            "***********Statistiques Menu**************\n"
            "******************************************\n"
            "1-> les etudiants ayant reussi\n"
            "2-> les etudiants ayant des notes entre 10 et 12\n"
            "3-> les etudiants ayant des notes < 10\n"
            "4-> les etudiants n'ayant pas des notes < 10, mais ont echoues\n"
            "0-> Retourner\n"
    );
}


/***********************************************************************************
 * Nom : void aff_etud_reussi(Dossier *ds)
 *       afficher les etudiants qui ont reussi
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 * Sortie : rien
 */
void aff_etud_reussi(Dossier *ds) {
    printf("\nLes etudiants ayant reussi\n");
    while(ds) {
        if (A_Reussi(ds))
            print_student(ds->student);
        ds = ds->svt;
    }
}

/***********************************************************************************
 * Nom : void aff_etud_reussi_module(Dossier *ds)
 *       afficher les etudiants qui ont reussi dans un module
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *          int nmod; numero de module
 * Sortie : rien
 */
void aff_etud_reussi_module(Dossier *ds, int nmod) {
    printf("\nLes etudiants ayant reussi\n");
    while(ds) {
        if (ds->notes[get_annee_actuel(ds->student)][nmod] >= 12);
            print_student(ds->student);
        ds = ds->svt;
    }
}



/***********************************************************************************
 * Nom : void aff_Main_Menu()
 *       afficher le menu pricipal
 *
 * Entree : rien
 * Sortie : rien
 */
void aff_Main_Menu() {
    printf(
            "\n******************************************\n"
            "***********Main Menu**************\n"
            "******************************************\n"
            "1-> Statistique par Annee/Promotion\n"
            "2-> Statistique par Module\n"
            "0-> Retourner\n"
    );
}



/***********************************************************************************
 * Nom : void aff_etud_10_12(Dossier *ds)
 *       afficher les etudiants ayant une note entre 10 et 12 dans un module
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *
 * Sortie : rien
 */
void aff_etud_10_12(Dossier *ds) {
    printf("\nLes etudiants ayant des note entre 10 et 12\n");
    while(ds) {
        if (ds->inf12)
            print_student(ds->student);
        ds = ds->svt;
    }
}

/***********************************************************************************
 * Nom : void aff_etud_10_12_module(Dossier *ds)
 *       afficher les etudiants ayant une note entre 10 et 12
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *          int nmod; numero de module
 * Sortie : rien
 */
void aff_etud_10_12_module(Dossier *ds, int nmod) {
    float tmp;
    printf("\nLes etudiants ayant des note entre 10 et 12\n");
    while(ds) {
        tmp = ds->notes[get_annee_actuel(ds->student)][nmod];
        if (( 10 >= tmp) && (tmp < 12))
            print_student(ds->student);
        ds = ds->svt;
    }
}

/***********************************************************************************
 * Nom : void aff_etud_10_module(Dossier *ds)
 *       afficher les etudiants ayant une note inferieure a 10
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *          int nmod; numero de module
 * Sortie : rien
 */
void aff_etud_10_module(Dossier *ds, int nmod) {
    float tmp;
    printf("\nLes etudiants ayant des note entre 10 et 12\n");
    while(ds) {
        tmp = ds->notes[get_annee_actuel(ds->student)][nmod];
        if (10 > tmp)
            print_student(ds->student);
        ds = ds->svt;
    }
}


/***********************************************************************************
 * Nom : aff_etud_not_10_not_reussi_module(Dossier *ds)
 *       afficher les etudiants ayant
 *       qui n'ont pas une note inferieure a 10 dans un module
 *       mais qui n'ont pas reussi
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *          int nmod; numero de module
 * Sortie : rien
 */
void aff_etud_not_10_not_reussi_module(Dossier *ds, int nmod) {
    float tmp;
    printf("\nLes etudiants ayant des note entre 10 et 12\n");
    while(ds) {
        tmp = ds->notes[get_annee_actuel(ds->student)][nmod];
        if ((tmp > 10) && !A_Reussi(ds))
            print_student(ds->student);
        ds = ds->svt;
    }
}

/***********************************************************************************
 * Nom : void aff_etud_10(Dossier *ds)
 *       afficher les etudiants ayant une note inferieure a 10
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 * Sortie : rien
 */
void aff_etud_10(Dossier *ds) {
    printf("\nLes etudiants ayant des notes inferieures 10\n");
    while(ds) {
        if (ds->inf10)
            print_student(ds->student);
        ds = ds->svt;
    }
}



/***********************************************************************************
 * Nom : void aff_etud_not_10_not_reussi(Dossier *ds)
 *       afficher les etudiants ayant
 *       qui n'ont pas une note inferieure a 10
 *       mais qui n'ont pas reussi
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 * Sortie : rien
 */
void aff_etud_not_10_not_reussi(Dossier *ds) {
    printf("\nles etudiants n'ayant pas des notes < 10, mais ont echoues\n");
    while(ds) {
        if (!(ds->inf10) && !A_Reussi(ds))
            print_student(ds->student);
        ds = ds->svt;
    }
}

/***********************************************************************************
 * Nom : void menu_par_annee(Dossier *ds)
 *       traitement des etudiant par annee
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 * Sortie : rien
 */
void menu_par_annee(Dossier *ds) {
    int choix;

    if (!ds) {
        printf("\nListe est vide\n");
        getch();
        return;
    }
    do {
        choix = 0;
        aff_Menu_Statis();
        printf("\n\n>>>  ");
        scanf("%d", &choix);
        switch(choix) {
            case 1:
                aff_etud_reussi(ds);
                break;
            case 2:
                aff_etud_10_12(ds);
                break;
            case 3:
                aff_etud_10(ds);
                break;
            case 4:
                aff_etud_not_10_not_reussi(ds);
                break;
            case 0:
                return;
            default:
                printf("\nErreur : Choix Invalide\n");
        }
        getch();
    }while(choix);
}

/***********************************************************************************
 * Nom : void menu_par_module(Dossier *ds, int nmod)
 *       traitement des etudiant par annee
 *
 * Entree : Dossier *ds; liste des dossiers des etudiants
 *          int nmod; numero du module
 * Sortie : rien
 */
void menu_par_module(Dossier *ds, int nmod) {
    int choix;

    if (!ds) {
        printf("\nListe est vide\n");
        getch();
        return;
    }
    do {
        choix = 0;
        aff_Menu_Statis();
        printf("\n\n>>>  ");
        scanf("%d", &choix);
        switch(choix) {
            case 1:
                aff_etud_reussi_module(ds, nmod);
                break;
            case 2:
                aff_etud_10_12_module(ds, nmod);
                break;
            case 3:
                aff_etud_10_module(ds, nmod);
                break;
            case 4:
                aff_etud_not_10_not_reussi_module(ds, nmod);
                break;
            case 0:
                return;
            default:
                printf("\nErreur : Choix Invalide\n");
        }
        getch();
    }while(choix);
}



/***********************************************************************************
 * Nom : void main_menu(Dossier *ds[3])
 *       choisir le traitement des etudiant
 *       soit par anne ou par module
 *
 * Entree : Dossier *ds[3]; les listes des etudiants de 3 promotions
 * Sortie : rien
 */
void main_menu(Dossier *ds[3]) {
    int choix, tmp, tmp2;
    do {
        choix = 0;
        aff_Main_Menu();
        printf("\n\n>>>  ");
        scanf("%d", &choix);
        switch(choix) {
            case 1:
                printf("\nEntrer la promotion [1,2 ou 3] : ");
                scanf("%d", &tmp);
                while((tmp < 1) || (3 < tmp)) {
                    printf("\nRentrer une promotion [1 ou 2 ou 3] : ");
                    scanf("%d", &tmp);
                }
                menu_par_annee(ds[tmp-1]);
                break;
            case 2:
                printf("\nEntrer l'annee du module [1,2 ou 3] : ");
                scanf("%d", &tmp);
                while((tmp < 1) || (3 < tmp)) {
                    printf("\nRentrer l'annee du module [1 ou 2 ou 3] : ");
                    scanf("%d", &tmp);
                }

                printf("\nEntrer le numero du module [1-16] : ");
                scanf("%d", &tmp2);
                while((tmp2 < 1) || (16 < tmp2)) {
                    printf("\nRentrer le numero du module (entre 1 et 16) : ");
                    scanf("%d", &tmp2);
                }

                menu_par_module(ds[tmp-1], tmp2-1);
                break;
            case 0:
                break;
            default:
                printf("\nErreur: Choix invalide\n");
        }
        getch();
    }while(choix);


}