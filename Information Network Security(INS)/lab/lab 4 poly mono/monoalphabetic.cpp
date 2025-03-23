#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char *inputKey, char *key) {
    int len = strlen(inputKey);
    int used[26] = {0}; 
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(inputKey[i])) {
            char c = toupper(inputKey[i]);
            if (!used[c - 'A']) {
                used[c - 'A'] = 1;
                key[index++] = c;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            key[index++] = 'A' + i;
        }
    }

    key[26] = '\0';
}

void encrypt(char *plaintext, char *substitution) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        if (isupper(plaintext[i])) {
            int index = plaintext[i] - 'A';
            plaintext[i] = substitution[index];
        }
        else if (islower(plaintext[i])) {
            int index = plaintext[i] - 'a';
            plaintext[i] = tolower(substitution[index]);
        }
    }
}

void decrypt(char *ciphertext, char *substitution) {
    int len = strlen(ciphertext);
    char reverseSubstitution[26];

    for (int i = 0; i < 26; i++) {
        reverseSubstitution[substitution[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; i < len; i++) {
        if (isupper(ciphertext[i])) {
            int index = ciphertext[i] - 'A';
            ciphertext[i] = reverseSubstitution[index];
        }
        else if (islower(ciphertext[i])) {
            int index = ciphertext[i] - 'a';
            ciphertext[i] = tolower(reverseSubstitution[index]);
        }
    }
}

int main() {
    char plaintext[100], ciphertext[100], inputKey[100], key[27];
    int choice;

    printf("Enter substitution key (any string): ");
    fgets(inputKey, sizeof(inputKey), stdin);
    
    inputKey[strcspn(inputKey, "\n")] = '\0';

    generateKey(inputKey, key);
    printf("Generated substitution key: %s\n", key);

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            printf("Enter plaintext: ");
            fgets(plaintext, sizeof(plaintext), stdin);
            plaintext[strcspn(plaintext, "\n")] = '\0';  
            strcpy(ciphertext, plaintext);
            encrypt(ciphertext, key);
            printf("Encrypted text: %s\n", ciphertext);
        }
        else if (choice == 2) {
            printf("Enter ciphertext: ");
            fgets(ciphertext, sizeof(ciphertext), stdin);
            ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
            decrypt(ciphertext, key);
            printf("Decrypted text: %s\n", ciphertext);
        }
        else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

