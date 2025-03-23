#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int q, alpha;  // Prime number (q) and primitive root (alpha)
    long long Xa, Xb, Xd1, Xd2, Ya, Yb, Yd1, Yd2, Ka, Kb, KdA, KdB, K1, K2;

    // Get prime number from user
    printf("Enter a prime number (q): ");
    scanf("%d", &q);

    // Get primitive root from user
    printf("Enter a primitive root (alpha) of %d: ", q);
    scanf("%d", &alpha);

    // Get private keys for Alice and Bob
    printf("Enter private key for Alice (Xa): ");
    scanf("%lld", &Xa);
    printf("Enter private key for Bob (Xb): ");
    scanf("%lld", &Xb);

    // Get private keys for Mallory (Attacker)
    printf("Enter private key for Attacker with Alice (Xd1): ");
    scanf("%lld", &Xd1);
    printf("Enter private key for Attacker with Bob (Xd2): ");
    scanf("%lld", &Xd2);

    // Compute original public keys for Alice and Bob
    Ya = power_mod(alpha, Xa, q);  // Alice's public key
    Yb = power_mod(alpha, Xb, q);  // Bob's public key

    // Compute fake public keys for Mallory (Attacker)
    Yd1 = power_mod(alpha, Xd1, q);  // Mallory's fake public key with Alice
    Yd2 = power_mod(alpha, Xd2, q);  // Mallory's fake public key with Bob

    // Compute keys for Alice and Bob (MITM Attack)
    Ka = power_mod(Yd2, Xa, q);  // Ka = (Yd2^Xa) mod q
    Kb = power_mod(Yd1, Xb, q);  // Kb = (Yd1^Xb) mod q

    // Mallory computes shared keys with both Alice and Bob
    KdA = power_mod(Ya, Xd1, q);  // KdA = (Ya^Xd1) mod q (Mallory's key with Alice)
    KdB = power_mod(Yb, Xd2, q);  // KdB = (Yb^Xd2) mod q (Mallory's key with Bob)

    // Verify attack using alternative computation
    K1 = power_mod(Ya, Xd2, q);  // K1 = (Ya^Xd2) mod q
    K2 = power_mod(Yb, Xd1, q);  // K2 = (Yb^Xd1) mod q

    // Display computed shared keys
    printf("\nMITM Attack Verification:\n");
    printf("Ka = (Yd2^Xa) mod q = %lld\n", Ka);
    printf("Kb = (Yd1^Xb) mod q = %lld\n", Kb);
    printf("Mallory computes K1 = (Ya^Xd2) mod q = %lld\n", K1);
    printf("Mallory computes K2 = (Yb^Xd1) mod q = %lld\n", K2);

    // Check if attack was successful
    if (Ka == K1 && Kb == K2) {
        printf("\nMITM Attack Fully Verified: Mallory successfully hijacked the communication!\n");
    } else {
        printf("\nMITM Attack Failed: Keys do not match.\n");
    }

    return 0;
}

