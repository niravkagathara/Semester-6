#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

char* encrypt(int rows, int cols, int msg_len, const char* msg, int col_order[]) {
    int index = 0;
    char matrix[rows][cols];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (index >= msg_len) {
                matrix[r][c] = '_';
            } else {
                matrix[r][c] = msg[index++];
            }
        }
    }

    static char cipher[MAX_LEN];
    cipher[0] = '\0';

    for (int c = 0; c < cols; c++) {
        int col_pos = col_order[c] - 1;
        for (int r = 0; r < rows; r++) {
            char str[2] = {matrix[r][col_pos], '\0'};
            strcat(cipher, str);
        }
    }

    return cipher;
}

char* decrypt(int rows, int cols, const char* cipher, int col_order[]) {
    char matrix[rows][cols];
    int index = 0;

    for (int c = 0; c < cols; c++) {
        int col_pos = col_order[c] - 1;
        for (int r = 0; r < rows; r++) {
            matrix[r][col_pos] = cipher[index++];
        }
    }

    static char message[MAX_LEN];
    message[0] = '\0';

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (matrix[r][c] == '_') {
                matrix[r][c] = ' ';
            }
            char str[2] = {matrix[r][c], '\0'};
            strcat(message, str);
        }
    }

    return message;
}

int main() {
    char msg[MAX_LEN];
    char key[MAX_LEN];

    printf("Enter the message to encrypt: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    printf("Enter the key as space-separated numbers (e.g., '6 3 4 2 5 1'): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    int cols = 0;
    int col_order[100];
    char *token = strtok(key, " ");
    while (token != NULL) {
        col_order[cols++] = atoi(token);
        token = strtok(NULL, " ");
    }

    int sorted_order[100];
    for (int i = 0; i < cols; i++) {
        sorted_order[i] = col_order[i];
    }

    for (int i = 0; i < cols; i++) {
        for (int j = i + 1; j < cols; j++) {
            if (sorted_order[i] > sorted_order[j]) {
                int temp = sorted_order[i];
                sorted_order[i] = sorted_order[j];
                sorted_order[j] = temp;
            }
        }
    }

    int final_order[100];
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            if (col_order[j] == sorted_order[i]) {
                final_order[i] = j + 1;
            }
        }
    }

    int msg_len = strlen(msg);

    int rows = msg_len / cols;
    if (msg_len % cols != 0) {
        rows += 1;
    }

    char* encrypted_msg = encrypt(rows, cols, msg_len, msg, final_order);
    printf("Encrypted Message: %s\n", encrypted_msg);

    char* decrypted_msg = decrypt(rows, cols, encrypted_msg, final_order);
    printf("Decrypted Message: %s\n", decrypted_msg);

    return 0;
}