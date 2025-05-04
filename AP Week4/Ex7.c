#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

int buffer[BUFFER_SIZE]; // Shared buffer
int count = 0; // Number of elements in buffer

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER; // Condition for producer
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER; // Condition for consumer

void *producer(void *arg);
void *consumer(void *arg);

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to finish (not actually needed in an infinite loop)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}

void *producer(void *arg) {
    int num = 1;

    while (1) {
        pthread_mutex_lock(&lock);

        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &lock);
        }

        // Add number to buffer
        buffer[count] = num;
        printf("Produced: %d\n", num);
        num++;
        count++;

        // Signal consumer that data is available
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&lock);

        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);

        // Wait if the buffer is empty
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &lock);
        }

        // Remove number from buffer
        int num = buffer[count - 1];
        printf("Consumed: %d\n", num);
        count--;

        // Signal producer that space is available
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&lock);

        sleep(2); // Simulate time taken to consume an item
    }
    return NULL;
}

