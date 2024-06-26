#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void file_stat(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", path);
    printf("Size: %ld bytes\n", statbuf.st_size);
    printf("Permissions: %o\n", statbuf.st_mode);
}

void read_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    // fcntl usage example
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fcntl(fd, F_SETFL, O_APPEND) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }
    
    // write to file
    const char *text = "Hello, World!\n";
    write(fd, text, strlen(text));

    // lseek usage example
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    close(fd);

    // stat usage example
    file_stat("example.txt");

    // opendir and readdir usage example
    printf("Reading current directory:\n");
    read_directory(".");

    return 0;
}

