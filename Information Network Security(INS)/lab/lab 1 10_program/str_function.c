#include <stdio.h>

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* my_strcat(char *dest, const char *src) {
    int i = 0, j = 0;
    while (dest[i] != '\0') {
        i++;
    }
    while (src[j] != '\0' && i < sizeof(dest) - 1) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int main() {
    char str1[100] = "Hello, ";
    char str2[] = "World!";
    
    printf("Length of str1: %d\n", my_strlen(str1));
    printf("Concatenated string: %s\n", my_strcat(str1, str2));
    printf("Comparison result: %d\n", my_strcmp("abc", "abc"));
    
    return 0;
}
