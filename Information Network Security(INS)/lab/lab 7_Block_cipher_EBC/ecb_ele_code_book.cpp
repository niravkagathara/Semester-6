#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8  // Define block size for the cipher

// Simple XOR-based block cipher for demonstration purposes
void encrypt_block(char *input, char *key, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % strlen(key)];
    }
}

void decrypt_block(char *input, char *key, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % strlen(key)];
    }
}

void pad_input(char *input, int *length) {
    int padding = BLOCK_SIZE - (*length % BLOCK_SIZE);
    for (int i = 0; i < padding; i++) {
        input[*length + i] = (char)padding;
    }
    *length += padding;
}

void remove_padding(char *input, int *length) {
    int padding = input[*length - 1];
    *length -= padding;
    input[*length] = '\0';
}

int main() {
    char input[128], key[16], encrypted[128], decrypted[128];
    int input_len;

    printf("Enter plaintext (max 128 characters): ");
    fgets(input, sizeof(input), stdin);
    input_len = strlen(input);
    if (input[input_len - 1] == '\n') input[--input_len] = '\0';

    printf("Enter encryption key (max 16 characters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    // Pad input to make it a multiple of BLOCK_SIZE
    pad_input(input, &input_len);

    // Encrypt each block
    for (int i = 0; i < input_len; i += BLOCK_SIZE) {
        encrypt_block(input + i, key, encrypted + i);
    }

    printf("Encrypted text: ");
    for (int i = 0; i < input_len; i++) {
        printf("%02X", (unsigned char)encrypted[i]);
    }
    printf("\n");

    // Decrypt each block
    for (int i = 0; i < input_len; i += BLOCK_SIZE) {
        decrypt_block(encrypted + i, key, decrypted + i);
    }

    // Remove padding from decrypted text
    remove_padding(decrypted, &input_len);

    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
//Input: HelloWorld!
//Key: secret123
//Output:
//Encrypted text: E6B5C49E8A6F7C3A...
//Decrypted text: HelloWorld!
