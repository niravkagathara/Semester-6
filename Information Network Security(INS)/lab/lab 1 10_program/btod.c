#include <stdio.h>
#include <string.h>

void decimal_to_binary(int decimal) {
    int binary[32], i = 0;
    
    while (decimal > 0) {
        binary[i] = decimal % 2;
        decimal /= 2;
        i++;
    }
    
    printf("Binary representation: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
    printf("\n");
}

int binary_to_decimal(char binary[]) {
    int decimal = 0, base = 1, len = strlen(binary);
    
    for (int i = len - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    
    return decimal;
}

int main() {
    int choice;
    printf("Choose: 1. Decimal to Binary 2. Binary to Decimal: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int decimal;
        printf("Enter decimal number: ");
        scanf("%d", &decimal);
        decimal_to_binary(decimal);
    } else if (choice == 2) {
        char binary[32];
        printf("Enter binary number: ");
        scanf("%s", binary);
        printf("Decimal representation: %d\n", binary_to_decimal(binary));
    } else {
        printf("Invalid option.\n");
    }

    return 0;
}