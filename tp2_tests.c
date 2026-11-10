#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define printf(...) ((void)0)
#include "algo_A.c"
#include "algo_B.c"
#undef printf

volatile int sink;

int alea(void){ return ((rand()&0x7FFF)<<15) | (rand()&0x7FFF); } 

double mesure(int (*f)(int*,int,int), int T[], int n, int x, long reps){
    long r;
    clock_t t0=clock();
    for(r=0;r<reps;r++) sink=f(T,n,x);
    clock_t t1=clock();
    return (double)(t1-t0)/CLOCKS_PER_SEC/reps*1e6;
}

/* Partie A  */
void testsA(void){
    int N[]={100000,200000,400000,600000,800000,1000000,1200000,1400000,1600000,1800000};
    int nb=sizeof(N)/sizeof(N[0]);
    int k,i;
    FILE *fc=fopen("resultats_A.csv","w");
    fprintf(fc,"n;NT_meilleur;NT_pire;T_meilleur;T_pire;Dicho_meilleur;Dicho_pire\n");
    printf("%9s | %10s %10s | %10s %10s | %10s %10s   (microsecondes)\n",
           "n","NT_best","NT_worst","T_best","T_worst","Di_best","Di_worst");

    for(k=0;k<nb;k++){
        int n=N[k];
        int *NT=malloc(n*sizeof(int)), *T=malloc(n*sizeof(int));
        long repsLin, repsBest=5000000, repsDicho=2000000;
        double a1,a2,b1,b2,c1,c2;

        for(i=0;i<n;i++){ NT[i]=alea()%1000000; T[i]=2*i; }   /* NT aleatoire, T trie */

        repsLin=200000000L/n; if(repsLin<1) repsLin=1;

        /* Non tries : meilleur = x en 1ere case ; pire = x absent (-1) */
        a1=mesure(rechElets_TabNonTries,NT,n,NT[0],repsBest);
        a2=mesure(rechElets_TabNonTries,NT,n,-1,repsLin);
        /* Tries sequentiel : meilleur = T[0] ; pire = x plus grand que tout */
        b1=mesure(rechElets_TabTries,T,n,T[0],repsBest);
        b2=mesure(rechElets_TabTries,T,n,2*n,repsLin);
        /* Dichotomie : meilleur = element du milieu ; pire = x absent */
        c1=mesure(rechDichotomique,T,n,T[(0+n-1)/2],repsDicho);
        c2=mesure(rechDichotomique,T,n,2*n+1,repsDicho);

        printf("%9d | %10.4f %10.2f | %10.4f %10.2f | %10.4f %10.4f\n",n,a1,a2,b1,b2,c1,c2);
        fprintf(fc,"%d;%.4f;%.4f;%.4f;%.4f;%.4f;%.4f\n",n,a1,a2,b1,b2,c1,c2);
        free(NT); free(T);
    }
    fclose(fc);
}

/* Partie B */
void testsB(void){
    int N[]={100000,200000,400000,600000,800000,1000000,1200000,1400000,
             1600000,1800000,2000000,4000000,6000000,8000000};
    int nb=sizeof(N)/sizeof(N[0]);
    int k,i;
    FILE *fc=fopen("resultats_B.csv","w");
    fprintf(fc,"n;cmp_A;cmp_B;theo_A;theo_B;temps_A_ms;temps_B_ms\n");
    printf("%9s | %12s %12s | %12s %12s | %9s %9s\n",
           "n","cmp_A","cmp_B","2(n-1)","ceil(3n/2)-2","t_A(ms)","t_B(ms)");

    for(k=0;k<nb;k++){
        int n=N[k];
        int *orig=malloc(n*sizeof(int)), *w=malloc(n*sizeof(int));
        long reps,r;
        int mn,mx;
        clock_t t0,t1;
        double tcopie,tA,tB;
        long long cA,cB,thA,thB;

        for(i=0;i<n;i++) orig[i]=i+1;
        for(i=n-1;i>0;i--){ int j=alea()%(i+1); int t=orig[i]; orig[i]=orig[j]; orig[j]=t; }

        reps=200000000L/n; if(reps<5) reps=5;

        /* 1) nombre de comparaisons : UN appel, on lit le 'compteur' de l'equipe */
        memcpy(w,orig,n*sizeof(int)); MaxEtMinA(w,n,&mn,&mx); cA=compteur;
        memcpy(w,orig,n*sizeof(int)); MaxEtMinB(w,n);         cB=compteur;

        /* 2) temps de la simple copie (a soustraire, car MaxEtMinB modifie le tableau) */
        t0=clock(); for(r=0;r<reps;r++) memcpy(w,orig,n*sizeof(int)); t1=clock();
        tcopie=(double)(t1-t0)/CLOCKS_PER_SEC*1000.0/reps;

        /* 3) temps de MaxEtMinA */
        t0=clock();
        for(r=0;r<reps;r++){ memcpy(w,orig,n*sizeof(int)); MaxEtMinA(w,n,&mn,&mx); }
        t1=clock();
        tA=(double)(t1-t0)/CLOCKS_PER_SEC*1000.0/reps - tcopie;

        /* 4) temps de MaxEtMinB */
        t0=clock();
        for(r=0;r<reps;r++){ memcpy(w,orig,n*sizeof(int)); MaxEtMinB(w,n); }
        t1=clock();
        tB=(double)(t1-t0)/CLOCKS_PER_SEC*1000.0/reps - tcopie;

        thA=2LL*(n-1); thB=(3LL*n+1)/2-2;
        printf("%9d | %12lld %12lld | %12lld %12lld | %9.3f %9.3f\n",n,cA,cB,thA,thB,tA,tB);
        fprintf(fc,"%d;%lld;%lld;%lld;%lld;%.4f;%.4f\n",n,cA,cB,thA,thB,tA,tB);
        free(orig); free(w);
    }
    fclose(fc);
}

int main(void){
    srand((unsigned)time(NULL));
    printf("PARTIE A\n"); testsA();
    printf("\nPARTIE B\n"); testsB();
    return 0;
}
