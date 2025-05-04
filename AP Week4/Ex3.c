#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* printMessage(void* threadID) {
    long tid = (long)threadID;
    printf("Thread %ld is running.\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    printf("Main thread is running\n");
    
    for (long i = 0; i < 3; i++) {
        int rc = pthread_create(&threads[i], NULL, printMessage, (void*)i);
        if (rc) {
            fprintf(stderr, "Error: Unable to create thread %ld\n", i);
            return 1;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("All threads have finished.\n");
    return 0;
}
