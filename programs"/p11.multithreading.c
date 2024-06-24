#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* threadFunc(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    
    if (pthread_create(&thread, NULL, threadFunc, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    printf("Thread finished execution\n");
    return 0;
}
