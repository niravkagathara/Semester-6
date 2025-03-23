#include <stdio.h>
#include <string.h>

void enc(char *str, int key) {
    int i;
    char str2[30];

    for (i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str2[i] = ((str[i] - 'a' + key) % 26) + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            
            str2[i] = ((str[i] - 'A' + key) % 26) + 'A';
        } else {
            
            str2[i] = str[i];
        }
    }
    str2[i] = '\0';  
    strcpy(str, str2);  
}


int main() {
    char str[30];
    int key;

    printf("Enter String for Encryption: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; 

    printf("Enter Key in integer: ");
    scanf("%d", &key);

    enc(str, key);

    printf("Encrypted String: %s\n", str);

    return 0;
}
