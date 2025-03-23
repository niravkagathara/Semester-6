#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a simple block cipher (for demonstration purposes)
void simple_block_cipher(const char *input, char *output, const char *key) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key[i % strlen(key)]; // XOR with the key
    }
}

// Function to implement CFB encryption/decryption
void cfb_mode(const char *input, char *output, const char *key, const char *iv, int encrypt) {
    int block_size = strlen(iv); // Block size is the length of the IV
    char *shift_register = (char *)malloc(block_size + 1);
    strncpy(shift_register, iv, block_size);
    shift_register[block_size] = '\0';

    for (int i = 0; i < strlen(input); i++) {
        char keystream_block[block_size + 1];
        simple_block_cipher(shift_register, keystream_block, key);
        keystream_block[block_size] = '\0';

        // XOR input with keystream to produce output
        output[i] = input[i] ^ keystream_block[0];

        // Update the shift register
        if (encrypt) {
            shift_register[block_size - 1] = output[i]; // Add ciphertext in encryption
        } else {
            shift_register[block_size - 1] = input[i]; // Add plaintext in decryption
        }
        memmove(shift_register, shift_register + 1, block_size - 1); // Shift left
    }
    output[strlen(input)] = '\0';

    free(shift_register);
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
    cfb_mode(plaintext, ciphertext, key, iv, 1);
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    cfb_mode(ciphertext, decryptedtext, key, iv, 0);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

