#include <stdio.h>
#include <stdlib.h>

#define n 20
#define m 20

int findMax(int vet[],int r);

int main() {
    int mat[n][m];
    int points[n];
    int R,C;
    FILE *fp;
    for(int i=0;i<n;i++)
        points[i]=0;
    fp=fopen("mat.txt","r");
    if(fp==NULL){
        printf("File open error");
        EXIT_FAILURE;
    }
    fscanf(fp,"%d %d",&R,&C);
    //store
    for(int i=0; i<R ; i++){
        for(int j=0; j<C; j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    //print
    for(int i=0; i<R ; i++){
        for(int j=0; j<C; j++){
            printf("%d",mat[i][j]);
        }
        printf("\n");
    }
    int flag=0;
    int j=0;
    int res;
    for(int i=0; i<R && flag==0; i++){
        points[i]+=mat[i][j];
        if(i==R-1){
            //controllo il massimo
            res=findMax(points,R);
            printf("\n Giornata %d : Capolista %d\n",j,res);
            i=-1;
            j++;
        }
        if(i==-1 && j == C)
            flag=1;
    }
    return 0;


}

int findMax(int vet[],int r){
  int max=0;
  int index=0;
  for(int i=0; i < r ; i++){
      if(vet[i]>=max){
          max=vet[i];
          index=i;
      }
  }

  return index+1;
}