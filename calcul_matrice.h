#ifndef _CALCUL_MATRICE_H
#define _CALCUL_MATRICE_
struct matrice  transpose(struct matrice * M_ptr);
int test_taille_matrice(struct matrice * M1_ptr,struct matrice * M2_ptr);
struct matrice additione(struct matrice * M1_ptr,struct matrice * M2_ptr);
struct matrice soustrait(struct matrice * M1_ptr,struct matrice * M2_ptr);
#endif
