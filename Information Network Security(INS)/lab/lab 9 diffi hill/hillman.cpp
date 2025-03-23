#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is a primitive root modulo q
int is_primitive_root(int alpha, int q) {
    int seen[q]; 
    for (int i = 0; i < q; i++) seen[i] = 0;

    int value = 1;
    for (int i = 0; i < q - 1; i++) {
        value = (value * alpha) % q;
        if (seen[value] == 1) return 0; // Duplicate value found, not a primitive root
        seen[value] = 1;
    }
    return 1;
}

// Function to find a primitive root of a prime number q
int find_primitive_root(int q) {
    for (int alpha = 2; alpha < q; alpha++) {
        if (is_primitive_root(alpha, q)) return alpha;
    }
    return -1; // No primitive root found (should not happen for prime q)
}

// Function to compute (base^exp) % mod using fast exponentiation
long long power_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int q, alpha, choice;
    long long Xa, Xb, Ya, Yb, Ka, Kb;

    // Get prime number from user
    printf("Enter a prime number (q): ");
    scanf("%d", &q);

    // Choose to enter or generate a primitive root
    printf("Choose:\n1. Enter a primitive root manually\n2. Auto-generate a primitive root\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a primitive root (alpha) of %d: ", q);
        scanf("%d", &alpha);
        if (!is_primitive_root(alpha, q)) {
            printf("Error: %d is not a primitive root of %d. Exiting...\n", alpha, q);
            return 1;
        }
    } else {
        alpha = find_primitive_root(q);
        if (alpha == -1) {
            printf("Error: Could not find a primitive root for %d. Exiting...\n", q);
            return 1;
        }
        printf("Auto-generated primitive root (alpha): %d\n", alpha);
    }

    // Get private keys from users
    printf("Enter private key for User A (Xa): ");
    scanf("%lld", &Xa);
    printf("Enter private key for User B (Xb): ");
    scanf("%lld", &Xb);

    // Compute public keys
    Ya = power_mod(alpha, Xa, q);
    Yb = power_mod(alpha, Xb, q);

    // Compute shared secret keys
    Ka = power_mod(Yb, Xa, q); // Ka = Yb^Xa mod q
    Kb = power_mod(Ya, Xb, q); // Kb = Ya^Xb mod q

    // Display results
    printf("\nPublic Key for User A (Ya = alpha^Xa mod q): %lld\n", Ya);
    printf("Public Key for User B (Yb = alpha^Xb mod q): %lld\n", Yb);
    printf("Shared Secret Key (Ka = Yb^Xa mod q): %lld\n", Ka);
    printf("Shared Secret Key (Kb = Ya^Xb mod q): %lld\n", Kb);

    // Verify if both keys match
    if (Ka == Kb) {
        printf("\nVerification successful! Both users have the same shared secret key: %lld\n", Ka);
    } else {
        printf("\nError: Shared keys do not match! Key exchange failed.\n");
    }

    return 0;
}

