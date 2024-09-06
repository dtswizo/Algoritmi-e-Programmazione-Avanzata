#include <stdio.h>
#define N 10


int findMaxSize(int vett[]);

int main() {
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
            for(int j=TempStartIndex; j <= i ; j++){
                printf("%d ",vett[j]);
            }
            printf("\n");
        }

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