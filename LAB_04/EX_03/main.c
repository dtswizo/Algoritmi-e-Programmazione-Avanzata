#include <stdio.h>
#include <string.h>

#define N 20

typedef enum{
    false,true
}boolean;

typedef struct{
    char carattere;
    int listaLettere[N];
    int arraySize;
    boolean qualsiasi;
    boolean qualsiasiMinuscola;
    boolean qualsiasiMaiuscola;
    boolean caratteriInclusi;
    boolean caratteriEsclusi;
}Lettere;

char *cercaRegexp(char *src, char *regexp);
void riempiStruct(char *regexp, Lettere array[]);
int controllaCaratteri(char carattere,Lettere entry);



int main() {
    char src[N]="foco";
    char regexp[N]="\Aoto";
    cercaRegexp(src,regexp);
    return 0;
}



char *cercaRegexp(char *src, char *regexp){
  Lettere array[N];
  int flag=0;
  int cnt=0;
  int l=strlen(src);
  char comparison[N];
    riempiStruct(regexp,array);
    //controllo
    for(int i=0; i < l && flag==0; i++){
        if(array[cnt].qualsiasi!=true){
            if(array[cnt].qualsiasiMaiuscola==true && (src[i]<65 || src[i]>90)){
             flag=1;
            }
            else if(array[cnt].qualsiasiMinuscola==true && (src[i]<97 || src[i]>122)){
                flag=1;
            }
            else if(array[cnt].caratteriInclusi==true){
                if(controllaCaratteri(src[i],array[cnt])==-1)
                    flag=1;
            }
            else if(array[cnt].caratteriEsclusi==true){
                if(controllaCaratteri(src[i],array[cnt])==1)
                    flag=1;
            }
            else{
                if(!array[cnt].qualsiasiMaiuscola &&  !array[cnt].qualsiasiMinuscola &&
                !array[cnt].caratteriInclusi  && !array[cnt].caratteriEsclusi && array[cnt].carattere!=src[i])
                    flag=1;
            }
        }
       cnt++;
    }
    if(flag==0)
     printf("src trovata");
    else
        printf("src non trovata");

    return src;
}

void riempiStruct(char *regexp,Lettere array[]){
    int j=0;
    int z=0;
    int cnt=0;
 //init
 for(int i=0 ; i < N ; i++){
     array[i].carattere=1;
     array[i].qualsiasi=false;
     array[i].arraySize=0;
     array[i].qualsiasiMaiuscola=false;
     array[i].qualsiasiMaiuscola=false;
     array[i].caratteriEsclusi=false;
     array[i].caratteriInclusi=false;
 }
 for(int i=0; i < strlen(regexp); i++){
     if(regexp[i]=='.'){
         array[j].qualsiasi=true;
         j++;
     }
     else if (regexp[i]=='[' && regexp[i+1]!='^'){
       for (int z=i+1 ; regexp[z]!=']';z++){
           array[j].caratteriInclusi=true;
           array[j].listaLettere[cnt]=regexp[z];
           cnt++;
       }
       array[j].arraySize=cnt;
       j++;
       i+=cnt+1;
       cnt=0;
     }
     else if (regexp[i]=='[' && regexp[i+1]=='^'){
         for (int z=i+2 ; regexp[z]!=']';z++){
             array[j].caratteriEsclusi=true;
             array[j].listaLettere[cnt]=regexp[z];
             cnt++;
         }
         array[j].arraySize=cnt;
         j++;
         i+=cnt+2;
         cnt=0;
     }
     else if (regexp[i]=='\a'){
         array[j].qualsiasiMinuscola=true;
         j++;
     }
     else if (regexp[i]=='\\' && regexp[i+1]=='A'){
         array[j].qualsiasiMaiuscola=true;
         j++;
         i+=1;
     }
     else{
         array[j].carattere=regexp[i];
         j++;
     }


 }

}

int controllaCaratteri(char carattere,Lettere entry){
    for(int i = 0 ; i < entry.arraySize;i++){
        if(carattere==entry.listaLettere[i])
            return 1;
    }
    return -1;
}