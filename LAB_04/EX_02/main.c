#include <stdio.h>
#define N 4

int majority( int *a, int R);
int majority1( int *a, int l,int r,int size);
int main() {
    int vet[N]={3,3,9,3};
    int C=N;
    majority(vet,C-1);
    return 0;
}

int majority( int *a, int R){
    int s,d;
    int res;
    res=majority1(a,0,R,R+1);
    return res;
}

int majority1( int *a, int l,int r,int size){
    int m=r/2;
    int cntSx=0;
    int cntDx=0;
    int i=0;
    int s=0,d=0;
    if(l>=r)
        return a[r];
    s=majority1(a,l,m,size);
    d=majority1(a,m+1,r,size);
    for(int i=0; i <= r ; i++){
        if(a[i]==s)
            cntSx++;
    }
    i=0;
    if(cntSx>size/2)
        return s;
    for(int i=0; i <= r ; i++){
        if(a[i]==d)
            cntDx++;
    }
    if(cntDx>size/2)
        return d;



    return -1;
}
