#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"
#include <ctype.h>
#include <dirent.h>

//taille maximum qu'une ligne d'un fichier .mat pourra prendre
int TAILLE_MAX_LIGNE = 1000;

double rand_ab_d(double a, double b){
    double c ;
    if ( a > b ) {
        c = a ;
        a = b ;
        b = c ;
    }
    return (a + (b-a) * (rand()/(RAND_MAX+1.0))) ;
}

void affiche_alea(int n, double a, double b){
    int i;
    for(i=1;i<=n;i++){
        double nombre = rand_ab_d(a,b);
        printf("%f \n",nombre);
    }
}

int listdir(const char* namefile){
    DIR * rep = opendir("/home/nico/C/Convole");
    int psexist =0;

    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            //printf("%s\n", ent->d_name);
            if (strcmp(namefile,ent->d_name)==0)
                psexist=1;
        }

        closedir(rep);
    }

    return psexist;  // 0 file does not exist, 1 file exist

}

double max_val_absolue(matrice *M_ptr){
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int i=0;
    double MAX = 0;

    for(i=0;i<P;i++)
    {
        if (fabs(M_ptr->v_ptr[i]) > MAX)
            MAX = fabs(M_ptr->v_ptr[i]);
    }
    return MAX;
}

int alloue_matrice(matrice *M_ptr){
    M_ptr->v_ptr=malloc(sizeof(double)*M_ptr->n*M_ptr->m);
    if (M_ptr->v_ptr == NULL){
        return 1;
    }
    return 0;

}

double rempli_matrice(matrice *M_ptr){
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int i=0;
    double MAX = 0;
    printf("Génération d'une matrice %d x %d....\n\n",M,N);
    for(i=0;i<P;i++)
    {
        double addnbr = rand_ab_d(-20,20);
        M_ptr->v_ptr[i]=addnbr;
        if (addnbr > MAX)
        {
            MAX = addnbr;
        }
    }
    printf("Matrice générée. Son max est %f.\n\n",MAX);
    return MAX;
}

void affiche_matrice(struct matrice *M_ptr){
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int m=0;
    int i=0;

    printf("Affichage de votre matrice %dx%d.\n\n",M,N);
    printf("|  ");
    for(i=0;i<P;i++)
    {
        m=i/N;
        if (m==(i+1)/N)
        {
        printf("%12f ",M_ptr->v_ptr[i]);
        }
        else
        {
        if(i<P-1)
            printf("%12f   |\n|  ",M_ptr->v_ptr[i]);
        else
            printf("%12f   |\n",M_ptr->v_ptr[i]);
        }
    }
    printf("\nFin d'affichage de matrice.\n\n\n");
}

void affiche_matrice_base(matrice *M_ptr){
    //génére et affiche une matrice 3x3
    M_ptr->m=3;
    M_ptr->n=3;
    rempli_matrice(M_ptr);
    affiche_matrice(M_ptr);
}

int est_nulle(matrice *M_ptr){
    //dit si une matrice est nulle ou non
    int P = (M_ptr->m)*(M_ptr->n);
    int i=0;
    for(i=0;i<P;i++)
    {
        if (M_ptr->v_ptr[i]> 10e-7)
        {
            return 0;
        }
    }
    return 1;
}

int ecrit_matrice(struct matrice *M_ptr, char *nom_fichier, char *commentaire){
    FILE* fichier = NULL;
    int choix = 0;
    char reponse;
    char chemin_fichier[100];
    char char_fichier[1000];


    int m=0;
    int i=0;
    char str_int[10] = "";

    //petite interface pour s'assurer que l'utilisateur écrit bien la ou il veut
    while (!choix)
    {
        if (listdir(nom_fichier))
        {
            printf("\n\nLe fichier %s existe déjà, voulez vous l'écraser [E], ou donner un nouveau nom de fichier [N] ? ",nom_fichier);
            scanf("%s",&reponse);

            if (strcmp(&reponse,"E")==0)
                choix++;
            else if (strcmp(&reponse,"N")==0){
                printf("Donnez un nouveau nom de fichier : ");
                scanf("%s",nom_fichier);
            }
            else{
                printf("\nVeuillez choisir d'écraser [E] ou de donner un nouveau nom [N]");
                choix=0;
            }
        }
        else {
            printf("\n\n Le fichier n'existe pas, on le créé\n\n");
            choix++;
        }
    }

    strcpy(chemin_fichier,"/home/nico/C/Convole/");
    strcat(chemin_fichier,nom_fichier);
    fichier = fopen(chemin_fichier, "w");

    if (fichier == NULL) { //erreur d'ouverture du fichier
        printf("Erreur : Impossible d'ouvrir le fichier %s .\n",nom_fichier);
        return 0;
    }
    else if (est_nulle(M_ptr)){ //matrice vide
        printf("Erreur : Matrice vide");
        return 0;
    }

    else{ // si pas d'erreur
        //ajout du commentaire au début
        strcpy(char_fichier,"#");
        strcat(char_fichier,commentaire);
        strcat(char_fichier,"\n");
        //ajout de la taille de la matrice
        sprintf(str_int, "%d ", M_ptr->m);
        strcat(char_fichier,str_int);
        sprintf(str_int, "%d", M_ptr->n);
        strcat(char_fichier,str_int);
        strcat(char_fichier,"\n");
        for(i=0;i<(M_ptr->m*M_ptr->n);i++)
        {
            m=i/M_ptr->n;
            if (m==(i+1)/M_ptr->n)
            {
            char s[15] = {0};
            sprintf(s, "%.9lf",M_ptr->v_ptr[i]);
            strcat(strcat(char_fichier,s)," ");
            }
            else
            {
            char s[15] = {0};
            sprintf(s, "%.9lf",M_ptr->v_ptr[i]);
            strcat(strcat(char_fichier,s),"\n");
            }
        }
        fputs(char_fichier, fichier);
        rewind(fichier);
        fclose(fichier);
        printf("L'écriture a fonctionné.\n\n");
        return 1;
        }
}

