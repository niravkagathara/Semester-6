#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key) {
    int len = strlen(plaintext);
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char shift = toupper(key[j % keyLen]) - 'A'; 
            if (isupper(plaintext[i])) {
                plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else if (islower(plaintext[i])) {
                plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
            j++; 
        }
    }
}

void decrypt(char *ciphertext, char *key) {
    int len = strlen(ciphertext);
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char shift = toupper(key[j % keyLen]) - 'A'; 
            if (isupper(ciphertext[i])) {
                ciphertext[i] = (ciphertext[i] - 'A' - shift + 26) % 26 + 'A';
            } else if (islower(ciphertext[i])) {
                ciphertext[i] = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
            }
            j++; 
        }
    }
}

int main() {
    char plaintext[100], ciphertext[100], key[100];
    int choice;

    printf("Enter the key (any string): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

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

