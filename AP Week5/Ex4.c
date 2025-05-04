#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4  // Matrix size NxN

int matrixA[N][N];
int matrixB[N][N];
int matrixC[N][N];

// Structure to pass data to threads
typedef struct {
    int row;
} ThreadData;

// Thread function to multiply one row
void* multiply_row(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    
    for (int j = 0; j < N; j++) {
        matrixC[row][j] = 0;
        for (int k = 0; k < N; k++) {
            matrixC[row][j] += matrixA[row][k] * matrixB[k][j];
        }
    }
    
    free(arg);
    pthread_exit(NULL);
}

// Function to initialize matrices with random values
void initialize_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }
}

// Function to print a matrix
void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    } 
}

int main() {
    pthread_t threads[N];
    
    // Initialize matrices with random values
    initialize_matrices();
    
    printf("Matrix A:\n");
    print_matrix(matrixA);
    printf("\nMatrix B:\n");
    print_matrix(matrixB);
    
    // Create threads for matrix multiplication
    for (int i = 0; i < N; i++) {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        data->row = i;
        
        if (pthread_create(&threads[i], NULL, multiply_row, (void*)data) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nResulting Matrix C = A * B:\n");
    print_matrix(matrixC);
    
    return 0;
}