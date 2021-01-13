#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul_matrice.h"
#include "matrice.h"
#include <ctype.h>
#include <dirent.h>


struct matrice  transpose(struct matrice * M_ptr){
   int i;
   int m;
   int n;

    matrice mat_retour;
    (&mat_retour)->m=M_ptr->n;
    (&mat_retour)->n=M_ptr->m;


    if( alloue_matrice(&mat_retour) == 1){
        printf("Problème lors de l'allocation de la matrice\n\n.");
        free((&mat_retour)->v_ptr);
        exit(EXIT_FAILURE);
    }

    else{
        for(i=0;i<M_ptr->m*M_ptr->n;i=i+1){
            m=i/M_ptr->n;
            n=i%M_ptr->n;
            (&mat_retour)->v_ptr[n*M_ptr->m+m]=M_ptr->v_ptr[i];

        }
    }
    return mat_retour;
}

int test_taille_matrice(struct matrice * M1_ptr,struct matrice * M2_ptr){
    if((M1_ptr->m!=M2_ptr->m) || (M1_ptr->n!=M2_ptr->n)){
        printf("Les matrices ne sont pas de la même taille, on ne peut pas faire de calcul.\n\n");
    return 1;
    }
    else{
        return 0;
    }
}

struct matrice  additione(struct matrice * M1_ptr,struct matrice * M2_ptr){

     int i;
     matrice mat_retour;
    (&mat_retour)->m=M1_ptr->m;
    (&mat_retour)->n=M1_ptr->n;

    if( alloue_matrice(&mat_retour) == 1){
        printf("Problème lors de l'allocation de la matrice\n\n.");
        free((&mat_retour)->v_ptr);
        exit(EXIT_FAILURE);
    }
    else{
         for(i=0;i<M1_ptr->m*M1_ptr->n;i=i+1)
            (&mat_retour)->v_ptr[i]=M1_ptr->v_ptr[i]+M2_ptr->v_ptr[i];
    }
    return mat_retour;
}

struct matrice soustrait(struct matrice * M1_ptr,struct matrice * M2_ptr){
    int i;
    matrice mat_retour;
    (&mat_retour)->m=M1_ptr->m;
    (&mat_retour)->n=M1_ptr->n;

    if( alloue_matrice(&mat_retour) == 1){
        printf("Problème lors de l'allocation de la matrice\n\n.");
        free((&mat_retour)->v_ptr);
        exit(EXIT_FAILURE);
    }
    else{
         for(i=0;i<M1_ptr->m*M1_ptr->n;i=i+1)
            (&mat_retour)->v_ptr[i]=M1_ptr->v_ptr[i]-M2_ptr->v_ptr[i];
    }
    return mat_retour;
}

