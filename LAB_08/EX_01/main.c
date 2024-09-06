#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define filename "easy_test_set.txt"

int stop=0;

enum{z,r,t,s};

typedef enum{
    false,true
}boolean;

typedef struct{
    int z,r,t,s;
}OccorrenzePietre;


void initVal(int **val);
void initMark(int **mark,OccorrenzePietre entry);
int perm_r(int pos,int *dist_val, int *sol, int *mark, int n , int n_dist,int count);
int binarySearch(int *dist_val,int *sol,int *mark,int n_dist,int R);
void stampaPietra(int i);
boolean check(int *sol,int pos,int *dist_val,int i);

int main() {
    setbuf(stdout, NULL);
    FILE *fp;
    int *dist_val;
    int *sol;
    int *mark;
    int nr;
    int output=0;
    int R;
    OccorrenzePietre entry;
    fp=fopen(filename,"r");
    fscanf(fp,"%d",&nr);
     for (int i = 0; i < nr; i++) {
            fscanf(fp, "%d %d %d %d", &entry.z, &entry.r, &entry.t, &entry.s);
            sol = (int *) malloc((entry.z + entry.r + entry.t + entry.s) * sizeof(int));
            initVal(&dist_val);
            initMark(&mark, entry);
            R=entry.z + entry.r + entry.t + entry.s;
            printf("Test #%d\n",i+1);
            printf("zaffiri: %d , rubini: %d , topazi: %d , smeraldi: %d \n",entry.z,entry.r,entry.t,entry.s);
            printf("%d\n",binarySearch(dist_val,sol,mark,4,R));
            free(sol);
            free(dist_val);
            free(mark);
        }


    return 0;
}

int perm_r(int pos,int *dist_val, int *sol, int *mark, int n , int n_dist,int count){
   int i;
   if(stop==1)
       return 1;
   if(pos>=n){
      stop=1;
       printf("\n");
       return count+1;
   }
   for(i=0 ; i<n_dist;i++){
       if(mark[i]>0 && check(sol,pos,dist_val,i)==true) {
           mark[i]--;
           sol[pos] = dist_val[i];
           count = perm_r(pos + 1, dist_val, sol, mark, n, n_dist, count);
           mark[i]++;
       }
   }
    return count;
}

boolean check(int *sol,int pos,int *dist_val,int i){
    if(pos>=1){
        switch(sol[pos-1]){
            case z:
                if(dist_val[i]!=z && dist_val[i]!=r)
                    return false;
                else
                    return true;
                break;
            case r:
                if(dist_val[i]!=s && dist_val[i]!=t)
                    return false;
                else
                    return true;
                break;
            case t:
                if(dist_val[i]!=z && dist_val[i]!=r)
                    return false;
                else
                    return true;
                break;
            case s:
                if(dist_val[i]!=s && dist_val[i]!=t)
                    return false;
                else
                    return true;
                break;
        }

    }
    else{
      return true;
    }
}

int binarySearch(int *dist_val,int *sol,int *mark,int n_dist,int R){
    int L=0;
    int M;
    int mTemp;
    while(L<=R){
     mTemp=(L+R)/2;
     if(perm_r(0,dist_val,sol,mark,mTemp,n_dist,0)){
         stop=0;
         M=mTemp;
         L=M+1;
     }
     else{
         R=mTemp-1;
     }
    }
   return M;
}

void initVal(int **val){
    *val=(int*)malloc(4*sizeof(int));
    (*val)[0]=0;
    (*val)[1]=1;
    (*val)[2]=2;
    (*val)[3]=3;
}

void initMark(int **mark,OccorrenzePietre entry){
    *mark=(int*)malloc(4*sizeof(int));
    (*mark)[0]=entry.z;
    (*mark)[1]=entry.r;
    (*mark)[2]=entry.t;
    (*mark)[3]=entry.s;
}

void stampaPietra(int i){
    switch(i){
        case z:
            printf("Z");
            break;
        case r:
            printf("R");
            break;
        case t:
            printf("T");
            break;
        case s:
            printf("S");
            break;
    }
}
