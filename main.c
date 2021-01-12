#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include <getopt.h>
#include <string.h>



int main(int argc, char *argv[]) {

    printf("Convole, un outil de manipulation de matrice\n\n");

    //initialisation
    matrice mat;
    int optch;
    int comp;
    int i =0;
    int valeur;
    char c;
    int l = 0;
    int o = 0;
    int k = 0;
    char format[] = "o:l:k:E";
    extern int opterr;
    opterr = 1;
    char nom_fichier[100];
    char nom_fichier_lu[100];
    char commentaire[100];
    int compt =0;


    //aucun arguments
    if(argc==1)
        {
            affiche_matrice_base(&mat);
            return 0;
        }



    //On vérifie que les arguments ne sont pas trop longs (bufferoverflow ?)
    for(int i=1;i<argc;i++){        if (strlen(argv[i])>100){
        printf("Un des arguments est trop long (>100).\n\n");
        return 0;
        }
    }


    //gestion des options
    while ((optch = getopt(argc,argv,format)) != -1) {
        switch (optch) {
        case 'o':
            o = 1;
            strcpy(nom_fichier,optarg);
            break;
        case 'k':
            k = 1;
            strcpy(commentaire,optarg);
            break;
        case 'l':
            l = 1;
            strcpy(nom_fichier_lu,optarg);
            break;
        default :
            printf("Mauvaises options lors du lancement du programme\n\n");
            return 0;
            break;
        }
    }



    //ecriture
    if (o==1) {
        //on cherche deux entiers qui se suivent
        while ((((sscanf(argv[compt], "%d%c", &comp, &c) != 1) || (sscanf(argv[compt+1], "%d%c", &comp, &c) != 1)))&&(compt<argc-1))
            compt++;
        if (argv[compt+1]!=NULL){
            mat.m=atoi(argv[compt]);
            mat.n=atoi(argv[compt+1]);
        }
        else{
            printf("Erreur, m x n non trouvé, on utilisera 3x3.\n\n");
            mat.m=3;
            mat.n=3;
        }
        rempli_matrice(&mat);
        ecrit_matrice(&mat,nom_fichier,commentaire);    }

    //lecture
    if (l==1){
        lit_matrice(&mat,nom_fichier_lu);
    }

    //pas d'option
    if (l==0 && o==0){

        //cas ou le 1er argument est un nombre.
        if (sscanf(argv[1], "%d%c", &comp, &c) == 1)
        {
            //On vérifie que il y'a un nombre pair d'entier
            if (argc%2==0){
                printf("Erreur : Veuillez saisir un nombre pair d'arguments !\n\n");
                affiche_matrice_base(&mat);
                return 0;
            }

            //On vérifie que les nombres sont entiers
            for (i=1;i<argc;i++){
                if (sscanf(argv[i], "%d%c", &valeur, &c) != 1){
                    puts("Erreur: Veuillez entrer des nombres entiers !\n\n");
                    affiche_matrice_base(&mat);
                    return 0;
                }
            }

            //on vérifie que les nombres ne sont pas trop grand
            i=0;
            for (i=1;i<argc;i=i+2){
                mat.m=atoi(argv[i]);
                mat.n=atoi(argv[i+1]);
                if ((mat.m*mat.n)>100){
                    printf("Erreur : Vous avez demandé une matrice de taille %d x %d : c'est trop grand ! Taille max = 10x10. \n\n",mat.m,mat.n);
                }
                else{
                    rempli_matrice(&mat);
                    affiche_matrice(&mat);
                }
            }
            return 0;
        }
        //cas ou le 1er argument n'est pas un nombre
        if (sscanf(argv[1], "%d%c", &comp, &c) != 1){
            for (i=1;i<argc;i++){
                lit_matrice(&mat,argv[i]);
            }
            return 0;
        }
    }
}


