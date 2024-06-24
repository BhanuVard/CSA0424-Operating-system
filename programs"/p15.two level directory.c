#include <stdio.h>
#include <string.h>

struct file {
    char name[20];
    int size;
};

struct directory {
    char name[20];
    struct file files[10];
    int file_count;
};

struct directory directories[5];
int dir_count = 0;

void create_directory(char* name) {
    strcpy(directories[dir_count].name, name);
    directories[dir_count].file_count = 0;
    dir_count++;
}

void create_file(char* dir_name, char* file_name, int size) {
    for (int i = 0; i < dir_count; i++) {
        if (strcmp(directories[i].name, dir_name) == 0) {
            int file_count = directories[i].file_count;
            strcpy(directories[i].files[file_count].name, file_name);
            directories[i].files[file_count].size = size;
            directories[i].file_count++;
            return;
        }
    }
}

void list_files() {
    for (int i = 0; i < dir_count; i++) {
        printf("Directory: %s\n", directories[i].name);
        for (int j = 0; j < directories[i].file_count; j++) {
            printf("  File: %s, Size: %d\n", directories[i].files[j].name, directories[i].files[j].size);
        }
    }
}

int main() {
    create_directory("dir1");
    create_directory("dir2");
    
    create_file("dir1", "file1.txt", 100);
    create_file("dir1", "file2.txt", 200);
    create_file("dir2", "file3.txt", 300);
    
    list_files();
    return 0;
}
