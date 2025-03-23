#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a simple block cipher (for demonstration purposes)
void simple_block_cipher(const char *input, char *output, const char *key) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key[i % strlen(key)]; // XOR with the key
    }
}

// Function to implement OFB encryption/decryption
void ofb_mode(const char *input, char *output, const char *key, const char *iv) {
    int block_size = strlen(iv); // Block size is the length of the IV
    char *keystream_block = (char *)malloc(block_size + 1);
    strncpy(keystream_block, iv, block_size);
    keystream_block[block_size] = '\0';

    for (int i = 0; i < strlen(input); i++) {
        if (i % block_size == 0) { 
            // Generate a new keystream block
            char next_iv[block_size + 1];
            simple_block_cipher(keystream_block, next_iv, key);
            strncpy(keystream_block, next_iv, block_size);
            keystream_block[block_size] = '\0';
        }

        // XOR the input with the keystream to produce output
        output[i] = input[i] ^ keystream_block[i % block_size];
    }
    output[strlen(input)] = '\0';

    free(keystream_block);
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
    if (strlen(iv) < strlen(key)) {
        printf("IV should be at least as long as the key. Exiting...\n");
        return 1;
    }

    char ciphertext[256];
    char decryptedtext[256];

    // Encrypt the plaintext
    ofb_mode(plaintext, ciphertext, key, iv);
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    ofb_mode(ciphertext, decryptedtext, key, iv);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

