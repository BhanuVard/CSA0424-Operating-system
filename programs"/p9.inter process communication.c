#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    // Size of shared memory
    const int SIZE = 4096;
    
    // Shared memory key
    key_t key = 1234;
    
    // Shared memory id
    int shmid = shmget(key, SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    // Attach to the shared memory
    char *shm = (char *) shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write to shared memory
    char *message = "Hello, World!";
    strncpy(shm, message, SIZE);
    
    // Detach from shared memory
    shmdt(shm);
    
    // Reattach to read the message
    shm = (char *) shmat(shmid, NULL, 0);
    printf("Message from shared memory: %s\n", shm);
    
    // Detach and destroy shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
