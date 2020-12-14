#include <stdio.h>
#include <stdlib.h>
#include "foncrand.h"
#include "matrice.h"

double rand_ab_d(double a, double b){
    double c ;
    if ( a > b ) {
        c = a ;
        a = b ;
        b = c ;
    }
    return (a + (b-a) * (rand()/(RAND_MAX+1.0))) ;
}

void affiche_alea(int n, double a, double b)
{
    int i;
    for(i=1;i<=n;i++){
        double nombre = rand_ab_d(a,b);
        printf("%f \n",nombre);
    }
}
