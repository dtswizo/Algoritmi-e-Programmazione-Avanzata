#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta(char S[20], int n);

int main() {
    FILE *fp;
    int N;
    int n=3; //numero di grandezza sotto stringhe
    int totRes=0;
    char word[20];
    fp=fopen("testo.txt","r");
    if(fp==NULL){
        return -1;
    }
    fscanf(fp,"%d",&N);
    for(int i=0; i < N ; i++){
        fscanf(fp,"%s",word);
        totRes+=conta(word,n);
    }
    printf("Totale sotto stringhe di lunghezza %d con esattamente 2 vocali: %d",n,totRes);
    return 0;
}

int conta(char S[20], int n){
    int res=0;
    int cnt=0;
   for(int i=0; i < strlen(S) ; i++){
       for(int j=i; j < i+n && i+n<=strlen(S); j++){
           if(S[j]=='a' || S[j]=='e' || S[j]=='i' || S[j]=='o' || S[j]=='u'){
               cnt++;
           }
       }
       if(cnt==2)
           res++;
       cnt=0;
   }
    return res;
}

