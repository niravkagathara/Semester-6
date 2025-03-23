#include<stdio.h>
int main(){
    int a,i;
    int flag=0;
    printf("Enter a number: ");
    scanf("%d", &a);
    for(i=2; i<=a/2; i++){
        if(a % i == 0){
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("%d is a prime number.\n", a);
    else
        printf("%d is not a prime number.\n", a);
}