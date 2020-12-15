#ifndef _MATRICE_H
#define _MATRICE_
typedef struct matrice {
    int m;
    int n;
    double v[100];
    //i=m*N+n,m=i/N div entière, n=i%N reste div entière
    } matrice;
double rempli_matrice(matrice *M_ptr);
void affiche_matrice(matrice *M_ptr);
void affiche_matrice_base();
int ecrit_matrice(matrice *M_ptr, char *nom_fichier, char *commentaire);
int est_nulle(matrice *M_ptr);
#endif
