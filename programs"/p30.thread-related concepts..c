#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

// Thread-related concepts

void *thread_create(void *arg) {
    printf("Thread created!\n");
    return NULL;
}

void *thread_join(void *arg) {
    printf("Thread running!\n");
    pthread_exit((void *)42);
}

void *thread_equal(void *arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu\n", tid);
    return NULL;
}

void *thread_exit(void *arg) {
    printf("Thread exiting!\n");
    pthread_exit(NULL);
}

// FIFO Paging technique
void simulate_fifo(int pages[], int n, int capacity) {
    int *frames = (int *)malloc(capacity * sizeof(int));
    int *time = (int *)malloc(capacity * sizeof(int));
    int count = 0, page_faults = 0;
    bool found;
    
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = -1;
    }
    
    for (int i = 0; i < n; i++) {
        found = false;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            if (count < capacity) {
                frames[count] = pages[i];
                time[count] = i;
                count++;
            } else {
                int min_time = time[0], min_index = 0;
                for (int j = 1; j < capacity; j++) {
                    if (time[j] < min_time) {
                        min_time = time[j];
                        min_index = j;
                    }
                }
                frames[min_index] = pages[i];
                time[min_index] = i;
            }
            page_faults++;
        }
        
        printf("Frames after accessing page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }
    
    printf("Total page faults (FIFO): %d\n", page_faults);
    free(frames);
    free(time);
}

// LRU Paging technique
void simulate_lru(int pages[], int n, int capacity) {
    int *frames = (int *)malloc(capacity * sizeof(int));
    int *time = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    bool found;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        found = false;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                time[j] = i;
                found = true;
                break;
            }
        }

        if (!found) {
            int lru = time[0], lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < lru) {
                    lru = time[j];
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            time[lru_index] = i;
            page_faults++;
        }

        printf("Frames after accessing page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total page faults (LRU): %d\n", page_faults);
    free(frames);
    free(time);
}

int main() {
    pthread_t thread1, thread2, thread3, thread4;
    void *retval;

    // Demonstrate thread create
    pthread_create(&thread1, NULL, thread_create, NULL);
    pthread_join(thread1, NULL);

    // Demonstrate thread join
    pthread_create(&thread2, NULL, thread_join, NULL);
    pthread_join(thread2, &retval);
    printf("Thread returned: %ld\n", (long)retval);

    // Demonstrate thread equal
    pthread_create(&thread3, NULL, thread_equal, NULL);
    pthread_create(&thread4, NULL, thread_equal, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    if (pthread_equal(thread3, thread4)) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Demonstrate thread exit
    pthread_create(&thread1, NULL, thread_exit, NULL);
    pthread_join(thread1, NULL);

    // Simulate FIFO Paging technique
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("\nFIFO Paging Simulation:\n");
    simulate_fifo(pages, n, capacity);

    // Simulate LRU Paging technique
    printf("\nLRU Paging Simulation:\n");
    simulate_lru(pages, n, capacity);

    return 0;
}

