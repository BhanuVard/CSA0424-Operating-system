#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int read_count = 0;
int data = 0;

void* writer(void* arg) {
    sem_wait(&wrt);
    data++;
    printf("Writer %d modified data to %d\n", (int)arg, data);
    sem_post(&wrt);
    return NULL;
}

void* reader(void* arg) {
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("Reader %d read data as %d\n", (int)arg, data);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t read[5], write[2];
    int ids[5];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        if (i < 2) {
            pthread_create(&write[i], NULL, writer, &ids[i]);
        }
        pthread_create(&read[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        if (i < 2) {
            pthread_join(write[i], NULL);
        }
        pthread_join(read[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
