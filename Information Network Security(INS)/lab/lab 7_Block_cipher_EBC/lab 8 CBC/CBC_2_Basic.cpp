#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a simple block cipher (for demonstration purposes)
void simple_block_cipher(const char *input, char *output, const char *key) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key[i % strlen(key)]; // XOR with the key
    }
}

// XOR two blocks of data
void xor_blocks(char *result, const char *block1, const char *block2, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// CBC mode for encryption and decryption
void cbc_mode(const char *input, char *output, const char *key, const char *iv, int encrypt) {
    int block_size = strlen(iv);
    int input_length = strlen(input);
    char *prev_block = (char *)malloc(block_size + 1);
    strncpy(prev_block, iv, block_size);
    prev_block[block_size] = '\0';

    for (int i = 0; i < input_length; i += block_size) {
        char current_block[block_size + 1];
        strncpy(current_block, input + i, block_size);
        current_block[block_size] = '\0';

        char temp_block[block_size + 1];
        if (encrypt) {
            // Encrypt: XOR plaintext with the previous ciphertext block (or IV)
            xor_blocks(temp_block, current_block, prev_block, block_size);
            simple_block_cipher(temp_block, output + i, key);
            strncpy(prev_block, output + i, block_size); // Update previous block
        } else {
            // Decrypt: Decrypt ciphertext, then XOR with the previous ciphertext block (or IV)
            simple_block_cipher(current_block, temp_block, key);
            xor_blocks(output + i, temp_block, prev_block, block_size);
            strncpy(prev_block, current_block, block_size); // Update previous block
        }
    }
    output[input_length] = '\0';
    free(prev_block);
}

int main() {
    char plaintext[256], key[256], iv[256];

    printf("Enter plaintext: ");
    gets(plaintext); // Read plaintext input

    printf("Enter key: ");
    gets(key); // Read key input

    printf("Enter initialization vector (IV): ");
    gets(iv); // Read IV input

    // Ensure IV length matches block size (for demonstration purposes)
    if (strlen(iv) != strlen(key)) {
        printf("IV length must match the key length. Exiting...\n");
        return 1;
    }

    char ciphertext[256];
    char decryptedtext[256];

    // Encrypt the plaintext
    cbc_mode(plaintext, ciphertext, key, iv, 1);
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    cbc_mode(ciphertext, decryptedtext, key, iv, 0);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

