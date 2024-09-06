#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_SCELTE 4

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione){
    int i=0;
    printf("\nMENU'\n");
    for(i=0;i<N_SCELTE;i++)
        printf("%2d > %s\n",i,scelte[i]);
    scanf(" %d",selezione);
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    char *scelte[] = {
            "Uscita",
            "elencare in ordine alfabetico i vertici e per ogni vertice gli archi che su di esso insistono",
            "dati 3 vertici verificare se formano un sottorafo completo",
            "generare la rappresentazione a lista di adiacenza",
    };

    char codiceRicerca[30];
    Graph G;
    int selezione;
    FILE *fp;
    bool  fineProgramma;
    fineProgramma = falso;
    G=GRAPHload(fp);

    do {
        stampaMenu(scelte, &selezione);
        switch(selezione){

            case 0: {
                fineProgramma = vero;
            } break;

            case 1: {
                userSelection(G,0);
            } break;

            case 2: {
                userSelection(G,1);

            } break;

            case 3: {
                userSelection(G,2);

            } break;
            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!fineProgramma);


    return 0;
}
