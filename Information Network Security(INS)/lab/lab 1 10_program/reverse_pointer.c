#include <stdio.h>
#include <string.h>
void main(){
    char str[100];
    printf("Enter a string:");
    scanf("%s", str); 
    int length=strlen(str);
    char *start = str; 
    char *end = str + length - 1; 
    while (start < end)
    {
        char temp = *start; 
        *start = *end; 
        *end = temp; 
        start++; 
        end--; 
    }
    printf("The reverse of the string is \"%s\".\n", str);
}
