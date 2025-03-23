#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

int determinant(int matrix[SIZE][SIZE]) {
    return (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
            matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
            matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]));
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void hillCipher(int key[SIZE][SIZE], char* input) {
    int matrix[SIZE][SIZE];
    int result[SIZE];
    int length = strlen(input);
    char output[length + 1];

    for (int i = 0; i < length; i += SIZE) {
        for (int j = 0; j < SIZE; j++) {
            if (i + j < length) {
                matrix[j][0] = input[i + j] - 'A';
            } else {
                matrix[j][0] = 'X' - 'A';
            }
        }

        for (int j = 0; j < SIZE; j++) {
            result[j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[j] += key[j][k] * matrix[k][0];
            }
            output[i / SIZE * SIZE + j] = (result[j] % 26) + 'A';
        }
    }
    output[length] = '\0';
    printf("Encrypted Output: %s\n", output);
}

int main() {
    int key[SIZE][SIZE];
    char input[100];
    
    printf("Enter the text (uppercase A-Z): ");
    scanf("%s", input);
    
    printf("Enter the 3x3 key matrix (9 integers): ");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }

   

    hillCipher(key, input);

    return 0;
}