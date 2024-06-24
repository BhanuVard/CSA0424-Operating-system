#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

char memory[MEMORY_SIZE];
int next_free = 0;

void* my_malloc(size_t size) {
    if (next_free + size > MEMORY_SIZE) {
        return NULL;
    }
    void* ptr = &memory[next_free];
    next_free += size;
    return ptr;
}

void my_free(void* ptr) {
    // Simple allocator, doesn't support free
}

int main() {
    int* p = (int*)my_malloc(sizeof(int) * 10);
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < 10; i++) {
        p[i] = i * i;
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    return 0;
}
