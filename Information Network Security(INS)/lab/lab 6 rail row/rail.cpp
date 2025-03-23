#include <stdio.h>
#include <string.h>

void railFenceEncrypt(char* text, int rails) {
    int len = strlen(text);
    char rail[rails][len];
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = ' ';
        }
    }
    
    int row = 0, col = 0;
    int dir_down = 0;  
    
    for (int i = 0; i < len; i++) {
        rail[row][col++] = text[i];
        
        if (row == 0 || row == rails - 1) {
            dir_down = !dir_down;
        }
        
        row = dir_down ? row + 1 : row - 1;
    }
    
    printf("Encrypted text: ");
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != ' ') {
                printf("%c", rail[i][j]);
            }
        }
    }
    printf("\n");
}

int main() {
    char text[100];
    int rails;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    text[strcspn(text, "\n")] = '\0';
    
    printf("Enter the number of rails: ");
    scanf("%d", &rails);
    
    if (rails < 2) {
        printf("Number of rails must be greater than 1.\n");
        return 1;
    }
    
    printf("Original text: %s\n", text);
    railFenceEncrypt(text, rails);
    return 0;
}
