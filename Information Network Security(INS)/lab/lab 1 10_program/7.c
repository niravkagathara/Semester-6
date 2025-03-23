#include <stdio.h>

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}
void writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

int main() {
    const char *filename = "example.txt";
    writeFile(filename, "Hello, World!");
    readFile(filename);
}
