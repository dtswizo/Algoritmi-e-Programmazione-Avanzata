#include <stdio.h>
#include <string.h>

#define S 30
#define N 1000

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
}comando_e;

typedef struct{
    char cod_tratta[S];
    char partenza[S];
    char destinazione[S];
    char data[S];
    char ora_partenza[S];
    char ora_arrivo[S];
    int ritardo;
}tratte;

//tools
comando_e leggiComando();
long dateToLong(char date[S]);
void stampaTratta(tratte vett[],int index);
void selezionaDati(tratte vett[],int nr,comando_e cmd);
//proper functions
int confrontaDate(char data1[S],char data2[S]);


int main() {
    tratte arrayTratte[N];
    FILE *fp;
    int nr;
    int exit=0;
    //lettura
    fp=fopen("log.txt","r");
    fscanf(fp,"%d",&nr);
    //memorizzazione
    for(int i = 0 ; i < nr ; i++){
        fscanf(fp," %s %s %s %s %s %s %d", arrayTratte[i].cod_tratta,arrayTratte[i].partenza,
               arrayTratte[i].destinazione,arrayTratte[i].data,arrayTratte[i].ora_partenza,
               arrayTratte[i].ora_arrivo,&arrayTratte[i].ritardo);
    }
    do{
    switch(leggiComando()){
        case r_date:
            selezionaDati(arrayTratte,nr,r_date);
            break;
        case r_partenza:
            selezionaDati(arrayTratte,nr,r_partenza);
            break;
        case r_capolinea:
            selezionaDati(arrayTratte,nr,r_capolinea);
            break;
        case r_ritardo:
            selezionaDati(arrayTratte,nr,r_ritardo);
            break;
        case r_ritardo_tot:
            selezionaDati(arrayTratte,nr,r_ritardo_tot);
            break;
        case r_fine:
            exit=1;
            break;
    }

    }
    while(!exit);
    return 0;
}

//main functions

int confrontaDate(char data1[S],char data2[S]){
    long data1l,data2l;
    data1l=dateToLong(data1);
    data2l=dateToLong(data2);
    if(data1l>=data2l)
        return 1;
    else
        return 0;
}












//tool
comando_e leggiComando(){
  char selezione[S];
  char tabella[r_fine][S]={"date","partenza","capolinea","ritardo","ritardotot"};
  printf("\nInserisci comando : date , partenza , capolinea, ritardo , ritardotot, fine: \n");
  scanf("%s",selezione);
  for(int i=0; i < r_fine; i++){
      if(strcmp(tabella[i],selezione)==0)
          return i;
  }
  return r_fine;
}
void selezionaDati(tratte vett[],int nr,comando_e cmd){
tratte d1,d2;
int tot=0;
switch(cmd){
    case r_date:
        printf("\n Inserisci due date nel formato AAAA/MM/DD separate da spazio:\n");
        scanf("%s %s",d1.data,d2.data);
        break;
    case r_partenza:
        printf("\n Inserisci fermata di partenza: \n");
        scanf("%s",d1.partenza);
        break;
    case r_capolinea:
        printf("\n Inserisci fermata di arrivo: \n");
        scanf("%s",d1.destinazione);
        break;
    case r_ritardo:
        printf("\n Inserisci due date nel formato AAAA/MM/DD separate da spazio:\n");
        scanf("%s %s",d1.data,d2.data);
        break;
    case r_ritardo_tot:
        printf("\n Inserisci Codice tratta:\n");
        scanf("%s",d1.cod_tratta);
        break;
    case r_fine:
        break;
}
    switch(cmd){
        case r_date:
            for(int i=0; i < nr ; i++){
                if(confrontaDate(vett[i].data,d1.data) && !confrontaDate(vett[i].data,d2.data))
                    stampaTratta(vett,i);
            }
            break;
        case r_partenza:
            for(int i=0; i < nr ; i++){
                if(!strcmp(vett[i].partenza,d1.partenza))
                    stampaTratta(vett,i);
            }
            break;
        case r_capolinea:
            for(int i=0; i < nr ; i++){
                if(!strcmp(vett[i].destinazione,d1.destinazione))
                    stampaTratta(vett,i);
            }
            break;
        case r_ritardo:
            for(int i=0; i < nr ; i++){
                if(confrontaDate(vett[i].data,d1.data) && !confrontaDate(vett[i].data,d2.data) && &vett[i].ritardo!=NULL)
                    stampaTratta(vett,i);
            }
            break;
        case r_ritardo_tot:
            for(int i=0; i < nr ; i++){
                if(!strcmp(vett[i].cod_tratta,d1.cod_tratta) && &vett[i].ritardo!=NULL)
                   tot+=vett[i].ritardo;
            }
            printf("\n ritardo accumulato %d \n",tot);
            break;
        case r_fine:
            break;
    }


}
long dateToLong(char date[S]){
    int d,m,a;
    long res;
    sscanf(date,"%d/%d/%d",&a,&m,&d);
    a-=2017;
    res=a*31536000+2592000*m+86400*d;
    return res;
}
void stampaTratta(tratte vett[],int index){
    printf(" %s %s %s %s %s %s %d\n", vett[index].cod_tratta, vett[index].partenza,
           vett[index].destinazione, vett[index].data, vett[index].ora_partenza,
           vett[index].ora_arrivo, vett[index].ritardo);
}