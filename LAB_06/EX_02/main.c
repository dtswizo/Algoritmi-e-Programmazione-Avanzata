#include <stdio.h>
#include <malloc.h>



void malloc2dP(int ***ptr,int nr,int nc);
int** malloc2dR(int nr,int nc);
void separa(int **mat, int nr, int nc,int **vN,int **vB,int *sizeN,int *sizeB);

int main() {
   FILE *fp;
   int nr,nc;
   int **mat;
   int *vN,*vB;
   int sizeN,sizeB;
   fp=fopen("nmat.txt","r");
   if(fp==NULL)
       return -1;
   fscanf(fp,"%d %d",&nr,&nc);
   malloc2dP(&mat,nr,nc);
   //mat=malloc2dR(nr,nc);
   for(int i = 0 ; i < nr ; i++){
       for(int j=0; j < nc ; j++){
           fscanf(fp,"%d",&mat[i][j]);
       }
   }
    for(int i = 0 ; i < nr ; i++){
        for(int j=0; j < nc ; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    separa(mat,nr,nc,&vN,&vB,&sizeN,&sizeB);
    printf("\nBlack : ");
    for(int i=0; i < sizeN; i++)
        printf(" %d ",vN[i]);
    printf("\nWhite : ");
    for(int i=0; i < sizeB; i++)
        printf("%d ",vB[i]);
    free(vN);
    free(vB);

    return 0;
}

void malloc2dP(int ***ptr,int nr,int nc){
    int **tmp;
    tmp=(int**)malloc(nr*sizeof(int*));
    for(int i = 0 ; i < nr; i++)
        tmp[i]=(int*)malloc(nc*sizeof(int));
   *ptr=tmp;
}

int** malloc2dR(int nr,int nc){
  int **res;
  res=(int**)malloc(nr*sizeof(int*));
  for(int i = 0 ; i < nr; i++)
  res[i]=(int*)malloc(nc*sizeof(int));
    return res;
}

void separa(int **mat, int nr, int nc,int **vN,int **vB,int *sizeN,int *sizeB){
    int cntN=0;
    int cntB=0;
    if(nr==nc){
        *sizeN=(nr*nc)/2+1;
        *sizeB=(nr*nc)/2;
    }
    else{
        *sizeN=(nr*nc)/2;
        *sizeB=(nr*nc)/2;
    }
    //allocazione vettori
    *vN=(int*)malloc((*sizeN)*sizeof(int));
    *vB=(int*)malloc((*sizeB)*sizeof(int));
        for(int i = 0 ; i < nr ; i++){
            for(int j=0 ; j < nc ; j++){
                if((i+j)%2==0)
                    (*vN)[cntN++]=mat[i][j];
                else
                    (*vB)[cntB++]=mat[i][j];
            }
        }
}