int nombre_espace_str(char* str){
    //donne le nombre d'espace dans une chaîne de caractère
    //donne a 1 près le nombre de double d'une ligne de matrice
    int nbr=0;
    for(int i=0;i<strlen(str);i++){
        if(str[i]==' ')
            nbr++;
    }
    return nbr;
}

int lit_matrice(struct matrice *M_ptr, char * nom_fichier){
    FILE *fichier = NULL;
    char *ligne = NULL;
    int taille_max_ligne;           //une fois qu'on connait m et n on peut allouer sans avoir besoin de TAILLE_MAX_LIGNE
    int nval= 0;                    //nbr de double sur une ligne
    long debut_ligne, fin_ligne;    //curseur de début et fin de ligne

    fichier = fopen(nom_fichier, "r");

    //ouverture du fichier
    //le fichier n'existe pas
    if (!listdir(nom_fichier)) {
        printf("Erreur : Le fichier %s n'existe pas.\n",nom_fichier);
        return 0;
        }
    //erreur à l'ouverture
    else if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s .\n",nom_fichier);
        return 0;
    }

    //lecture des dimensions de la matrice
    ligne = (char*)malloc(TAILLE_MAX_LIGNE);
    fgets(ligne,TAILLE_MAX_LIGNE,fichier);
    // si il n'y a pas de commentaire au début du fichier
    if (ligne[0]!='#'){
        rewind(fichier);
        fscanf(fichier," %i ",&M_ptr->m);
        fscanf(fichier," %i ",&M_ptr->n);
        rewind(fichier);
        fgets(ligne,TAILLE_MAX_LIGNE,fichier);     //(pour passer la ligne mxn)
    }
    //si il y'a un commentaire
    else{
        rewind(fichier);
        fgets(ligne,TAILLE_MAX_LIGNE,fichier);
        fscanf(fichier," %i ",&M_ptr->m);
        fscanf(fichier," %i ",&M_ptr->n);
        rewind(fichier);
        fgets(ligne,TAILLE_MAX_LIGNE,fichier);     //(pour passer la ligne de commentaire)
        fgets(ligne,TAILLE_MAX_LIGNE,fichier);     //(pour passer la ligne mxn)
    }

    //erreur d'allocation
    if( alloue_matrice(M_ptr) == 1){
             printf("Problème lors de l'allocation de la matrice\n\n.");
             free(M_ptr);
             free(ligne);
             return 0;
    }

    else{

        taille_max_ligne =15*M_ptr->n*sizeof(char);
        ligne = (char*)malloc(TAILLE_MAX_LIGNE);

        for(int i=0;i<M_ptr->m;i++){

            //on lit une ligne en gardant les positions de début et fin de ligne en mémoire
            debut_ligne = ftell(fichier);
            fgets(ligne,taille_max_ligne ,fichier);
            fin_ligne = ftell(fichier);
            //nombre de double sur cette ligne
            nval=1+nombre_espace_str(ligne);

            //on reviens au début de la ligne pour la lire
            fseek(fichier,debut_ligne,SEEK_SET);

            //on lit les doubles
            for(int j=0;j<nval;j++){
                fscanf(fichier,"%lf",&M_ptr->v_ptr[i*M_ptr->n+j]);
              }
            //quand il n'y a plus de double on met des zéros
            for (int j=nval;j<M_ptr->n;j++){
                M_ptr->v_ptr[i*M_ptr->n+j]=0.0;
            }
            //on s'assure d'être à la fin de la ligne après lecture
            fseek(fichier,fin_ligne,SEEK_SET);
        }
    }
    free(ligne);
    rewind(fichier);
    fclose(fichier);
    affiche_matrice(M_ptr);
    return 1;
}





