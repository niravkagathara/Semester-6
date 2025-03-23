#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int matrixSize = 2;

// Function to convert the key into a 2x2 matrix
void getKeyMatrix(char key[], int keyMatrix[2][2]) {
    int k = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            keyMatrix[i][j] = key[k] - 'A'; // Convert letter to integer (A=0, B=1, ..., Z=25)
            k++;
        }
    }
}

// Function to perform encryption using the Hill Cipher
void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int keyMatrix[2][2];
    getKeyMatrix(key, keyMatrix); // Convert key into a 2x2 matrix

    int plaintextVector[2];
    int resultVector[2];

    // Process the plaintext in blocks of 2 characters
    int i;
    for (i = 0; i < strlen(plaintext); i += 2) {
        // If the remaining plaintext is 1 character, add padding
        if (i + 1 >= strlen(plaintext)) {
            plaintext[i + 1] = 'X'; // Padding character 'X'
        }

        // Prepare the plaintext vector
        for (int j = 0; j < 2; j++) {
            plaintextVector[j] = plaintext[i + j] - 'A'; // Convert characters to numbers (A=0, B=1, ..., Z=25)
        }

        // Multiply the key matrix by the plaintext vector
        for (int j = 0; j < 2; j++) {
            resultVector[j] = 0;
            for (int k = 0; k < 2; k++) {
                resultVector[j] += keyMatrix[j][k] * plaintextVector[k];
            }
            resultVector[j] %= 26; // Modulo 26 to ensure it's in the range 0-25
        }

        // Convert the result back into characters and store it in the ciphertext
        for (int j = 0; j < 2; j++) {
            ciphertext[i + j] = resultVector[j] + 'A'; // Convert numbers back to characters (0=A, 1=B, ..., 25=Z)
        }
    }

    ciphertext[i] = '\0'; // Null-terminate the string
}

// Function to find the inverse of the key matrix
void findInverseKeyMatrix(int keyMatrix[2][2], int inverseKeyMatrix[2][2]) {
    int determinant = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;
    if (determinant < 0) determinant += 26;

    // Find modular inverse of the determinant modulo 26
    int inverseDeterminant = -1;
    for (int i = 0; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            inverseDeterminant = i;
            break;
        }
    }

    if (inverseDeterminant == -1) {
        printf("Key matrix is not invertible.\n");
        exit(1);
    }

    // Calculate the inverse matrix
    inverseKeyMatrix[0][0] = (keyMatrix[1][1] * inverseDeterminant) % 26;
    inverseKeyMatrix[0][1] = (-keyMatrix[0][1] * inverseDeterminant) % 26;
    inverseKeyMatrix[1][0] = (-keyMatrix[1][0] * inverseDeterminant) % 26;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0] * inverseDeterminant) % 26;

    // Ensure values are positive
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverseKeyMatrix[i][j] < 0) {
                inverseKeyMatrix[i][j] += 26;
            }
        }
    }
}

// Function to decrypt ciphertext using the Hill Cipher
void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int keyMatrix[2][2], inverseKeyMatrix[2][2];
    getKeyMatrix(key, keyMatrix);
    findInverseKeyMatrix(keyMatrix, inverseKeyMatrix);

    int ciphertextVector[2];
    int resultVector[2];

    // Process the ciphertext in blocks of 2 characters
    for (int i = 0; i < strlen(ciphertext); i += 2) {
        // Prepare the ciphertext vector
        for (int j = 0; j < 2; j++) {
            ciphertextVector[j] = ciphertext[i + j] - 'A';
        }

        // Multiply with the inverse key matrix
        for (int j = 0; j < 2; j++) {
            resultVector[j] = 0;
            for (int k = 0; k < 2; k++) {
                resultVector[j] += inverseKeyMatrix[j][k] * ciphertextVector[k];
            }
            resultVector[j] %= 26;
        }

        // Convert result vector to characters and store in plaintext
        for (int j = 0; j < 2; j++) {
            plaintext[i + j] = resultVector[j] + 'A';
        }
    }

    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[MAX], ciphertext[MAX], key[5];
    int choice;

    while (1) {
        printf("\n--- Hill Cipher ---\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter plaintext (in uppercase, multiple of 2 length): ");
                scanf("%s", plaintext);
                printf("Enter 4-character key (in uppercase): ");
                scanf("%s", key);
                encrypt(plaintext, key, ciphertext);
                printf("Ciphertext: %s\n", ciphertext);
                break;

            case 2:
                printf("Enter ciphertext (in uppercase, multiple of 2 length): ");
                scanf("%s", ciphertext);
                printf("Enter 4-character key (in uppercase): ");
                scanf("%s", key);
                decrypt(ciphertext, key, plaintext);
                printf("Plaintext: %s\n", plaintext);
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

