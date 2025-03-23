#include <stdio.h>
#include <string.h>

void andEncrypt(const char text[], char output[], char key) {
    for (int i = 0; i < strlen(text); i++) {
        output[i] = text[i] & key; 
    }
    output[strlen(text)] = '\0';
}

void printBinary(const char text[]) {
    for (int i = 0; i < strlen(text); i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (text[i] >> j) & 1); 
        }
        printf(" "); 
    }
    printf("\n");
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    char key;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter key (single character): ");
    scanf(" %c", &key);

    andEncrypt(text, encrypted, key);

    printf("Encrypted text (as binary): ");
    printBinary(encrypted); 


    return 0;
}

