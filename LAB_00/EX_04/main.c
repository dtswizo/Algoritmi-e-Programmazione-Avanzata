#include <stdio.h>
#include <stdlib.h>

#define N 20


int main() {
    FILE *fp;
    int mat[N][N];
    int min;
    int flag=0;
    int input;
    int cnt=0;
    fp=fopen("mat.txt","r");
    int R,C;
    if(fp==NULL){
        return -1;
    }
    fscanf(fp,"%d %d",&R,&C);
    if(R>C)
        min=C;
    else
        min=R;
    for(int i =0 ; i < R ; i++){
        for(int j=0 ; j < C ; j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }

    do{
    cnt=0;
    printf("\nInserisci un valore compreso tra 1 e %d : \n",min);
    scanf("%d", &input);
    if(input<1 || input>min)
        flag=1;
    for(int i=0; i < R ; i++){
        for(int j=0 ; j < C ; j++){
              for(int z=i; z+input<=R  && z < min ; z++){
                  for(int x=j; x+input<=C  && x < min ; x++){
                      printf("%d",mat[z][x]);
                  }
              }
              printf("\n");
        }
    }



    }
    while(flag==0);

    return 0;
}
