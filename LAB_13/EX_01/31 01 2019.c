//
// Created by wizodts on 20/01/2022.
//
int minmaxdiff(int **A, int n, int m){
    int min=INT_MAX;
    int index;
    for(int j=0; j < m ; j++){
        for(int i=0; i < n ; i++){
            if(i+1<n){ //evito di uscire dai bordi
                if(abs(mat[j][i]-mat[j][i+1])<min){
                    min=abs(mat[j][i]-mat[j][i+1]);
                    index=j;
                }
            }
        }
    }
    return index;
}

void splice (list L1, list L2, int start, int num){
link *linkArray;
link x,p;
link temp;
link last;
int cnt=0;
linkArray=(link*)malloc(num*sizeof(link));
for(int i=0 ; i < num ; i++){  //estraggo num elementi
    temp=L2->head;
    L2->head=L2->head->next;
    valArray[i]=temp;
}

for(x=head; x!=NULL ; p=x, x=x->next){
    cnt++;
    if(cnt==start){
        temp=x->next;
        for(link y=x i=num-1; >=0 ; y=y->next,i--){
            y->next=linkArray[i];
            last=y;
        }
        y->next=temp;
        break;
    }
 }
}

int disp_rip(int n,int m,int *lunghezza,int *prezzo,int pos,int cnt,int *sol){



    for(int i=0; i < m ; i++){
        if()
     return count+1;
    }

}

int disp_semplici(int pos,int *sol,int *val,int *mark,int n,int k,int count){
    if(pos>=k){

        return count+1;
    }
  for(int i=0; i < n ; i++){
      if(mark[i]==0) {
          mark[i] = 1;
          sol[pos] = val[i]
          count=disp_semplici(pos + 1);
          mark[i] = 0; //backtrack
      }
  }
    return count;
}

int disp_ripetute7(int pos,int *sol,int *val,int n,int k,int count){
    if(pos>=k){

        return count+1;
    }
    for(int i=0; i < n ; i++){
            sol[pos] = val[i]
            disp_semplici(pos + 1);
    }
    return count;
}





