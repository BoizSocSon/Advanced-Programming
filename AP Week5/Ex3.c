#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000
#define MAX_STRING_LENGTH 100

// Shared variables
char** strings;
char target[MAX_STRING_LENGTH];
int found_index = -1;
bool found_flag = false;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Structure to pass arguments to threads
typedef struct {
    int start_index;
    int end_index;
    int thread_id;
} ThreadArgs;

void* search_strings(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    for (int i = args->start_index; i < args->end_index && !found_flag; i++) {
        if (strcmp(strings[i], target) == 0) {
            pthread_mutex_lock(&mutex);
            if (!found_flag) {  // Check again after acquiring lock
                found_flag = true;
                found_index = i;
                printf("Thread %d found target at index %d\n", args->thread_id, i);
            }
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    
    return NULL;
}

int main() {
    // Initialize array of strings
    strings = (char**)malloc(ARRAY_SIZE * sizeof(char*));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        strings[i] = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
        sprintf(strings[i], "string%d", i);  // Generate sample strings
    }
    
    // Set target string (for testing, we'll search for "string500")
    strcpy(target, "string500");
    
    // Create threads
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].start_index = i * chunk_size;
        thread_args[i].end_index = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
        thread_args[i].thread_id = i;
        
        pthread_create(&threads[i], NULL, search_strings, &thread_args[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Print result
    if (found_flag) {
        printf("Target string found at index: %d\n", found_index);
    } else {
        printf("Target string not found\n");
    }
    
    // Cleanup
    for (int i = 0; i < ARRAY_SIZE; i++) {
        free(strings[i]);
    }
    free(strings);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}