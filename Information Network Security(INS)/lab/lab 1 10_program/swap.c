#include <stdio.h>
void swapa(int a,int b){

    int c;
    c = a;
    a = b;
    b = c;
    printf("Swapped values: a = %d, b = %d\n", a, b);
}
void main(){
    int a,b;
     printf("enter first number");
     scanf("%d",&a);
     
     printf("enter second number");
     scanf("%d",&b);

     swapa(a,b);
}
