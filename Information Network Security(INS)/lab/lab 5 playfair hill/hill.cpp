#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define SIZEE 3
int matrixSize = 2;

// Function to convert the key into a 2x2 matrix
void getKeyMatrix(char key[], int keyMatrix[2][2])
{
    int k = 0;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            keyMatrix[i][j] = key[k] - 'A'; // Convert letter to integer (A=0, B=1, ..., Z=25)
            k++;
        }
    }
}

// Function to perform encryption using the Hill Cipher
void encrypt(char plaintext[], char key[], char ciphertext[])
{
    int keyMatrix[2][2];
    getKeyMatrix(key, keyMatrix); // Convert key into a 2x2 matrix

    int plaintextVector[2];
    int resultVector[2];

    // Process the plaintext in blocks of 2 characters
    int i;
    for (i = 0; i < strlen(plaintext); i += 2)
    {
        // If the remaining plaintext is 1 character, add padding
        if (i + 1 >= strlen(plaintext))
        {
            plaintext[i + 1] = 'X'; // Padding character 'X'
        }

        // Prepare the plaintext vector
        for (int j = 0; j < 2; j++)
        {
            plaintextVector[j] = plaintext[i + j] - 'A'; // Convert characters to numbers (A=0, B=1, ..., Z=25)
        }

        // Multiply the key matrix by the plaintext vector
        for (int j = 0; j < 2; j++)
        {
            resultVector[j] = 0;
            for (int k = 0; k < 2; k++)
            {
                resultVector[j] += keyMatrix[j][k] * plaintextVector[k];
            }
            resultVector[j] %= 26; // Modulo 26 to ensure it's in the range 0-25
        }

        // Convert the result back into characters and store it in the ciphertext
        for (int j = 0; j < 2; j++)
        {
            ciphertext[i + j] = resultVector[j] + 'A'; // Convert numbers back to characters (0=A, 1=B, ..., 25=Z)
        }
    }

    ciphertext[i] = '\0'; // Null-terminate the string
}

// Function to find the inverse of the key matrix
void findInverseKeyMatrix(int keyMatrix[2][2], int inverseKeyMatrix[2][2])
{
    int determinant = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;
    if (determinant < 0)
        determinant += 26;

    // Find modular inverse of the determinant modulo 26
    int inverseDeterminant = -1;
    for (int i = 0; i < 26; i++)
    {
        if ((determinant * i) % 26 == 1)
        {
            inverseDeterminant = i;
            break;
        }
    }

    if (inverseDeterminant == -1)
    {
        printf("Key matrix is not invertible.\n");
        exit(1);
    }

    // Calculate the inverse matrix
    inverseKeyMatrix[0][0] = (keyMatrix[1][1] * inverseDeterminant) % 26;
    inverseKeyMatrix[0][1] = (-keyMatrix[0][1] * inverseDeterminant) % 26;
    inverseKeyMatrix[1][0] = (-keyMatrix[1][0] * inverseDeterminant) % 26;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0] * inverseDeterminant) % 26;

    // Ensure values are positive
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (inverseKeyMatrix[i][j] < 0)
            {
                inverseKeyMatrix[i][j] += 26;
            }
        }
    }
}

// Function to decrypt ciphertext using the Hill Cipher
void decrypt(char ciphertext[], char key[], char plaintext[])
{
    int keyMatrix[2][2], inverseKeyMatrix[2][2];
    getKeyMatrix(key, keyMatrix);
    findInverseKeyMatrix(keyMatrix, inverseKeyMatrix);

    int ciphertextVector[2];
    int resultVector[2];

    // Process the ciphertext in blocks of 2 characters
    for (int i = 0; i < strlen(ciphertext); i += 2)
    {
        // Prepare the ciphertext vector
        for (int j = 0; j < 2; j++)
        {
            ciphertextVector[j] = ciphertext[i + j] - 'A';
        }

        // Multiply with the inverse key matrix
        for (int j = 0; j < 2; j++)
        {
            resultVector[j] = 0;
            for (int k = 0; k < 2; k++)
            {
                resultVector[j] += inverseKeyMatrix[j][k] * ciphertextVector[k];
            }
            resultVector[j] %= 26;
        }

        // Convert result vector to characters and store in plaintext
        for (int j = 0; j < 2; j++)
        {
            plaintext[i + j] = resultVector[j] + 'A';
        }
    }

    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the string
}

// 3x3 encryption

int determinant(int matrixaa[SIZEE][SIZEE])
{
    return (matrixaa[0][0] * (matrixaa[1][1] * matrixaa[2][2] - matrixaa[1][2] * matrixaa[2][1]) -
            matrixaa[0][1] * (matrixaa[1][0] * matrixaa[2][2] - matrixaa[1][2] * matrixaa[2][0]) +
            matrixaa[0][2] * (matrixaa[1][0] * matrixaa[2][1] - matrixaa[1][1] * matrixaa[2][0]));
}

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

