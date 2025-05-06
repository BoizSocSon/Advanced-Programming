//23020845 Hoàng Nhật Nam

// 4.1 Write a C program that creates a thread to: 
// Compute the sum of of squares from 1 to N (N is entered by the user). 
// Return the result to the main thread, which prints the result.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int N;
    int sum_squares;
} ThreadData;

void *compute_sum_squares(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->sum_squares = 0;
    for (int i = 1; i <= data->N; i++) {
        data->sum_squares += i * i;
    }
    return NULL;
}

int main(){
    int N;
    printf("Enter the value of N: ");
    scanf("%d", &N);

    ThreadData data = {N, 0};
    pthread_t thread;
    pthread_create(&thread, NULL, compute_sum_squares, &data);
    pthread_join(thread, NULL);

    printf("Sum of squares from 1 to %d: %d\n", N, data.sum_squares);
    return 0;
}