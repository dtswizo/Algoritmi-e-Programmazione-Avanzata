#include <stdio.h>
#define N 10

typedef struct{
    int startIndex;
    int endIndex;
 }subvectors;

int findMaxSize(int vett[]);

int main() {
    subvectors subvec[N];
    int structIndex=0;
    int maxSize;
    int TempStartIndex;
    int cnt=0;
    int vett[N]={1,3,4,0,1,0,9,4,2,0};
    maxSize=findMaxSize(vett);
    for(int i=0; i < N ; i++){
       if(vett[i]!=0){
         cnt++;
         if(cnt==1)
         TempStartIndex=i;
       }
       else
           cnt=0;
       if(cnt==maxSize){
           subvec[structIndex].startIndex=TempStartIndex;
           subvec[structIndex].endIndex=i;
           structIndex++;
       }

    }
    //mi sono complicato la vita per niente, non mi serviva memorizzare tutto
    printf("%d SubVectors of %d size found\n",structIndex,maxSize);
    for(int i=0; i < structIndex; i++){
        printf("SubVector n %d : ",i);
        for(int j=subvec[i].startIndex; j <= subvec[i].endIndex;j++){
            printf("%d ", vett[j]);
        }
        printf("\n");
    }

    return 0;
}

int findMaxSize(int vett[]){
    int max=0;
    int cnt=0;
    for(int i=0; i < N ; i++){
        if(vett[i]!=0)
            cnt++;
        else
            cnt=0;
        if(cnt>max)
            max=cnt;
    }

    return max;
}