void hillCipher(int key[SIZEE][SIZEE], char *input)
{
    int matrixaa[SIZEE][SIZEE];
    int resultaa[SIZEE];
    int length = strlen(input);
    char output[length + 1];

    for (int i = 0; i < length; i += SIZEE)
    {
        for (int j = 0; j < SIZEE; j++)
        {
            if (i + j < length)
            {
                matrixaa[j][0] = input[i + j] - 'A';
            }
            else
            {
                matrixaa[j][0] = 'X' - 'A';
            }
        }

        for (int j = 0; j < SIZEE; j++)
        {
            resultaa[j] = 0;
            for (int k = 0; k < SIZEE; k++)
            {
                resultaa[j] += key[j][k] * matrixaa[k][0];
            }
            output[i / SIZEE * SIZEE + j] = (resultaa[j] % 26) + 'A';
        }
    }
    output[length] = '\0';
    printf("Encrypted Output: %s\n", output);
}
void initializeKeyMatrix(int ekey[SIZEE][SIZEE], char input[100]) {
    int count = 0;
    for (int i = 0; i < SIZEE; i++) {
        for (int j = 0; j < SIZEE; j++) {
            if (count < strlen(input) && input[count] >= 'a' && input[count] <= 'z') {
                ekey[i][j] = input[count] - 'a'; // Convert character to corresponding number
            } else {
                ekey[i][j] = 23; // Default value if input is invalid
            }
            count++;
        }
    }
     for (int i = 0; i < SIZEE; i++) {
        for (int j = 0; j < SIZEE; j++) {
            if (ekey[i][j] == 0 && (i != 0 || j != 0)) {
                ekey[i][j] = 23;
            }
        }
    }
    printf("The 3x3 key matrix is:\n");
    for (int i = 0; i < SIZEE; i++) {
        for (int j = 0; j < SIZEE; j++) {
            printf("%d ", ekey[i][j]);
        }
        printf("\n");
    }
}


//3x3 decryption

int determinanta(int matrix[3][3]) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
         - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
         + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

// Function to find the modular inverse of a number modulo 26
int mod_inversea(int num, int mod) {
    num = num % mod;
    for (int x = 1; x < mod; x++) {
        if ((num * x) % mod == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

// Function to compute the adjugate of a 3x3 matrix
void adjugate_matrix(int matrix[3][3], int adj[3][3]) {
    adj[0][0] =  matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adj[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    adj[0][2] =  matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];

    adj[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    adj[1][1] =  matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adj[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);

    adj[2][0] =  matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    adj[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
    adj[2][2] =  matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to compute the inverse of a 3x3 matrix modulo 26
void inverse_matrix(int matrix[3][3], int inverse[3][3], int mod) {
    int det = determinanta(matrix);
    det = det % mod;
    if (det < 0) det += mod;

    int det_inv = mod_inversea(det, mod);
    if (det_inv == -1) {
        printf("Key matrix is not invertible modulo %d.\n", mod);
        exit(1);
    }

    int adj[3][3];
    adjugate_matrix(matrix, adj);

    // Compute the inverse matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = (adj[i][j] * det_inv) % mod;
            if (inverse[i][j] < 0) inverse[i][j] += mod;
        }
    }
}

// Function to decrypt the ciphertext
void decryptaaa(char* ciphertext, int key[3][3]) {
    int key_inverse[3][3];
    int mod = 26;
    int len = strlen(ciphertext);

    // Ensure ciphertext length is a multiple of 3 by padding with 'X' (23) if needed
    while (len % 3 != 0) {
        strcat(ciphertext, "X");
        len++;
    }

    // Calculate the inverse of the key matrix
    inverse_matrix(key, key_inverse, mod);

    // Decrypt the ciphertext in blocks of size 3
    printf("Decrypted text: ");
    for (int i = 0; i < len; i += 3) {
        int c[3] = {ciphertext[i] - 'A', ciphertext[i + 1] - 'A', ciphertext[i + 2] - 'A'};
        int p[3] = {0};

        // Perform matrix multiplication with the inverse key
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                p[row] += key_inverse[row][col] * c[col];
            }
            p[row] = p[row] % mod;
            if (p[row] < 0) p[row] += mod;
        }

        // Convert numeric values back to characters
        printf("%c%c%c", p[0] + 'A', p[1] + 'A', p[2] + 'A');
    }
    printf("\n");
} 

int main()
{
    int keySize;
    char plaintext[MAX], ciphertext[MAX], key[5];
    int choice;
    int ekey[SIZEE][SIZEE];
    char enc_pt[100];
    char cipher_text[100];
    int key_matrix[SIZEE][SIZEE];
    char k[100],w[100];

    while (1)
    {
        printf("\n--- Hill Cipher ---\n");

        printf("Choose key size:\n");
        printf("2: 2x2 key matrix\n");
        printf("3: 3x3 key matrix\n");
        printf("1: exit\n");

        scanf("%d", &keySize);

        if (keySize == 2)
        {
            printf("2x2\n1. Encrypt\n");
            printf("2. Decrypt\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
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
        else if (keySize == 3)
        {
            printf("3x3 \n1. Encrypt\n");
            printf("2. Decrypt\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter the  Plaintext:( A-Z): ");
                scanf("%s", enc_pt);
                printf("Enter the 3x3 key matrix (9 characters a-z in): ");
                scanf("%s", k);
                initializeKeyMatrix(ekey, k);
                hillCipher(ekey, enc_pt);
                break;

            case 2:
                printf("Enter the cipher text:( A-Z): ");
                scanf("%s", cipher_text);
                printf("Enter the 3x3 key matrix (9  characters a-z in): ");
                scanf("%s", w);
                initializeKeyMatrix(key_matrix, w);
                printf("Decrypted Text: ");
                decryptaaa(cipher_text, key_matrix);
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
            }
        }
        else if (keySize == 1)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
