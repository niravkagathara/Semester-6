#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a simple block cipher (for demonstration purposes)
void simple_block_cipher(const char *input, char *output, const char *key) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key[i % strlen(key)]; // XOR with the key
    }
}

// ECB mode for encryption and decryption
void ecb_mode(const char *input, char *output, const char *key, int block_size) {
    int input_length = strlen(input);

    for (int i = 0; i < input_length; i += block_size) {
        char current_block[block_size + 1];
        strncpy(current_block, input + i, block_size);
        current_block[block_size] = '\0';

        simple_block_cipher(current_block, output + i, key);
    }
    output[input_length] = '\0';
}

int main() {
    char plaintext[256], key[256];

    printf("Enter plaintext: ");
    gets(plaintext); // Read plaintext input

    printf("Enter key: ");
    gets(key); // Read key input

    // Determine the block size
    int block_size = strlen(key);

    // Ensure the plaintext length is a multiple of the block size
    if (strlen(plaintext) % block_size != 0) {
        printf("Plaintext length must be a multiple of the block size (key length). Exiting...\n");
        return 1;
    }

    char ciphertext[256];
    char decryptedtext[256];

    // Encrypt the plaintext
    ecb_mode(plaintext, ciphertext, key, block_size);
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    ecb_mode(ciphertext, decryptedtext, key, block_size);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

//this below code is both enc and dec both algo implic
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// Function to perform XOR operation between two blocks
//void xor_operation(const char *block1, const char *block2, char *result, int block_size) {
//    for (int i = 0; i < block_size; i++) {
//        result[i] = block1[i] ^ block2[i];
//    }
//}
//
//// Simulated block cipher encryption
//void block_cipher_encrypt(const char *input, char *output, const char *key, int block_size) {
//    xor_operation(input, key, output, block_size); // XOR the block with the key for encryption
//}
//
//// Simulated block cipher decryption
//void block_cipher_decrypt(const char *input, char *output, const char *key, int block_size) {
//    xor_operation(input, key, output, block_size); // XOR the block with the key for decryption
//}
//
//// ECB mode encryption
//void ecb_encrypt(const char *plaintext, char *ciphertext, const char *key, int block_size) {
//    int input_length = strlen(plaintext);
//
//    for (int i = 0; i < input_length; i += block_size) {
//        char current_block[block_size + 1];
//        strncpy(current_block, plaintext + i, block_size);
//        current_block[block_size] = '\0';
//
//        block_cipher_encrypt(current_block, ciphertext + i, key, block_size);
//    }
//    ciphertext[input_length] = '\0';
//}
//
//// ECB mode decryption
//void ecb_decrypt(const char *ciphertext, char *plaintext, const char *key, int block_size) {
//    int input_length = strlen(ciphertext);
//
//    for (int i = 0; i < input_length; i += block_size) {
//        char current_block[block_size + 1];
//        strncpy(current_block, ciphertext + i, block_size);
//        current_block[block_size] = '\0';
//
//        block_cipher_decrypt(current_block, plaintext + i, key, block_size);
//    }
//    plaintext[input_length] = '\0';
//}
//
//int main() {
//    char plaintext[256], key[256];
//
//    printf("Enter plaintext: ");
//    gets(plaintext); // Read plaintext input
//
//    printf("Enter key: ");
//    gets(key); // Read key input
//
//    // Determine the block size
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
//        printf("%02X ", (unsigned char)ciphertext[i]);
//    }
//    printf("\n");
//
//    // Decrypt the ciphertext
//    ecb_decrypt(ciphertext, decryptedtext, key, block_size);
//    printf("Decrypted text: %s\n", decryptedtext);
//
//    return 0;
//}

