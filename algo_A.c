#include<stdio.h>
#include <stdbool.h>


int rechElets_TabNonTries(int T[],int n,int x){
    int i=0;
    bool trouver;
    trouver=false;
    while (i<n && trouver==false){
        if (T[i]==x){
            
            trouver=true;

            printf("l'element %d est trouve dans le tableau a la posistion %d \n",x,i+1);

         
        }
        else{i++;}

    }
    if(trouver==false){
     printf("L'element %d n'existe pas dans le tableau\n", x);

    }
    return trouver;


}

int rechElets_TabTries(int T[],int n,int x){
 
    int i,t;
    bool trouver;
    trouver=false;

    if(x<T[n/2]){
      i=0;
      t=n/2;  
    }else{
        i=(n/2);
        t=n;
    }
    while (i<t && trouver==false){
        if (T[i]==x){
            
            trouver=true;

            printf("l'element %d est trouve dans le tableau a la posistion %d \n",x,i+1);

         
        }
        else{i++;}

    }
    if(trouver==false){
     printf("L'element %d n'existe pas dans le tableau\n", x);

    }
    return trouver;

}

int rechDichotomique(int T[], int n, int x)
{
    int gauche = 0;
    int droite = n - 1;
    int milieu;


    while (gauche <= droite)
    {

        milieu = (gauche + droite) / 2;


        if (T[milieu] == x) {
            return milieu + 1;
        }
        if (x < T[milieu])
            droite = milieu - 1;

        else
            gauche = milieu + 1;
    }

    return -1;
}

