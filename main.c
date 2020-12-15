#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "foncrand.h"
#include <getopt.h>
#include <string.h>



int main(int argc, char *argv[]) {
    printf("Convole, un outil de manipulation de matrice\n\n");

    //initialisation
    matrice mat;
    int optch;
    int comp;
    int l = 0;
    int o = 0;
    char format[] = "o:l:";
    extern int opterr;
    opterr = 1;
    char c;
    char nom_fichier[100];
    char commentaire[100];

    //On se prémunie d'un éventuel bufferoverflow en controlant tout les parametres donnés par l'utilisateur
    for(int i=1;i<argc;i++){        if (strlen(argv[i])>100){
        printf("Un des arguments est trop long (>100).\n\n");
        return 0;
        }
    }

    while ((optch = getopt(argc,argv,format)) != -1) {
        switch (optch) {
        case 'o':
            o = 1;
            break;
        case 'l':
            l = 1;
            break;
        default :
            printf("Mauvaises options lors du lancement du programme\n"); // si une autre option est utilisee
            return 0;
            break;
        }
    }
    if (o==1) {
        if ((sscanf(argv[3], "%d%c", &comp, &c) != 1) || (sscanf(argv[4], "%d%c", &comp, &c) != 1)) {
            puts("Veuillez donner des nombres entiers");
            return 0;
        }
        mat.m=atoi(argv[3]);
        mat.n=atoi(argv[4]);
        rempli_matrice(&mat);
        strcpy(nom_fichier,argv[2]);
        if (argv[5]!=NULL)
             strcpy(commentaire,argv[5]);
        ecrit_matrice(&mat,nom_fichier,commentaire);
    }









/*

    if(argc==1) //Si aucun arguments
    {
         pour utiliser écrit matrice
        matrice mat;
        mat.m=6;
        mat.n=9;
        rempli_matrice(&mat);
        char nom[20]=  "test2";
        char comment[50] = "commentaire du deuxième test";
        ecrit_matrice(&mat,&nom,&comment);

    }
    else // si on a des arguments on vérifie que c'est nombres entiers et qu'il y'en a bien un nombre pair et qu'ils ne sont pas trop grand
    {
        if (argc%2==0)
        {
        printf("Erreur : Veuillez saisir un nombre pair d'arguments !\n\n");
        affiche_matrice_base();
        return 0;
        }
        int i=0;
        int valeur;
        char c;
        for (i=1;i<argc;i++)
        {
            if (sscanf(argv[i], "%d%c", &valeur, &c) != 1)
            {
                puts("Erreur: Veuillez entrer des nombres entiers !\n\n");
                affiche_matrice_base();
                return 0;
            }

        }
        i=0;
        for (i=1;i<argc;i=i+2)
        {
            matrice mat;
            mat.m=atoi(argv[i]);
            mat.n=atoi(argv[i+1]);
            //on vérifie que les nombres ne sont pas trop grand
            if ((mat.m*mat.n)>100)
            {
                printf("Erreur : Vous avez demandé une matrice de taille %d x %d : c'est trop grand ! Taille max = 10x10. \n\n",mat.m,mat.n);
            }
            else
            {
                rempli_matrice(&mat);
                affiche_matrice(&mat);
            }
        }
    return 0;
    }
*/
}


