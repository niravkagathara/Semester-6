#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        if (isalpha(ch)) { // Check if the character is a letter
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (ch - base + shift) % 26 + base; // Perform the shift
        }
    }
}

void decrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        if (isalpha(ch)) { // Check if the character is a letter
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (ch - base - shift + 26) % 26 + base; // Perform the reverse shift
        }
    }
}

int main() {
    char text[100];
    int shift;
    char choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the shift amount: ");
    scanf("%d", &shift);

    printf("Choose an operation: (e)ncrypt or (d)ecrypt: ");
    scanf(" %c", &choice);

    if (choice == 'e' || choice == 'E') {
        encrypt(text, shift);
        printf("Encrypted text: %s\n", text);
    } else if (choice == 'd' || choice == 'D') {
        decrypt(text, shift);
        printf("Decrypted text: %s\n", text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

