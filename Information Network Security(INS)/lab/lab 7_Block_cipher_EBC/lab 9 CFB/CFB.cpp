//first
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8  // 8 bytes per block for simplicity

// Function to XOR two byte arrays (used for encryption and feedback)
void xor_block(unsigned char *block, unsigned char *feedback, int size) {
    for (int i = 0; i < size; i++) {
        block[i] ^= feedback[i];
    }
}

// Simple XOR encryption function (for demonstration purposes)
void xor_encrypt_decrypt(unsigned char *data, unsigned char *key, int size) {
    for (int i = 0; i < size; i++) {
        data[i] ^= key[i];
    }
}

// CFB encryption function
void cfb_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv, int length) {
    unsigned char feedback[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    
    // Initialize feedback with the IV
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i++) {
        // XOR the feedback with the key to create the encryption stream
        xor_encrypt_decrypt(feedback, key, BLOCK_SIZE);

        // Encrypt the current block
        temp[0] = input[i];
        xor_block(temp, feedback, 1);

        // Store the ciphertext (encrypted data)
        output[i] = temp[0];

        // Update the feedback (shift the previous ciphertext into feedback)
        memcpy(feedback, &output[i], 1);
    }
}

// CFB decryption function
void cfb_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv, int length) {
    unsigned char feedback[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    
    // Initialize feedback with the IV
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i++) {
        // XOR the feedback with the key to create the decryption stream
        xor_encrypt_decrypt(feedback, key, BLOCK_SIZE);

        // Decrypt the current block
        temp[0] = input[i];
        xor_block(temp, feedback, 1);

        // Store the plaintext (decrypted data)
        output[i] = temp[0];

        // Update the feedback (shift the previous ciphertext into feedback)
        memcpy(feedback, &input[i], 1);
    }
}

// Function to trim the newline and spaces from the input string
void trim_input(char *input) {
    int len = strlen(input);
    if (len == 0) return;

    // Trim trailing spaces and newline characters
    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == ' ')) {
        input[len - 1] = '\0';
        len--;
    }
}

int main() {
    unsigned char key[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE];
    unsigned char input[1024];  // Max input length
    unsigned char encrypted[1024];
    unsigned char decrypted[1024];
    int length;

    // User input for plaintext
    printf("Enter the plaintext:\n");
    fgets((char*)input, sizeof(input), stdin);
    trim_input((char*)input);

    // Check if the plaintext is empty
    length = strlen((char*)input);
    if (length == 0) {
        printf("No plaintext entered, exiting.\n");
        return 0;
    }

    // User input for key (as string)
    char key_input[BLOCK_SIZE + 1];  // Allow for 8 characters + null terminator
    printf("Enter an 8-character key (string):\n");
    fgets(key_input, sizeof(key_input), stdin);
    key_input[strcspn(key_input, "\n")] = '\0';  // Remove newline character
    strncpy((char*)key, key_input, BLOCK_SIZE);

    // Clear the input buffer to ensure IV input is processed correctly
    while (getchar() != '\n');  // Flush input buffer

    // User input for IV (as string)
    char iv_input[BLOCK_SIZE + 1];   // Allow for 8 characters + null terminator
    printf("Enter an 8-character IV (string):\n");
    fgets(iv_input, sizeof(iv_input), stdin);
    iv_input[strcspn(iv_input, "\n")] = '\0';  // Remove newline character

    // Check if IV length is exactly 8 characters
    if (strlen(iv_input) != 8) {
        printf("Error: IV length must be exactly 8 characters.\n");
        return 1;
    }

    strncpy((char*)iv, iv_input, BLOCK_SIZE);

    // Encrypt the data
    cfb_encrypt(input, encrypted, key, iv, length);
    printf("Encrypted (Hexadecimal): ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", encrypted[i]);
    }
    printf("\n");

    // Decrypt the data
    cfb_decrypt(encrypted, decrypted, key, iv, length);
    printf("Decrypted: ");
    for (int i = 0; i < length; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}

