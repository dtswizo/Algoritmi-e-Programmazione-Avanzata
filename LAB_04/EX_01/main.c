#include <stdio.h>

typedef enum{
    false, true
}boolean;


int gcd(int a, int b);
boolean isEven(int entry);

int main(){
    int a, b;
    printf("Inserisci due numeri: ");
    scanf("%d %d", &a, &b);
    printf("Il gcd e\' %d", gcd(a, b));
    return 0;
}


int gcd(int a,int b){
    int tmp;
    if(b>a){
        tmp=a;
        a=b;
        b=tmp;
    }

    if(b==0)
        return a;
    if(isEven(a) && isEven(b)){
        return (2*(gcd(a/2,b/2)));
    }
    if(!isEven(a) && isEven(b)){
        return (gcd(a,b/2));
    }
    if(isEven(a) && !isEven(b)){
        return (gcd(a/2,b));
    }
    if(!isEven(a) && !isEven(b)){
        return (gcd((a-b)/2,b));
    }


}

boolean isEven(int entry){
    if(entry%2==0)
        return true;
    else
        return false;
}