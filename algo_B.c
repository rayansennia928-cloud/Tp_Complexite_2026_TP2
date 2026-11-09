#include<stdlib.h>
#include<stdlib.h>
#include <stdbool.h>

int compteur;
int min, max;

void MaxEtMinA(int T[],int n, int *min, int *max){
    int i=0;
    compteur=0;
    *min=T[0];
    *max=T[0];
    for(i=1;i<n;i++){
        compteur++;
        if(T[i]<*min){
            *min=T[i];
        }
       
        compteur++;

        if(T[i]>*max){
            *max=T[i];
        }
    }
    printf("Min = %d\n", *min);
printf("Max = %d\n", *max);
printf("Comparaisons = %d\n", compteur);
   
}

void MaxEtMinB(int T[], int n) {
    int i, min, max, c;

    compteur = 0;

    // Initialisation avec la première paire
    compteur++;

    if(T[0] < T[1]) {
        min = T[0];
        max = T[1];
    }
    else {
        min = T[1];
        max = T[0];
    }

    // Traitement des autres paires
    for(i = 2; i+1 < n; i += 2) {

        compteur++;

        if(T[i] < T[i+1]) {
            c = T[i];
            T[i] = T[i+1];
            T[i+1] = c;
        }

        compteur++;
        if(T[i+1] < min) {
            min = T[i+1];
        }

        compteur++;
        if(T[i] > max) {
            max = T[i];
        }
    }

    // Traitement du dernier élément si n est impair
    if(n % 2 != 0) {
        compteur++;

        if(T[n-1] < min) {
            min = T[n-1];
        }

        compteur++;

        if(T[n-1] > max) {
            max = T[n-1];
        }
    }

    printf("Min = %d\n", min);
    printf("Max = %d\n", max);
    printf("Comparaisons = %d\n", compteur);
}

