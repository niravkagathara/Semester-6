#include<stdio.h>
#include <string.h>

void main(){
    char str[100];
    printf("Enter a string:");
	scanf("%s", str); 

    // char temp[100];
    int length=strlen(str);
    int s=0,e;
    e=length-1;

    while (s<e)
    {
       char temp=str[s];
        str[s]=str[e];
        str[e]=temp;
        s++;
        e--;
    }
    printf("The reverse of the string is \"%s\".\n", str);
}