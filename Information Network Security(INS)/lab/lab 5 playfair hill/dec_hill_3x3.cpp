#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 3 // For a 3x3 matrix

// Function to find the determinant of a 3x3 matrix
int determinant(int matrix[SIZE][SIZE]) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

// Function to find the modular inverse of a number mod 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No inverse exists
}

// Function to calculate the adjugate matrix
void adjugate(int matrix[SIZE][SIZE], int adj[SIZE][SIZE]) {
    adj[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adj[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    adj[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    
    adj[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    adj[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adj[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    
    adj[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    adj[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
    adj[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to find the inverse matrix modulo 26
int inverse_matrix(int matrix[SIZE][SIZE], int inv[SIZE][SIZE]) {
    int det = determinant(matrix);
    int det_inv = mod_inverse(det, 26);
    
    if (det_inv == -1) {
        printf("Inverse does not exist!\n");
        return 0;
    }
    
    int adj[SIZE][SIZE];
    adjugate(matrix, adj);

    // Multiply adjugate matrix with determinant inverse mod 26
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv[i][j] = (adj[i][j] * det_inv) % 26;
            if (inv[i][j] < 0) {
                inv[i][j] += 26; // Ensure positive values
            }
        }
    }

    return 1;
}

// Function to decrypt the ciphertext
void hill_decrypt(char *cipher_text, int key_matrix[SIZE][SIZE]) {
    int inv_key_matrix[SIZE][SIZE];
    if (!inverse_matrix(key_matrix, inv_key_matrix)) {
        return;
    }
    
    int len = strlen(cipher_text);
    int cipher_vals[len];
    
    // Convert cipher text to numeric values
    for (int i = 0; i < len; i++) {
        cipher_vals[i] = toupper(cipher_text[i]) - 'A';
    }

    // Decrypt the ciphertext
    for (int i = 0; i < len; i += SIZE) {
        int result[SIZE] = {0};
        
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                result[row] += inv_key_matrix[row][col] * cipher_vals[i + col];
            }
            result[row] = result[row] % 26;
            printf("%c", result[row] + 'A');
        }
    }
    printf("\n");
}

int main() {
    char cipher_text[100];
    int key_matrix[SIZE][SIZE];
    
    // Input ciphertext
    printf("Enter the cipher text: ");
    fgets(cipher_text, sizeof(cipher_text), stdin);
    cipher_text[strcspn(cipher_text, "\n")] = '\0'; // Remove newline

    // Input 3x3 key matrix
    printf("Enter the 3x3 key matrix (9 integers): ");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &key_matrix[i][j]);
        }
    }

    printf("Decrypted Text: ");
    hill_decrypt(cipher_text, key_matrix);

    return 0;
}
