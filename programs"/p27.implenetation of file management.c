#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Create a new file
    int fd = open("testfile.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write to the file
    const char *text = "Hello, File Management!\n";
    if (write(fd, text, strlen(text)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Read from the file
    lseek(fd, 0, SEEK_SET);
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';
    printf("Content read from file: %s", buffer);

    // Close the file
    close(fd);

    // Remove the file
    if (unlink("testfile.txt") == -1) {
        perror("unlink");
        return 1;
    }

    return 0;
}

