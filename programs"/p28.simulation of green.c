#include <stdio.h>
#include <string.h>

void grep(FILE *fp, const char *search_term) {
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, search_term)) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s search_term file\n", argv[0]);
        return 1;
    }

    const char *search_term = argv[1];
    const char *filename = argv[2];
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    grep(fp, search_term);

    fclose(fp);
    return 0;
}

