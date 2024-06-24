#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafeState() {
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        finished[i] = false;
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_PROCESSES; j++) {
            if (!finished[j]) {
                bool canAllocate = true;
                for (int k = 0; k < MAX_RESOURCES; k++) {
                    if (need[j][k] > work[k]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allocation[j][k];
                    }
                    finished[j] = true;
                    i = -1;
                }
            }
        }
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!finished[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Sample data for demonstration
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[MAX_PROCESSES][MAX_RESOURCES] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int avail[MAX_RESOURCES] = {3, 3, 2};

    // Copy data
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocation[i][j] = alloc[i][j];
            maximum[i][j] = max[i][j];
        }
    }
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] = avail[i];
    }

    calculateNeed();

    if (isSafeState()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}
