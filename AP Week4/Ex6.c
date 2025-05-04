#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4 // Number of threads

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   // Condition variable for signaling
int counter = 0; // Tracks how many threads have reached the barrier

void *thread_func(void *arg);

int main() {
    pthread_t threads[N];
    int thread_ids[N];

    // Create threads
    for (int i = 0; i < N; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

void *thread_func(void *arg) {
    int id = *(int *)arg;

    // Each thread prints before reaching the barrier
    printf("Thread %d reached the barrier\n", id);

    pthread_mutex_lock(&lock);
    counter++;

    if (counter == N) {
        // Last thread to arrive prints message and signals others
        printf("All threads reached the barrier! Releasing them...\n");
        pthread_cond_broadcast(&cond);
    } else {
        // Wait for other threads to reach the barrier
        while (counter < N) {
            pthread_cond_wait(&cond, &lock);
        }
    }
    
    pthread_mutex_unlock(&lock);

    // Each thread prints after passing the barrier
    printf("Thread %d passed the barrier\n", id);

    return NULL;
}
