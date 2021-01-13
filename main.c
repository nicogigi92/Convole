#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "calcul_matrice.h"
#include <getopt.h>
#include <string.h>



int main(int argc, char *argv[]) {

    printf("Convole, un outil de manipulation de matrice\n\n");

    //initialisation
    char nom_fichier_lu_1[100];
    char nom_fichier_lu_2[100];     //on a besoin d'un deuxième fichier pour faire calcul +
    matrice mat_ecriture;           //instance de matrice à écrire
    matrice mat_lecture_1;          //instance de matrice qui contient ce qu'on aura lu d'un fichier
    matrice mat_lecture_2;          //instance de matrice qui contient ce qu'on aura lu d'un fichier
    int optch;
    extern int opterr;
     opterr=1;
    int comp;
    int res_allocation;
    int i =0;
    int valeur;
    char c;
    int l = 0;
    int o = 0;
    int k = 0;
    char format[] = "o:l:k:c:";
    char nom_fichier[100];
    char commentaire[100];
    int compt =0;
    char type_de_calcul[10];


    //aucun arguments
    if(argc==1){
        if( alloue_matrice(&mat_ecriture) == 1){
             printf("Problème lors de l'allocation de la matrice\n\n.");
             free((&mat_ecriture)->v_ptr);
             return 1;
        }
        else{
            affiche_matrice_base(&mat_ecriture);
            return 0;
        }
    }



    //On vérifie que les arguments ne sont pas trop longs.
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
            strcpy(nom_fichier_lu_1,optarg);
            break;
        case 'c':
            c = 1;
            strcpy(type_de_calcul,optarg);
            if (type_de_calcul[0]=='t'){
            //on s'attend à avoir le nom de la matrice à transposer juste après le t
                if (optind<argc){
                    strcpy(nom_fichier_lu_1,argv[optind]);
                }
                else{
                    printf("Il y'a un problème dans vos arguments.\n");
                    return 0;
                }

            }
            else{
            // on attend deux noms de matrices pour +, -, * etc...
                if (optind+1<argc){
                    strcpy(nom_fichier_lu_1,argv[optind]);
                    strcpy(nom_fichier_lu_2,argv[optind+1]);
                }
                else{
                    printf("Il y'a un problème dans vos arguments.\n");
                    return 0;
                }
            }
            break;
        default :
            printf("Mauvaises options lors du lancement du programme.\n\n");
            return 0;
            break;
        }
    }



    //option de calcul
    if(c==1){

        //transposition
        if (type_de_calcul[0]=='t'){

            if (lit_matrice(&mat_lecture_1,nom_fichier_lu_1)==1){
                    mat_ecriture = transpose(&mat_lecture_1);
                    affiche_matrice(&mat_ecriture);
            }
            else{
                return 0;
            }
        }

        //addition
        else if (type_de_calcul[0]=='+'){
            //on vérifie que les fichiers existent
            if ( (lit_matrice(&mat_lecture_1,nom_fichier_lu_1)==1) && (lit_matrice(&mat_lecture_2,nom_fichier_lu_2) == 1 ) ){
                //on verifie que les matrices sont de la bonne taille
                if (test_taille_matrice(&mat_lecture_1,&mat_lecture_2)==1){
                    return 0;
                }
                else
                    mat_ecriture=additione(&mat_lecture_1,&mat_lecture_2);
                    affiche_matrice(&mat_ecriture);
            }
            else{
                return 0;
            }
        }

        //soustraction
        else if (type_de_calcul[0]=='-'){
            if ( (lit_matrice(&mat_lecture_1,nom_fichier_lu_1)==1) && (lit_matrice(&mat_lecture_2,nom_fichier_lu_2) == 1 ) ){
                if (test_taille_matrice(&mat_lecture_1,&mat_lecture_2)==1){
                    return 0;
                }
                else
                    mat_ecriture=soustrait(&mat_lecture_1,&mat_lecture_2);
                    affiche_matrice(&mat_ecriture);
            }
            else{
                return 0;
            }
        }

        //on écrit si demandé
        if (o==1){
        ecrit_matrice(&mat_ecriture,nom_fichier,commentaire);
        }

        return 0;
    }

    //option d'ecriture
    if (o==1 && c==0) {
        //on cherche deux entiers qui se suivent dans les arguments pour initialiser la matrice
        while ((((sscanf(argv[compt], "%d%c", &comp, &c) != 1) || (sscanf(argv[compt+1], "%d%c", &comp, &c) != 1)))&&(compt<argc-1))
            compt++;
        //cas ou on trouve deux entiers consécutif
        if (argv[compt+1]!=NULL){
            mat_ecriture.m=atoi(argv[compt]);
            mat_ecriture.n=atoi(argv[compt+1]);
        }
        else{
            printf("Erreur, m x n non trouvé, on utilisera 3x3.\n\n");
            mat_ecriture.m=3;
            mat_ecriture.n=3;
        }


        //allocation de la matrice
        if( alloue_matrice(&mat_ecriture) == 1){
             printf("Problème lors de l'allocation de la matrice\n\n.");
             free((&mat_ecriture)->v_ptr);
             return 1;
        }
        else{
            //remplissage et écriture de la matrice
            rempli_matrice(&mat_ecriture);
            ecrit_matrice(&mat_ecriture,nom_fichier,commentaire);
            free((&mat_ecriture)->v_ptr);
        }
    }

    //option de lecture
    if (l==1){
        lit_matrice(&mat_ecriture,nom_fichier_lu_1);
    }



    //pas d'option
    if (l==0 && o==0 && c==0){

        //cas ou le 1er argument est un nombre.
        if (sscanf(argv[1], "%d%c", &comp, &c) == 1)
        {
            //On vérifie que il y'a un nombre pair d'entier
            if (argc%2==0){
                printf("Erreur : Veuillez saisir un nombre pair d'arguments !\n\n");
                return 0;
            }

            //On vérifie que les nombres sont entiers
            for (i=1;i<argc;i++){
                if (sscanf(argv[i], "%d%c", &valeur, &c) != 1){
                    puts("Erreur: Veuillez entrer des nombres entiers !\n\n");
                    return 0;
                }
            }

            //on vérifie que les nombres ne sont pas trop grand
            i=0;
            for (i=1;i<argc;i=i+2){
                mat_ecriture.m=atoi(argv[i]);
                mat_ecriture.n=atoi(argv[i+1]);


                if( alloue_matrice(&mat_ecriture) == 1){
                    printf("Problème lors de l'allocation de la matrvBj7SWjZBMkvcCice\n\n.");
                    free((&mat_ecriture)->v_ptr);
                    return 1;
                }
                else{
                    rempli_matrice(&mat_ecriture);
                    affiche_matrice(&mat_ecriture);
                    free((&mat_ecriture)->v_ptr);
                }
            }
            return 0;
        }
        //cas ou le 1er argument n'est pas un nombre
        if (sscanf(argv[1], "%d%c", &comp, &c) != 1){
            for (i=1;i<argc;i++){
                lit_matrice(&mat_ecriture,argv[i]);
            }
            return 0;
        }
    }
}


