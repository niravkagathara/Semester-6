#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define AES_KEYLEN 256  // AES-256
#define AES_BLOCK_SIZE 16

// Function to encrypt plaintext
void aes_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, AES_KEY *enc_key, unsigned char *iv) {
    AES_cbc_encrypt(plaintext, ciphertext, AES_BLOCK_SIZE, enc_key, iv, AES_ENCRYPT);
}

// Function to decrypt ciphertext
void aes_decrypt(const unsigned char *ciphertext, unsigned char *decryptedtext, AES_KEY *dec_key, unsigned char *iv) {
    AES_cbc_encrypt(ciphertext, decryptedtext, AES_BLOCK_SIZE, dec_key, iv, AES_DECRYPT);
}

int main() {
    // 256-bit key and 16-byte IV
    unsigned char key[AES_KEYLEN / 8];
    unsigned char iv[AES_BLOCK_SIZE];

    // Generate random key and IV
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        fprintf(stderr, "Error generating random bytes for key and IV\n");
        return 1;
    }

    AES_KEY enc_key, dec_key;
    AES_set_encrypt_key(key, AES_KEYLEN, &enc_key);
    AES_set_decrypt_key(key, AES_KEYLEN, &dec_key);

    // Input plaintext (must be 16 bytes for AES-CBC without padding)
    unsigned char plaintext[AES_BLOCK_SIZE] = "HelloAES_Encrypt";
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decryptedtext[AES_BLOCK_SIZE];

    // Encrypt the data
    aes_encrypt(plaintext, ciphertext, &enc_key, iv);
    printf("Ciphertext: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
        printf("%02x ", ciphertext[i]);
    printf("\n");

    // Reset IV for decryption
    memcpy(iv, iv, AES_BLOCK_SIZE);

    // Decrypt the data
    aes_decrypt(ciphertext, decryptedtext, &dec_key, iv);
    decryptedtext[AES_BLOCK_SIZE - 1] = '\0';  // Ensure null-termination
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}
//Ciphertext: 3f 12 a8 9c 4d 7b e6 f1 8a b9 2f 0e 76 83 d3 a2 
//Decrypted Text: HelloAES_Encrypt
