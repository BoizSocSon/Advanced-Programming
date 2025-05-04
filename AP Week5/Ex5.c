#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THRESHOLD 100  // Threshold for switching to sequential sort
#define MAX_SIZE 10000

typedef struct {
    int* array;
    int low;
    int high;
} SortParams;

// Function prototypes
void* quicksort_thread(void* arg);
void quicksort_sequential(int* array, int low, int high);
int partition(int* array, int low, int high);
void swap(int* a, int* b);

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void quicksort_sequential(int* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quicksort_sequential(array, low, pi - 1);
        quicksort_sequential(array, pi + 1, high);
    }
}

void* quicksort_thread(void* arg) {
    SortParams* params = (SortParams*)arg;
    int low = params->low;
    int high = params->high;
    int* array = params->array;

    if (high - low <= THRESHOLD) {
        quicksort_sequential(array, low, high);
    } else {
        int pi = partition(array, low, high);

        pthread_t left_thread, right_thread;
        SortParams left_params = {array, low, pi - 1};
        SortParams right_params = {array, pi + 1, high};

        pthread_create(&left_thread, NULL, quicksort_thread, &left_params);
        pthread_create(&right_thread, NULL, quicksort_thread, &right_params);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }

    free(arg);
    return NULL;
}

void parallel_quicksort(int* array, int size) {
    SortParams* params = malloc(sizeof(SortParams));
    params->array = array;
    params->low = 0;
    params->high = size - 1;

    quicksort_thread(params);
}

int main() {
    int size;
    printf("Enter the size of array (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size <= 0 || size > MAX_SIZE) {
        printf("Invalid size!\n");
        return 1;
    }

    int* array = malloc(size * sizeof(int));
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    printf("\nOriginal array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    parallel_quicksort(array, size);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}