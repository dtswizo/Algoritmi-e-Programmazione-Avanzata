#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 20
#define S 5
#define X 200
#define Y 25


int findMatch(char string[S]);

int main() {
    FILE *fp;
    int nr;
    int wordCnt=0;
    char sequenze[N][S];
    char temp[S];
    char riga[X];
    char parola [Y];
    fp=fopen("sequenze.txt","r");
    fscanf(fp,"%d",&nr);
    for(int i=0 ; i < nr ; i++){
        fscanf(fp,"%s",temp);
        findMatch(temp);
        strcpy(sequenze[i],temp);
    }
    fclose(fp);
    return 0;
}


int findMatch(char string[S]){
    FILE *fp;
    char ch;
    char word[Y];
    int indiceParola=0;
    int cnt=0;
    int wordCount=1;
    int trovato=0;
    int j=0;
    for(int i=0; i< strlen(string); i++){
        string[i]=tolower(string[i]);
    }
    fp=fopen("testo.txt","r");
    while((fscanf(fp,"%c",&ch))!=EOF){
        if(isspace(ch) || ch=='\n' || ch==39) {   //39 ASCII CODE OF " ' "
            wordCount++;
            word[indiceParola]='\0';
            indiceParola=0;
            if(trovato==1)
                printf(" nella parola %s\n",word);
            trovato=0;
        }
        else
            word[indiceParola++]=ch;

        ch=tolower(ch);
        if(ch==string[j]) {
            cnt++;
            j++;
        }
        else {
            cnt = 0;
            j=0;
        }
        if(cnt==strlen(string)) {
            printf("trovato %s in posizione %d", string, wordCount);
            trovato=1;
        }
    }



    return 1;
}
