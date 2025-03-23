#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Encryption function
char* Encryption(int no_rows, int len_key, int len_msg, const char* msg, int col_val[]) {
    int x = 0;
    char enc_mat[no_rows + 1][len_key];
    // creating the matrix
    for (int i = 0; i < no_rows + 1; i++) {
        for (int j = 0; j < len_key; j++) {
            // initializes the positions with '_' after the end of message
            if (x >= len_msg) {
                enc_mat[i][j] = '_';
            } else {
                enc_mat[i][j] = msg[x];
            }
            x++;
        }
    }

    int t = 1;
    static char cipher[1000];
    cipher[0] = '\0';
    // finding the cipher text according to the value of col_val matrix
    while (t <= len_key) {
        for (int i = 0; i < len_key; i++) {
            int k = col_val[i];
            if (k == t) {
                for (int j = 0; j < no_rows + 1; j++) {
                    char str[2] = {enc_mat[j][i], '\0'};
                    strcat(cipher, str);
                }
                t++;
            }
        }
    }
    return cipher;
}

// Decryption function
char* Decryption(int no_rows, int len_key, const char* cipher, int col_val[]) {
    char dec_mat[no_rows + 1][len_key];
    int x = 0, t = 1;
    // rearrange the matrix according to the col_val
    while (t <= len_key) {
        for (int i = 0; i < len_key; i++) {
            int k = col_val[i];
            if (k == t) {
                for (int j = 0; j < no_rows + 1; j++) {
                    dec_mat[j][i] = cipher[x];
                    x++;
                }
                t++;
            }
        }
    }

    static char message[1000];
    message[0] = '\0';
    for (int i = 0; i < no_rows + 1; i++) {
        for (int j = 0; j < len_key; j++) {
            // replacing the '_' with space
            if (dec_mat[i][j] == '_') {
                dec_mat[i][j] = ' ';
            }
            char str[2] = {dec_mat[i][j], '\0'};
            strcat(message, str);
        }
    }
    return message;
}

int main() {
    char msg[100];
    char key[100];

    // Get message input from user
    printf("Enter the message to encrypt: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0'; // Remove trailing newline

    // Get key input from user
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

    int len_key = strlen(key);
    int len_msg = strlen(msg);

    int val = 1, count = 0, ind;

    int col_val[len_key];
    // initializing col_val matrix with 0
    memset(col_val, 0, sizeof(col_val));
    // numbering the key alphabets according to their ASCII value
    while (count < len_key) {
        int min = 999;
        for (int i = 0; i < len_key; i++) {
            if ((min > (int)key[i]) && (col_val[i] == 0)) {
                min = (int)key[i];
                ind = i;
            }
        }
        col_val[ind] = val;
        count++;
        val++;
    }

    int no_rows = len_msg / len_key;
    if (len_msg % len_key != 0) {
        no_rows += 1;
    }

    // encrypted text
    char* cipher_text = Encryption(no_rows, len_key, len_msg, msg, col_val);
    printf("Encrypted Message: %s\n", cipher_text);

    // decrypted text
    char* original_msg = Decryption(no_rows, len_key, cipher_text, col_val);
    printf("Decrypted Message: %s\n", original_msg);

    return 0;
}
