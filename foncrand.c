#include <stdio.h>
#include <stdlib.h>
#include "foncrand.h"
#include "matrice.h"
#include <dirent.h>
#include <string.h>

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


int listdir(const char* namefile)
{
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
