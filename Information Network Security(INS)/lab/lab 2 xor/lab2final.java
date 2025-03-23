public class lab2final {

    // Method to encrypt and decrypt text using Caesar Cipher
    public static String caesarCipher(String text, int shift, String mode) {
        StringBuilder result = new StringBuilder();
        
        if (mode.equalsIgnoreCase("decrypt")) {
            shift = -shift;  // For decryption, reverse the shift
        }

        // Iterate through each character in the text
        for (int i = 0; i < text.length(); i++) {
            char charAt = text.charAt(i);

            // Encrypt or decrypt alphabetic characters
            if (Character.isLetter(charAt)) {
                char base = Character.isUpperCase(charAt) ? 'A' : 'a';
                char newChar = (char) ((charAt - base + shift + 26) % 26 + base);
                result.append(newChar);
            } else {
                // Non-alphabetic characters remain unchanged
                result.append(charAt);
            }
        }

        return result.toString();
    }

    public static void main(String[] args) {
        String text = "Hello, World!";
        int shift = 3;

        // Encrypt the text
        String encryptedText = caesarCipher(text, shift, "encrypt");
        System.out.println("Encrypted Text: " + encryptedText);

        // Decrypt the text
        String decryptedText = caesarCipher(encryptedText, shift, "decrypt");
        System.out.println("Decrypted Text: " + decryptedText);
    }
}
