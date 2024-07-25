#include <stdio.h>
#include <pthread.h>

// Shared variable and mutex
int shared_data = 0;
pthread_mutex_t my_mutex;

void* thread_func(void* arg) {
    pthread_mutex_lock(&my_mutex);  // Lock the mutex
    shared_data++;                  // Critical section
    printf("Thread %ld incremented shared_data to %d\n", (long)arg, shared_data);
    pthread_mutex_unlock(&my_mutex); // Unlock the mutex
    return NULL;
}

int main() {
    pthread_t threads[2];

    // Initialize the mutex
    pthread_mutex_init(&my_mutex, NULL);

    // Create threads
    for (long i = 0; i < 2; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the mutex, doesn't change the output, but might prevent a memory and/or resource leak.
    pthread_mutex_destroy(&my_mutex);
}
