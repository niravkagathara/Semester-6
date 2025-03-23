#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes

// Function to XOR a block of plaintext/ciphertext with a key
void xorBlock(unsigned char *block, const unsigned char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

// Encryption function
void encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE); // Copy plaintext block
        xorBlock(ciphertext + i, key); // XOR with key
    }
}

// Decryption function
void decrypt(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE); // Copy ciphertext block
        xorBlock(plaintext + i, key); // XOR with key
    }
}

int main() {
    unsigned char key[BLOCK_SIZE + 1]; // Add 1 for null terminator
    unsigned char plaintext[64];
    unsigned char ciphertext[64] = {0};
    unsigned char decrypted[64] = {0};
    int length;

    // Get plaintext from the user
    printf("Enter plaintext (max 64 characters): ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn((char *)plaintext, "\n")] = '\0'; // Remove newline character

    // Get key from the user
    printf("Enter key (exactly 8 characters): ");
    fgets((char *)key, sizeof(key), stdin);
    key[strcspn((char *)key, "\n")] = '\0'; // Remove newline character

    // Check key length
    if (strlen((char *)key) != BLOCK_SIZE) {
        printf("Error: Key must be exactly 8 characters long.\n");
        return 1;
    }

    // Determine plaintext length and pad if necessary
    length = strlen((char *)plaintext);
    if (length % BLOCK_SIZE != 0) {
        int pad = BLOCK_SIZE - (length % BLOCK_SIZE);
        memset(plaintext + length, ' ', pad); // Pad with spaces
        length += pad;
    }

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext, length);

    // Display ciphertext
    printf("Ciphertext (hex): ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decrypted, length);

    // Display decrypted text
    printf("Decrypted text: '%s'\n", decrypted);

    return 0;
}
//Enter plaintext (max 64 characters): HelloWorld
//Enter key (exactly 8 characters): mysecret
//Ciphertext (hex): 3D 05 04 0C 02 16 0F 01 03 02 20 20 20 20 20 20 
//Decrypted text: 'HelloWorld 





//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// Function to perform XOR operation between two blocks
//void xor_operation(const char *block1, const char *block2, char *result, int block_size) {
//    for (int i = 0; i < block_size; i++) {
//        result[i] = block1[i] ^ block2[i]; // XOR operation between blocks
//    }
//}
//
//// Simple XOR Block Cipher - Encryption
//void xor_block_cipher_encrypt(const char *input, char *output, const char *key, int block_size) {
//    xor_operation(input, key, output, block_size); // XOR the block with the key
//}
//
//// Simple XOR Block Cipher - Decryption
//void xor_block_cipher_decrypt(const char *input, char *output, const char *key, int block_size) {
//    xor_operation(input, key, output, block_size); // XOR the block with the key (same as encryption)
//}
//
//// ECB Mode Encryption
//void ecb_encrypt(const char *plaintext, char *ciphertext, const char *key, int block_size) {
//    int input_length = strlen(plaintext);
//    
//    // Process plaintext in blocks
//    for (int i = 0; i < input_length; i += block_size) {
//        char current_block[block_size + 1];
//        strncpy(current_block, plaintext + i, block_size);
//        current_block[block_size] = '\0';
//
//        xor_block_cipher_encrypt(current_block, ciphertext + i, key, block_size);
//    }
//    ciphertext[input_length] = '\0';
//}
//
//// ECB Mode Decryption
//void ecb_decrypt(const char *ciphertext, char *plaintext, const char *key, int block_size) {
//    int input_length = strlen(ciphertext);
//
//    // Process ciphertext in blocks
//    for (int i = 0; i < input_length; i += block_size) {
//        char current_block[block_size + 1];
//        strncpy(current_block, ciphertext + i, block_size);
//        current_block[block_size] = '\0';
//
//        xor_block_cipher_decrypt(current_block, plaintext + i, key, block_size);
//    }
//    plaintext[input_length] = '\0';
//}
//
//int main() {
//    char plaintext[256], key[256];
//
//    // Get user input for plaintext and key
//    printf("Enter plaintext: ");
//    gets(plaintext); // Read plaintext input
//
//    printf("Enter key: ");
//    gets(key); // Read key input
//
//    // Set block size to the length of the key (for this example)
//    int block_size = strlen(key);
//
//    // Ensure the plaintext length is a multiple of the block size
//    if (strlen(plaintext) % block_size != 0) {
//        printf("Plaintext length must be a multiple of the block size (key length). Exiting...\n");
//        return 1;
//    }
//
//    char ciphertext[256];
//    char decryptedtext[256];
//
//    // Encrypt the plaintext
//    ecb_encrypt(plaintext, ciphertext, key, block_size);
//    printf("Ciphertext: ");
//    for (int i = 0; i < strlen(plaintext); i++) {
//        printf("%02X ", (unsigned char)ciphertext[i]); // Display ciphertext in hex
//    }
//    printf("\n");
//
//    // Decrypt the ciphertext
//    ecb_decrypt(ciphertext, decryptedtext, key, block_size);
//    printf("Decrypted text: %s\n", decryptedtext); // Display the decrypted text
//
//    return 0;
//}
     

