#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"
#include "foncrand.h"

int TAILLE_MAX_FICHIER = 1000;


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

void affiche_matrice(struct matrice *M_ptr)
{
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

void affiche_matrice_base()
{
    matrice mat;
    mat.m=3;
    mat.n=3;
    rempli_matrice(&mat);
    affiche_matrice(&mat);
}

int est_nulle(matrice *M_ptr){
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



int ecrit_matrice(struct matrice *M_ptr, char (*nom_fichier)[20], char (*commentaire)[50])
{
    //chaine qu'on va écrire dans le fichier
    char chemin_fichier[71];
    char char_fichier[1000]={0};
    //on ouvre le fichier en mode écriture
    FILE* fichier = NULL;
    fichier = fopen(chemin_fichier, "w");
    //matrice
    int M=M_ptr->m;
    int N=M_ptr->n;
    int P = M*N;
    int m=0;
    int i=0;


    if (strlen(*nom_fichier)>50)
    {
        printf("\n Le nom de fichier est trop long (>50).\n");
        return 0;
    }


    strcpy(chemin_fichier,"/home/nico/C/Convole/");
    strcat(chemin_fichier,*nom_fichier);
    //on ajoute le commentaire au début
    strcpy(char_fichier,"#");
    strcat(char_fichier,*commentaire);
    strcat(char_fichier,"\n");
    //on écrit dans la matrice comme on les avait print en passant par une chaine de caractère
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

    if ((fichier != NULL) && !(est_nulle(M_ptr)))
        {
        fputs(char_fichier, fichier);
        fclose(fichier);
        printf("L'écriture a fonctionné.\n\n");
        return 1;
        }
    else
        {
        fclose(fichier);
        printf("L'écriture a échoué.\n\n");
        return 0;
        }
}
