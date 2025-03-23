//second 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // Define block size (e.g., 8 bytes)

void xor_blocks(char *block1, char *block2, char *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// CFB encryption: Shift register, then XOR with plaintext
void cfb_encrypt(char *plaintext, char *key, char *iv, char *ciphertext, int text_len, int block_size) {
    char shift_register[BLOCK_SIZE], temp[BLOCK_SIZE];
    memcpy(shift_register, iv, block_size); // Initialize with IV

    for (int i = 0; i < text_len; i++) {
        memcpy(temp, shift_register, block_size); // Copy shift register to temp for encryption
        xor_blocks(temp, key, temp, block_size); // XOR with key (simulate encryption)
        ciphertext[i] = plaintext[i] ^ temp[0]; // XOR with first byte of the shifted output
        memmove(shift_register, shift_register + 1, block_size - 1); // Shift register left
        shift_register[block_size - 1] = ciphertext[i]; // Append ciphertext byte to shift register
    }
}

// CFB decryption: Reverse the process by using the same key and IV
void cfb_decrypt(char *ciphertext, char *key, char *iv, char *plaintext, int text_len, int block_size) {
    char shift_register[BLOCK_SIZE], temp[BLOCK_SIZE];
    memcpy(shift_register, iv, block_size); // Initialize with IV

    for (int i = 0; i < text_len; i++) {
        memcpy(temp, shift_register, block_size); // Copy shift register to temp for decryption
        xor_blocks(temp, key, temp, block_size); // XOR with key (simulate decryption)
        plaintext[i] = ciphertext[i] ^ temp[0]; // XOR with first byte of the shifted output
        memmove(shift_register, shift_register + 1, block_size - 1); // Shift register left
        shift_register[block_size - 1] = ciphertext[i]; // Append ciphertext byte to shift register
    }
}

int main() {
    char plaintext[256], key[BLOCK_SIZE], iv[BLOCK_SIZE];
    int text_len;

    printf("Enter plaintext (max 256 characters): ");
    fgets(plaintext, 256, stdin);
    text_len = strlen(plaintext);
    if (plaintext[text_len - 1] == '\n') plaintext[--text_len] = '\0'; // Remove newline

    printf("Enter a %d-byte key: ", BLOCK_SIZE);
    fgets(key, BLOCK_SIZE + 1, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline from key

    printf("Enter a 8-byte IV: ");
    scanf("%8s", iv); // Read exactly 8 characters for IV

    if (strlen(iv) != BLOCK_SIZE) {
        fprintf(stderr, "Error: IV must be exactly %d bytes long.\n", BLOCK_SIZE);
        return 1;
    }

    // Padding the plaintext to a multiple of BLOCK_SIZE
    int padded_len = ((text_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    for (int i = text_len; i < padded_len; i++) {
        plaintext[i] = '\0'; // Pad with null bytes
    }
    plaintext[padded_len] = '\0';

    char *ciphertext = (char *)malloc(padded_len);
    char *decrypted_text = (char *)malloc(padded_len);

    cfb_encrypt(plaintext, key, iv, ciphertext, padded_len, BLOCK_SIZE);

    printf("\nEncrypted text (hex): ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02x ", (unsigned char)ciphertext[i]);
    }

    cfb_decrypt(ciphertext, key, iv, decrypted_text, padded_len, BLOCK_SIZE);

    printf("\nDecrypted text: %s\n", decrypted_text);

    free(ciphertext);
    free(decrypted_text);
    return 0;
}

