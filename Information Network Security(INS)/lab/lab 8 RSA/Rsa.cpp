#include <stdio.h>
#include <stdlib.h>

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

// Function to find the smallest possible `e` that is relatively prime to f(n)
int findRelativePrimeE(int phi_n) {
    int e = 2; // Start checking from 2
    while (gcd(e, phi_n) != 1) {
        e++; // Increment until we find a valid `e`
    }
    return e;
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
    int p, q, e, choice;

    // User input for prime numbers
    printf("Enter first prime number (p): ");
    scanf("%d", &p);
    printf("Enter second prime number (q): ");
    scanf("%d", &q);

    // Compute n and f(n)
    int n = p * q;
    int phi_n = (p - 1) * (q - 1);

    // User chooses to enter `e` or generate one automatically
    printf("\nChoose an option for public exponent e:\n");
    printf("1. Enter your own value of e\n");
    printf("2. Use an automatically selected e (relative prime to f(n))\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a value for e (must be coprime with f(n) = %d): ", phi_n);
        scanf("%d", &e);
        if (gcd(e, phi_n) != 1) {
            printf("Invalid choice! e is not coprime with f(n). Exiting.\n");
            return 1;
        }
    } else {
        e = findRelativePrimeE(phi_n);
        printf("Automatically chosen e: %d\n", e);
    }

    // Compute private key d
    int d = findPrivateKey(e, phi_n);

    // Display public and private keys
    printf("\nPublic Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // User input for message
    int plaintext;
    printf("\nEnter the message (as a number) to encrypt: ");
    scanf("%d", &plaintext);

    // Encryption
    long long ciphertext = modExp(plaintext, e, n);
    printf("Encrypted Message: %lld\n", ciphertext);

    // Decryption
    long long decryptedMessage = modExp(ciphertext, d, n);
    printf("Decrypted Message: %lld\n", decryptedMessage);

    return 0;
}

