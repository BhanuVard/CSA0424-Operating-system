#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a new process
    
    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
    } else if (pid > 0) {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
    } else {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    return 0;
}

