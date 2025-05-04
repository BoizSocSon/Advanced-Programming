#include <stdio.h>
#include <pthread.h>

#define RANGE_START 1
#define RANGE_END 10000000
#define NUM_THREADS 8

typedef struct {
    int start;
    int end;
    int count;
} ThreadData;

void* count_odds(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->count = 0;

    for (int i = data->start; i <= data->end; i++) {
        if (i % 2 != 0) {
            data->count++;
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int range_size = (RANGE_END - RANGE_START + 1) / NUM_THREADS;
    int total_count = 0;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = RANGE_START + i * range_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? RANGE_END : thread_data[i].start + range_size - 1;

        pthread_create(&threads[i], NULL, count_odds, &thread_data[i]);
    }

    // Join threads and sum results
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_count += thread_data[i].count;
    }

    printf("Total odd numbers in range [%d, %d]: %d\n", RANGE_START, RANGE_END, total_count);
    return 0;
}
