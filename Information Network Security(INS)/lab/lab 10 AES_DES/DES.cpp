#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function to allocate and initialize permutation tables dynamically
void initialize_permutation(int **table, int size, const int values[]) {
    *table = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        (*table)[i] = values[i];
    }
}

// Function to apply a permutation table dynamically
uint64_t permute(uint64_t block, int *table, int size) {
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        result |= ((block >> (64 - table[i])) & 1) << (size - i - 1);
    }
    return result;
}

// Function to perform DES encryption
uint64_t des_encrypt(uint64_t plaintext, uint64_t key, int *IP, int *IP_INV, int *PC1, int *PC2, int *E, int *P) {
    // Apply Initial Permutation (IP)
    plaintext = permute(plaintext, IP, 64);

    printf("\nAfter Initial Permutation: %llx", plaintext);

    // Split into L and R
    uint32_t L = (plaintext >> 32) & 0xFFFFFFFF;
    uint32_t R = plaintext & 0xFFFFFFFF;

    printf("\nInitial L: %x, R: %x", L, R);

    // Placeholder for 16 rounds of encryption
    for (int i = 0; i < 16; i++) {
        uint32_t old_R = R;

        // Expansion (E-box)
        uint64_t expanded_R = permute(R, E, 48);

        // Simulated key XOR (in real case, use round key)
        expanded_R ^= key; 

        // Dummy S-Box Substitution (for demonstration, real S-box logic needed)
        uint32_t substituted = expanded_R & 0xFFFFFFFF;

        // P-Box permutation
        uint32_t permuted = permute(substituted, P, 32);

        // XOR with L
        R = L ^ permuted;
        L = old_R;

        printf("\nRound %d -> L: %x, R: %x", i + 1, L, R);
    }

    // Swap L and R
    uint64_t pre_output = ((uint64_t)R << 32) | L;

    // Apply Final Permutation (IP?�)
    uint64_t ciphertext = permute(pre_output, IP_INV, 64);

    return ciphertext;
}

int main() {
    uint64_t plaintext, key;

    printf("Enter 64-bit plaintext (in hex): ");
    scanf("%llx", &plaintext);
    printf("Enter 64-bit key (in hex): ");
    scanf("%llx", &key);

    // Define tables dynamically
    int *IP, *IP_INV, *PC1, *PC2, *E, *P;

    // Initial Permutation (IP)
    int ip_values[] = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                        62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                        57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };
    initialize_permutation(&IP, 64, ip_values);

    // Final Permutation (IP?�)
    int ip_inv_values[] = { 40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
                             38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
                             36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
                             34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25 };
    initialize_permutation(&IP_INV, 64, ip_inv_values);

    // Permuted Choice 1 (PC-1)
    int pc1_values[] = { 57, 49, 41, 33, 25, 17,  9, 1, 58, 50, 42, 34, 26, 18,
                         10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
                         63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
                         14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4 };
    initialize_permutation(&PC1, 56, pc1_values);

    // Expansion (E-Box)
    int e_values[] = { 32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
                        8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
                       16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
                       24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1 };
    initialize_permutation(&E, 48, e_values);

    // P-Box
    int p_values[] = { 16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,
                        5, 18, 31, 10,  2,  8, 24, 14, 32, 27,  3,  9,
                       19, 13, 30,  6, 22, 11,  4, 25 };
    initialize_permutation(&P, 32, p_values);

    // Perform encryption
    uint64_t ciphertext = des_encrypt(plaintext, key, IP, IP_INV, PC1, PC2, E, P);

    printf("\nCiphertext: %llx\n", ciphertext);

    // Free dynamically allocated memory
    free(IP); free(IP_INV); free(PC1); free(PC2); free(E); free(P);

    return 0;
}

// Enter 64-bit plaintext (in hex): abc123
// Enter 64-bit key (in hex): a1a2b1b2

// After Initial Permutation: 400000e060a020a0
// Initial L: 400000e0, R: 60a020a0
// Round 1 -> L: 60a020a0, R: 400000e0
// Round 2 -> L: 400000e0, R: 60a020a0
// Round 3 -> L: 60a020a0, R: 400000e0
// Round 4 -> L: 400000e0, R: 60a020a0
// Round 5 -> L: 60a020a0, R: 400000e0
// Round 6 -> L: 400000e0, R: 60a020a0
// Round 7 -> L: 60a020a0, R: 400000e0
// Round 8 -> L: 400000e0, R: 60a020a0
// Round 9 -> L: 60a020a0, R: 400000e0
// Round 10 -> L: 400000e0, R: 60a020a0
// Round 11 -> L: 60a020a0, R: 400000e0
// Round 12 -> L: 400000e0, R: 60a020a0
// Round 13 -> L: 60a020a0, R: 400000e0
// Round 14 -> L: 400000e0, R: 60a020a0
// Round 15 -> L: 60a020a0, R: 400000e0
// Round 16 -> L: 400000e0, R: 60a020a0
// Ciphertext: 57c213
// PS F:\semester 6\Information Network Security(INS)\lab\lab 10 AES_DES> cd "f:\semester 6\Information Network Security(INS)\lab\lab 10 AES_DES\" ; if ($?) { g++ DES.cpp -o DES } ; if ($?) { .\DES }
// Enter 64-bit plaintext (in hex): 57c213
// Enter 64-bit key (in hex): a1a2b1b2

// After Initial Permutation: 60a020a0400000e0
// Initial L: 60a020a0, R: 400000e0
// Round 1 -> L: 400000e0, R: 60a020a0
// Round 2 -> L: 60a020a0, R: 400000e0
// Round 3 -> L: 400000e0, R: 60a020a0
// Round 4 -> L: 60a020a0, R: 400000e0
// Round 5 -> L: 400000e0, R: 60a020a0
// Round 6 -> L: 60a020a0, R: 400000e0
// Round 7 -> L: 400000e0, R: 60a020a0
// Round 8 -> L: 60a020a0, R: 400000e0
// Round 9 -> L: 400000e0, R: 60a020a0
// Round 10 -> L: 60a020a0, R: 400000e0
// Round 11 -> L: 400000e0, R: 60a020a0
// Round 12 -> L: 60a020a0, R: 400000e0
// Round 13 -> L: 400000e0, R: 60a020a0
// Round 14 -> L: 60a020a0, R: 400000e0
// Round 15 -> L: 400000e0, R: 60a020a0
// Round 16 -> L: 60a020a0, R: 400000e0
// Ciphertext: abc123