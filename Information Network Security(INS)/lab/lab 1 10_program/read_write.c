#include <stdio.h>
int main() {
    const char *filename = "example.txt";
    FILE *file;
    char content[255];
    file = fopen(filename, "w"); 
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1; 
    }
    printf("Please enter content to write to the text file: ");
    fgets(content, sizeof(content), stdin);
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content written to '%s'.\n", filename);
    file = fopen(filename, "r"); 
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1; 
    }
    printf("File content:\n");
    while (fgets(content, sizeof(content), file) != NULL) {
        printf("%s", content); 
    }
    fclose(file);
    return 0; 
}