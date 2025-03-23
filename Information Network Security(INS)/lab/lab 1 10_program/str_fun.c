#include <stdio.h>
#include <string.h>

int main() {
    const char *str = "Hello, World!";
    printf("Length of string: %zu\n", strlen(str));

    const char *str1 = "Hello";
    const char *str2 = "World";
    int cmp_result = strcmp(str1, str2);
    printf("Comparison result: %d\n", cmp_result);

    char dest[50] = "Hello, ";
    const char *src = "World!";
    strcat(dest, src);
    printf("Concatenated string: %s\n", dest);

    return 0;
}
