#include <stdio.h>
#include <pthread.h>

// Structure to hold the input number and the result
typedef struct {
    int n;
    int sum;
} SumData;

// Function to compute the sum of numbers from 1 to N
void* compute_sum(void* arg) {
    SumData* data = (SumData*)arg;
    data->sum = 0;
    
    // Calculate the sum of numbers from 1 to N
    for (int i = 1; i <= data->n; i++) {
        data->sum += i;
    }
    
    return NULL;
}

int main() {
    int N;
    
    // Get user input for N
    printf("Enter a number (N): ");
    scanf("%d", &N);
    
    // Create a structure to hold the input number and the result
    SumData data;
    data.n = N;
    
    pthread_t thread;  // Declare thread variable
    
    // Create a thread to compute the sum
    if (pthread_create(&thread, NULL, compute_sum, &data) != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    
    // Print the sum result after the thread has completed
    printf("The sum of numbers from 1 to %d is: %d\n", data.n, data.sum);
    
    return 0;
}
