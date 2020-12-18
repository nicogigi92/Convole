#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"
#include "foncrand.h"
#include <ctype.h>
#include <dirent.h>

int TAILLE_MAX_FICHIER = 1000;

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

double rempli_matrice(matrice *M_ptr){
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int i=0;
    double MAX = 0;

    printf("Génération d'une matrice %d x %d....\n",M,N);
    for(i=0;i<P;i++)
    {
        double addnbr = rand_ab_d(-10,10);
        M_ptr->v[i]=addnbr;
        if (addnbr > MAX)
        {
            MAX = addnbr;
        }
    }
    printf("Matrice générée. Son max est %f.\n",MAX);
    return MAX;
}

void affiche_matrice(struct matrice *M_ptr){
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int m=0;
    int i=0;
    printf("Affichage de votre matrice %dx%d.\n\n",M,N);
        for(i=0;i<P;i++)
        {
            m=i/N;
            if (m==(i+1)/N)
            {
            printf("%9f ",M_ptr->v[i]);
            }
            else
            {
            printf("%9f\n",M_ptr->v[i]);
            }
        }
    printf("\nFin d'affichage de matrice.\n\n\n");
}

void affiche_matrice_base(matrice *M_ptr){
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
        if (M_ptr->v[i]> 10e-7)
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
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
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
        sprintf(str_int, "%d ", M);
        strcat(char_fichier,str_int);
        sprintf(str_int, "%d", N);
        strcat(char_fichier,str_int);
        strcat(char_fichier,"\n");
        for(i=0;i<P;i++)
        {
            m=i/N;
            if (m==(i+1)/N)
            {
            char s[15] = {0};
            sprintf(s, "%.9lf",M_ptr->v[i]);
            strcat(strcat(char_fichier,s)," ");
            }
            else
            {
            char s[15] = {0};
            sprintf(s, "%.9lf",M_ptr->v[i]);
            strcat(strcat(char_fichier,s),"\n");
            }
        }
        fputs(char_fichier, fichier);
        fclose(fichier);
        printf("L'écriture a fonctionné.\n\n");
        return 1;
        }
}

int nombre_espace_str(char* str){
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
    int c=0;
    int nval= 0;
    int taille_max = 0;
    long debut_ligne, fin_ligne;



    fichier = fopen(nom_fichier, "r");

    taille_max = 1000; //on va limiter les commentaires à 1000 caractères
    //on récupère les dimensions de la matrice et on saute le commenaitre
    if (fichier != NULL) {
        ligne = (char*)malloc(taille_max);
        fgets(ligne,taille_max,fichier);
        if (ligne[0]!='#'){ // si il n'y a pas de commentaire au début du fichier
            rewind(fichier);
            fscanf(fichier," %i ",&M_ptr->m);
            fscanf(fichier," %i ",&M_ptr->n);
            rewind(fichier);
            fgets(ligne,taille_max,fichier);
            }
        else{ //si il y'a un commentaire
            rewind(fichier);
            fgets(ligne,taille_max,fichier);
            fscanf(fichier," %i ",&M_ptr->m);
            fscanf(fichier," %i ",&M_ptr->n);
            rewind(fichier);
            fgets(ligne,taille_max,fichier);
            fgets(ligne,taille_max,fichier);
        }
    }

    //conditions d'arrêt du programme
    if (!listdir(nom_fichier)) {
        printf("Erreur : Le fichier %s n'existe pas.\n",nom_fichier);
        fclose(fichier);
        return 0;
        }
    else if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s .\n",nom_fichier);
        return 0;
    }
    else if (M_ptr->m*M_ptr->n>=100){//matrice trop grande
        printf("Erreur : Matrice trop grande.\n");
        fclose(fichier);
        return 0;
    }
    //if erreur de format à coder
    else{
        taille_max = 11*M_ptr->n*sizeof(char);
        ligne = (char*)malloc(taille_max);
        for(int i=0;i<M_ptr->m;i++){
            //nombre d'espace sur la ligne i
            // pour j allant de 1 à nprime on scan puis on rajoute des zéro
            debut_ligne = ftell(fichier);
            fgets(ligne,taille_max,fichier);
            fin_ligne = ftell(fichier);

            nval=1+nombre_espace_str(ligne); //nombre de valeurs sur une ligne

            fseek(fichier,debut_ligne,SEEK_SET);

            for(int j=0;j<nval;j++){
                fscanf(fichier,"%lf",&M_ptr->v[i*M_ptr->n+j]);
              }

            for (int j=nval;j<M_ptr->n;j++){
                M_ptr->v[i*M_ptr->n+j]=0.0;
            }

           fseek(fichier,fin_ligne,SEEK_SET);
        }
    }
    fclose(fichier);
    affiche_matrice(M_ptr);
    return 1;
}





