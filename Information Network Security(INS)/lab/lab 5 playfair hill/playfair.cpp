#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int k = 0;

    for (int i = 0; i < strlen(key); i++) {
        char c = toupper(key[i]);
        if (isalpha(c) && c != 'J' && !used[c - 'A']) {
            matrix[k / SIZE][k % SIZE] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !used[c - 'A']) {
            matrix[k / SIZE][k % SIZE] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }
}

void printMatrix(char matrix[SIZE][SIZE]) {
    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPosition(char letter, char matrix[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void preparePlaintext(char *plaintext, char *preparedText) {
    int len = strlen(plaintext);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char c = toupper(plaintext[i]);
            if (i + 1 < len && toupper(plaintext[i]) == toupper(plaintext[i + 1])) {
                preparedText[j++] = c;
                preparedText[j++] = 'X';
                i++; 
            } else {
                preparedText[j++] = c;
            }
        }
    }
    if (j % 2 != 0) {
        preparedText[j++] = 'X';  
    }
    preparedText[j] = '\0';
}

void encryptPair(char a, char b, char matrix[SIZE][SIZE], char *encryptedPair) {
    int row1, col1, row2, col2;
    findPosition(a, matrix, &row1, &col1);
    findPosition(b, matrix, &row2, &col2);

    if (row1 == row2) {
        encryptedPair[0] = matrix[row1][(col1 + 1) % SIZE];
        encryptedPair[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encryptedPair[0] = matrix[(row1 + 1) % SIZE][col1];
        encryptedPair[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        encryptedPair[0] = matrix[row1][col2];
        encryptedPair[1] = matrix[row2][col1];
    }
}

void encrypt(char *plaintext, char *key, char *ciphertext) {
    char matrix[SIZE][SIZE];
    char preparedText[100];

    generateMatrix(key, matrix);
    printMatrix(matrix);
    preparePlaintext(plaintext, preparedText);

    int j = 0;
    for (int i = 0; i < strlen(preparedText); i += 2) {
        char encryptedPair[3];
        encryptPair(preparedText[i], preparedText[i + 1], matrix, encryptedPair);
        ciphertext[j++] = encryptedPair[0];
        ciphertext[j++] = encryptedPair[1];
    }
    ciphertext[j] = '\0';
}

void decryptPair(char a, char b, char matrix[SIZE][SIZE], char *decryptedPair) {
    int row1, col1, row2, col2;
    findPosition(a, matrix, &row1, &col1);
    findPosition(b, matrix, &row2, &col2);

    if (row1 == row2) {
        decryptedPair[0] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
        decryptedPair[1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
    } else if (col1 == col2) {
        decryptedPair[0] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
        decryptedPair[1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
    } else {
        decryptedPair[0] = matrix[row1][col2];
        decryptedPair[1] = matrix[row2][col1];
    }
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    char matrix[SIZE][SIZE];
    generateMatrix(key, matrix);
    printMatrix(matrix);

    int j = 0;
    for (int i = 0; i < strlen(ciphertext); i += 2) {
        char decryptedPair[3];
        decryptPair(ciphertext[i], ciphertext[i + 1], matrix, decryptedPair);
        plaintext[j++] = decryptedPair[0];
        plaintext[j++] = decryptedPair[1];
    }
    plaintext[j] = '\0';
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
            encrypt(plaintext, key, ciphertext);
            printf("Encrypted text: %s\n", ciphertext);
        }
        else if (choice == 2) {
            printf("Enter ciphertext: ");
            fgets(ciphertext, sizeof(ciphertext), stdin);
            ciphertext[strcspn(ciphertext, "\n")] = '\0';
            decrypt(ciphertext, key, plaintext);
            printf("Decrypted text: %s\n", plaintext);
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

