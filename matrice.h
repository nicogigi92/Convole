#ifndef _MATRICE_H
#define _MATRICE_
typedef struct matrice {
    int m;
    int n;
    double v[100];
    //i=m*N+n,m=i/N div entière, n=i%N reste div entière
    } matrice;
void affiche_alea(int n, double a, double b);
double rand_ab_d(double a, double b);
int listdir(const char* namefile);
double rempli_matrice(matrice *M_ptr);
void affiche_matrice(matrice *M_ptr);
void affiche_matrice_base(matrice *M_ptr);
int ecrit_matrice(matrice *M_ptr, char *nom_fichier, char *commentaire);
int est_nulle(matrice *M_ptr);
int lit_matrice(struct matrice *M_ptr, char * nom_fichier);
int nbr_ligne_mat(FILE * fichier);
int nombre_espace_str(char* str);
#endif
