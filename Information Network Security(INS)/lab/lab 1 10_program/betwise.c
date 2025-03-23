#include <stdio.h>

int isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}
int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (isPowerOfTwo(number)) {
        printf("%d is a power of 2.\n", number);
    } else {
        printf("%d is not a power of 2.\n", number);
    }
    return 0;
}