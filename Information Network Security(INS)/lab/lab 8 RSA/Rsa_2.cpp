#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse using d = (1 + j * f(n)) / e
int findPrivateKey(int e, int phi_n) {
    int j = 1;
    while (1) {
        if ((1 + j * phi_n) % e == 0) {
            return (1 + j * phi_n) / e;
        }
        j++;
    }
}

// Function to perform modular exponentiation: (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int p, q, e;

    // User input for prime numbers
    printf("Enter first prime number (p): ");
    scanf("%d", &p);
    printf("Enter second prime number (q): ");
    scanf("%d", &q);

    // Compute n and f(n)
    int n = p * q;
    int phi_n = (p - 1) * (q - 1);

    // Ensure n is large enough
    if (n < 128) {
        printf("Error: n = %d is too small! Choose larger primes.\n", n);
        return 1;
    }

    // User enters e
    printf("Enter public exponent (e) (must be coprime with f(n) = %d): ", phi_n);
    scanf("%d", &e);

    // Check if e is valid
    if (gcd(e, phi_n) != 1) {
        printf("Error: e is not coprime with f(n). Choose another e.\n");
        return 1;
    }

    // Compute private key d
    int d = findPrivateKey(e, phi_n);

    // Display public and private keys
    printf("\nPublic Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Clear input buffer
    while (getchar() != '\n');

    // User input for plaintext string
    char plaintext[256];
    printf("\nEnter the message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline

    int len = strlen(plaintext);
    long long encrypted[len], decrypted[len];

    // Encrypt each character
    printf("\nEncrypted Message:\n");
    for (int i = 0; i < len; i++) {
        encrypted[i] = modExp(plaintext[i], e, n);
        printf("%lld ", encrypted[i]);
    }
    printf("\n");

    // Decrypt each character
    printf("\nDecrypted Message: ");
    for (int i = 0; i < len; i++) {
        decrypted[i] = modExp(encrypted[i], d, n);
        printf("%c", (char)decrypted[i]);
    }
    printf("\n");

    return 0;
}

