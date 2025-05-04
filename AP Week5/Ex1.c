#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define RANGE_START 1
#define RANGE_END 10000000

// Structure to hold thread arguments
typedef struct {
    long start;
    long end;
    long count;
} ThreadArgs;

// Thread function to count odd numbers in a range
void* countOddNumbers(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->count = 0;

    for (long i = args->start; i <= args->end; i++) {
        if (i % 2 != 0) {
            args->count++;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    long total_count = 0;
    
    // Calculate range size for each thread
    long range_size = (RANGE_END - RANGE_START + 1) / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].start = RANGE_START + (i * range_size);
        thread_args[i].end = (i == NUM_THREADS - 1) ? RANGE_END : RANGE_START + ((i + 1) * range_size - 1);
        
        int rc = pthread_create(&threads[i], NULL, countOddNumbers, 
                              (void*)&thread_args[i]);
        if (rc) {
            printf("Error creating thread %d\n", i);
            exit(-1);
        }
    }

    // Wait for threads to complete and sum their counts
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_count += thread_args[i].count;
    }

    printf("Total odd numbers between %d and %d: %ld\n", 
           RANGE_START, RANGE_END, total_count);

    return 0;
}