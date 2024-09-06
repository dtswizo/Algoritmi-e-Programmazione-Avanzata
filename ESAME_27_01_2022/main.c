#include <stdio.h>
#include <malloc.h>
#define N 100

typedef struct{
    char ID;
    int upSx[2];
    int upDx[2];
    int downSx[2];
    int downDx[2];
}sottoregioneBianca;

typedef enum{false,true}boolean;

boolean matriceQuadrata(sottoregioneBianca entry);
int contaCelleBianche(int **mat,int nr,int nc);
void disp_sempliciW(int **mat,int nr,int nc);
boolean disp_semplici(int pos,sottoregioneBianca **sol,int **val,int k,int nr,int nc,int **mark);
sottoregioneBianca prendiMassimaMatriceQuadrata(int ***mark,int **mat,int nr, int nc, int i,int j);
void backtrack(int ***mat,sottoregioneBianca temp);
boolean lastCheck(int **mat,int **mark,int nr,int nc);





int main() {
    FILE *fp;
    sottoregioneBianca *entriesSottoregione;
    int NRG,NCG;
    int Nentries;
    int **mat;
    int **prop;
    int sum=0;
    fp=fopen("griglia.txt","r");
    if(fp==NULL){
        return -1;
    }
    fscanf(fp,"%d %d",&NRG,&NCG);
    //allocazione matrice
    mat=(int**)malloc(NRG*sizeof(int*));
    for(int i=0; i < NRG ; i++){
        mat[i]=(int*)malloc(NCG*sizeof(int));
    }
    //store
    for(int i=0; i < NRG; i++ ){
        for(int j=0; j < NCG ; j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);
    fp=fopen("proposta.txt","r");
    if(fp==NULL)
        return -2;
    fscanf(fp,"%d",&Nentries);
    entriesSottoregione=(sottoregioneBianca*)malloc(Nentries*sizeof(sottoregioneBianca));
    for(int i=0; i < Nentries; i++){
        fscanf(fp," %c %d %d %d %d %d %d %d %d",&(entriesSottoregione[i]).upSx[0],&(entriesSottoregione[i]).upSx[1],&(entriesSottoregione[i]).upDx[0],
               &(entriesSottoregione[i]).upSx[1],&(entriesSottoregione[i]).downSx[0],&(entriesSottoregione[i]).downSx[1],&(entriesSottoregione[i]).downDx[0],
               &(entriesSottoregione[i]).downDx[1]);
    }
    fclose(fp);
    //fase di verifica
    for(int i=0; i < Nentries; i++){
      if(!matriceQuadrata(entriesSottoregione[i])){
          printf("sottoregione non Valida");
          return -3;
      }
      sum+=(entriesSottoregione[i].upDx[1]-entriesSottoregione[i].upSx[1])*(entriesSottoregione[i].upDx[1]-entriesSottoregione[i].upSx[1]);
    }
    if(sum != contaCelleBianche(mat,NRG,NCG)){
        printf("Le sottoregioni non coprono tutte le celle bianche");
        return -4;
    }
    disp_sempliciW(mat,NRG,NCG);
    return 0;
}

boolean matriceQuadrata(sottoregioneBianca entry){
    if((entry.upDx[1]-entry.upSx[1])==(entry.downDx[0]-entry.upDx[0]))
        return true;
    else
        return false;
}

int contaCelleBianche(int **mat,int nr,int nc){
    int cnt=0;
    for(int i=0; i < nr ; i++){
        for(int j=0; j < nc ; j++){
            if(mat[i][j]==0)
                cnt++;
        }
    }
    return cnt;
}

void disp_sempliciW(int **mat,int nr,int nc){
    int **mark;
    mark=(int**)malloc(nr*sizeof(int));
    for(int i=0; i < nr; i++)
        mark[i]=(int*)malloc(nc*sizeof(int));
    sottoregioneBianca  *sol;
    sol=(sottoregioneBianca*)malloc(N*sizeof(sottoregioneBianca));
    for(int i=1 ; i < N ; i++){
        disp_semplici(0,&sol,mat,i,nr,nc,mark);
    }
     return;
}

boolean disp_semplici(int pos,sottoregioneBianca **sol,int **val,int k,int nr,int nc,int **mark){
    sottoregioneBianca temp;
    if(pos>=k){
            printf("\nsoluzione con %d quadrati trovata",k);
            return true;
        }

    for(int i=0 ; i < nr ; i++){
        for(int j=0 ; j < nc ; j++){
            if(val[i][j]==0 && mark[i][j]==0){  //controlla se la casella è bianca e non marcata
            temp= prendiMassimaMatriceQuadrata(&mark,val,nr,nc,i,j);
            (*sol)[i]=temp;
            disp_semplici(pos+1,sol,val,k,nr,nc,mark);
            backtrack(&mark,temp);
            }
        }
    }
    return false;
}

sottoregioneBianca prendiMassimaMatriceQuadrata(int ***mark,int **mat,int nr, int nc, int i,int j){
    //funzione incompleta non sono arrivato a implementarla all'esame
    sottoregioneBianca res;
    int x,y;
    int maxlun=0, maxh=0;
    int dim;
    int estremiRiga[2];
    int estremiColonna[2];
    for(x=i; x < nr ; x++){
        if(mat[x][j]==0 && (*mark)[x][j]==0){  //controllo che le caselle siano bianche e non marcate
            maxh++;
            estremiRiga[1]=x;
        }
        else
            break;
    }
    for(x=i; x >= 0 ; x--){
        if(mat[x][j]==0 && (*mark)[x][j]==0){  //controllo che le caselle siano bianche e non marcate
            maxh++;
            estremiRiga[0]=x;
        }
        else
            break;
    }
    for(y=j; x < nr ; y++){
        if(mat[i][y]==0 && (*mark)[i][y]==0){  //controllo che le caselle siano bianche e non marcate
            estremiColonna[1]=y;
        }
        else
            break;
    }
    for(y=j; y > 0 ; y--){
        if(mat[i][y]==0 && (*mark)[i][y]==0){  //controllo che le caselle siano bianche e non marcate
            estremiColonna[0]=y;
        }
        else
            break;
    }
    if(maxlun==maxh){
        for(int x=estremiRiga[0]; x <= estremiRiga[1]; x++) {
            for (int y = estremiColonna[0]; y <= estremiColonna[1]; j++){
                (*mark)[x][j]=1;
            }
        }
        res.upSx[0]=estremiRiga[0];
        res.upSx[1]=estremiColonna[0];
        res.upDx[0]=estremiRiga[1];
        res.upDx[1]=estremiColonna[1];
    }
    return res;
}

//funzione non implementata all'esame
void backtrack(int ***mat,sottoregioneBianca temp){
    //smarco il cubo preso precedentemente
    for(int i=temp.upSx[0] ; i <= temp.downSx[0] ; i++){
        for(int j=temp.upSx[1]; j <= temp.downDx[1];j++){
            (*mat)[i][j]=0;
        }
    }
    return;
}


//funzione non implementata all'esame
boolean lastCheck(int **mat,int **mark,int nr,int nc){
    for(int i=0; i < nr ; i++){
        for(int j=0; j < nc ; j++){
            if(mat[i][j]==0 && mark[i][j]!=1){
                return false;   //se almeno un elemento bianco non è stato preso la soluzione è errata
            }
        }
    }
    return true;
}
