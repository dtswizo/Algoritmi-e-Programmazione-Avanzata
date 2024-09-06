#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 30

typedef struct{
    char ricodifica[20];
    char originale[20];
}ricodifica;
ricodifica vett[S];

char* checkString(char word[],int cnt,FILE *sp);

int main() {
    FILE *fp;
    FILE *sp;
    char tempRicodifica[20];
    char tempOriginale[20];
    char temp[20];
    char* res;
    int cnt=0;
    fp=fopen("dizionario.txt","r");
    if(fp==NULL) {
        return -1;
    }

    fscanf(fp,"%d",&cnt);
    for(int i=0;i < cnt ; i++){
        fscanf(fp,"%s %s",tempRicodifica,tempOriginale);
        strcpy(vett[i].ricodifica,tempRicodifica);
        strcpy(vett[i].originale,tempOriginale);
    }
    fclose(fp);
    int flagCase1=0;
    fp=fopen("sorgente.txt","r");
    if(fp==NULL) {
        return -1;
    }
    sp=fopen("ricodifica.txt","w");
    while(fscanf(fp,"%s",temp)==1){
        //case 1 se la parola da sostituire è completa
        for(int i=0; i < cnt && flagCase1==0; i++){
            if(strcmp(temp,vett[i].originale)==0){
                fprintf(sp,"%s ",vett[i].ricodifica);
                flagCase1=1;
            }
        }
        //case 2 se devo sostituire un frammento di una parola
        if(flagCase1==0){
            res=checkString(temp,cnt,sp);

        }
        flagCase1=0;
    }


    return 0;
}

char* checkString(char word[],int cnt,FILE *sp){
    char * ptr;
    char res[20];
    int flag=0;
    int flagRes=0;
    int counter=0;
    int counter2=0;
    int trovato=0;
    for(int i=0; i< cnt && flag==0; i++){
        ptr=strstr(word,vett[i].originale);
        if(ptr!=NULL){
            //printf("\n%s found in %s\n",vett[i].originale,word);
             while(flagRes==0){
               if(&word[counter2]==ptr){
                   strncpy(&res[counter],vett[i].ricodifica,strlen(vett[i].ricodifica));
                   counter+=strlen(vett[i].ricodifica);
                   counter2+=strlen(vett[i].originale);
                   trovato=1;
               }
               else{
                   if(word[counter2]=='\0'){
                       flagRes=1;
                       res[counter]=word[counter2];
                   }
                   else {
                       res[counter]=word[counter2];
                       counter++;
                       counter2++;
                   }

               }

             }
            flag=1;

        }
    }
    if(trovato==1)
    fprintf(sp,"%s ",res);
    else
        fprintf(sp,"%s ",word);

   return res;
}