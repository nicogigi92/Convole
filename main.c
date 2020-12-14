#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "foncrand.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Convole, un outil de manipulation de matrice\n\n");

    //-g <m1> <n1> <m2> <n2> ... generate matrice with no writing
    // -o <m> <n> <filename> générer une matrice et l'enregistrer dans le filename
    //-l <matname> lire une matrice de nom l


    if(argc==1) //Si aucun arguments
    {

        matrice mat;
        mat.m=3;
        mat.n=3;
        rempli_matrice(&mat);
        char nom[20]=  "test";
        char comment[50] = "commenttest";
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
}



