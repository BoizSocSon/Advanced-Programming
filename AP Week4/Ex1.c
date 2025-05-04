#include <stdio.h>
#include <pthread.h>

// Function to print numbers from 1 to N
void* print_numbers(void* arg) {
    int n = *((int*)arg);  // Cast argument to int
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

int main() {
    int N;
    
    // Get user input for N
    printf("Enter a number (N): ");
    scanf("%d", &N);
    
    pthread_t thread;  // Declare thread variable
    
    // Create a thread to run the print_numbers function
    if (pthread_create(&thread, NULL, print_numbers, &N) != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    
    // After the thread finishes, print the message from the main thread
    printf("Main thread exiting.\n");
    
    return 0;
}
