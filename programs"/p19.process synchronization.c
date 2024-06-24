#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

void* criticalSection(void* arg) {
    pthread_mutex_lock(&lock);

    printf("Thread %d is in the critical section\n", (int)arg);
    sleep(1);
    printf("Thread %d is leaving the critical section\n", (int)arg);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, criticalSection, &thread_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}
