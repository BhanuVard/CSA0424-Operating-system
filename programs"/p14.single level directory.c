#include <stdio.h>
#include <string.h>

struct file {
    char name[20];
    int size;
};

struct file directory[10];
int file_count = 0;

void create_file(char* name, int size) {
    strcpy(directory[file_count].name, name);
    directory[file_count].size = size;
    file_count++;
}

void list_files() {
    for (int i = 0; i < file_count; i++) {
        printf("File: %s, Size: %d\n", directory[i].name, directory[i].size);
    }
}

int main() {
    create_file("file1.txt", 100);
    create_file("file2.txt", 200);
    
    list_files();
    return 0;
}
