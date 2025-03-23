#include <stdio.h>
#include <ctype.h>

// Function to encrypt and decrypt text using Caesar Cipher
void caesarCipher(char* text, int shift, char* mode) {
    if (mode == "decrypt") {
        shift = -shift;  // Reverse the shift for decryption
    }

    // Iterate through each character in the string
    for (int i = 0; text[i] != '\0'; i++) {
        char charAt = text[i];

        // Encrypt or decrypt alphabetic characters
        if (isalpha(charAt)) {
            char base = isupper(charAt) ? 'A' : 'a';
            text[i] = (char)(((charAt - base + shift + 26) % 26) + base);
        }
    }
}

int main() {
    char text[] = "Hello, World!";
    int shift = 3;

    // Encrypt the text
    caesarCipher(text, shift, "encrypt");
    printf("Encrypted Text: %s\n", text);

    // Decrypt the text
    caesarCipher(text, shift, "decrypt");
    printf("Decrypted Text: %s\n", text);

    return 0;
}
