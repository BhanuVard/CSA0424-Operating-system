#include <stdio.h>
#include <stdlib.h>

void copyFile(const char *src, const char *dest) {
    FILE *srcFile = fopen(src, "r");
    FILE *destFile = fopen(dest, "w");
    char ch;
    
    if (srcFile == NULL || destFile == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }
    
    while ((ch = fgetc(srcFile)) != EOF) {
        fputc(ch, destFile);
    }
    
    fclose(srcFile);
    fclose(destFile);
}

int main() {
    const char *src = "source.txt";
    const char *dest = "destination.txt";
    
    copyFile(src, dest);
    printf("File copied successfully.\n");
    
    return 0;
}

