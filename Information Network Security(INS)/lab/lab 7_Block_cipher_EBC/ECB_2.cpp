#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Define the size of each block

// Function to perform XOR-based encryption/decryption of a block
void xor_block(char *block, const char *key, int size) {
    for (int i = 0; i < size; i++) {
        block[i] ^= key[i];
    }
}

// Function to pad plaintext if its length is not a multiple of BLOCK_SIZE
int pad_plaintext(char *plaintext, int length) {
    int padding = BLOCK_SIZE - (length % BLOCK_SIZE);
    for (int i = 0; i < padding; i++) {
        plaintext[length + i] = padding; // Use PKCS#7 padding
    }
    return length + padding;
}

// ECB Encryption
void ecb_encrypt(char *plaintext, char *ciphertext, const char *key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE); // Copy block
        xor_block(ciphertext + i, key, BLOCK_SIZE); // Encrypt block
    }
}

// ECB Decryption
void ecb_decrypt(char *ciphertext, char *decrypted_text, const char *key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(decrypted_text + i, ciphertext + i, BLOCK_SIZE); // Copy block
        xor_block(decrypted_text + i, key, BLOCK_SIZE); // Decrypt block
    }
}

// Remove padding after decryption
int remove_padding(char *text, int length) {
    int padding = text[length - 1];
    return length - padding;
}

int main() {
    char plaintext[128], key[BLOCK_SIZE], ciphertext[128], decrypted_text[128];
    int length, padded_length;

    // User input for plaintext
    printf("Enter plaintext (max 120 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
        length--;
    }

    // User input for key
    printf("Enter key (8 characters): ");
    fgets(key, sizeof(key), stdin);
    if (key[strlen(key) - 1] == '\n') {
        key[strlen(key) - 1] = '\0';
    }

    // Padding plaintext
    padded_length = pad_plaintext(plaintext, length);

    // Encryption
    ecb_encrypt(plaintext, ciphertext, key, padded_length);

    // Display ciphertext
    printf("Ciphertext (in hex): ");
    for (int i = 0; i < padded_length; i++) {
        printf("%02x ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decryption
    ecb_decrypt(ciphertext, decrypted_text, key, padded_length);

    // Remove padding
    int decrypted_length = remove_padding(decrypted_text, padded_length);
    decrypted_text[decrypted_length] = '\0';

    // Display decrypted text
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

