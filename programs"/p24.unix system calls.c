#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buf[100];

    // Creating a file
    fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Failed to create file");
        return 1;
    }
    
    // Writing to the file
    if (write(fd, "Hello, World!\n", 14) < 0) {
        perror("Failed to write to file");
        return 1;
    }
    close(fd);

    // Reading from the file
    fd = open("file.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }
    if (read(fd, buf, sizeof(buf)) < 0) {
        perror("Failed to read from file");
        return 1;
    }
    printf("File contents: %s", buf);
    close(fd);

    // Renaming the file
    if (rename("file.txt", "newfile.txt") < 0) {
        perror("Failed to rename file");
        return 1;
    }

    // Deleting the file
    if (unlink("newfile.txt") < 0) {
        perror("Failed to delete file");
        return 1;
    }

    return 0;
}
