#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000
#define MAX_VALUE 256

// Structure to pass data to threads
typedef struct {
    int* data;
    int start;
    int end;
    int* local_hist;
} ThreadData;

// Global histogram array and mutex for thread synchronization
int global_histogram[MAX_VALUE] = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function to calculate local histogram
void* calculate_histogram(void* arg) {
    ThreadData* thread_data = (ThreadData*)arg;
    int* local_hist = (int*)calloc(MAX_VALUE, sizeof(int));
    
    // Calculate local histogram for the chunk
    for (int i = thread_data->start; i < thread_data->end; i++) {
        local_hist[thread_data->data[i]]++;
    }
    
    // Update global histogram with local results
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_VALUE; i++) {
        global_histogram[i] += local_hist[i];
    }
    pthread_mutex_unlock(&mutex);
    
    free(local_hist);
    pthread_exit(NULL);
}

int main() {
    // Initialize random data array
    int* data = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % MAX_VALUE;  // Random values between 0 and 255
    }
    
    // Create threads and their data
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    
    // Launch threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].data = data;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
        
        if (pthread_create(&threads[i], NULL, calculate_histogram, &thread_data[i])) {
            printf("Error creating thread %d\n", i);
            exit(1);
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Print the histogram
    printf("Histogram:\n");
    for (int i = 0; i < MAX_VALUE; i++) {
        if (global_histogram[i] > 0) {
            printf("Value %d: %d occurrences\n", i, global_histogram[i]);
        }
    }
    
    // Cleanup
    pthread_mutex_destroy(&mutex);
    free(data);
    return 0;
}