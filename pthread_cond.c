#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int shared_int = 0; // Shared integer to be used for signaling
pthread_mutex_t lock;
pthread_cond_t cond;

void* worker(void *arg) {
    pthread_mutex_lock(&lock);
    // Wait for the condition to be signaled
    while (shared_int == 0) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    printf("Worker: Received signal!\n");
}

int main() {
    pthread_t thread;

    // Initialize mutex and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    // Create the worker thread
    pthread_create(&thread, NULL, worker, NULL);

    // Simulate some work in the main thread
    sleep(2);

    // Signal the worker thread
    pthread_mutex_lock(&lock);
    shared_int = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // Wait for the worker thread to finish
    pthread_join(thread, NULL);

    // Clean up
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}
