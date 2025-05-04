#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int sharedVar = 5; // Shared among threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *threadFunc(void *arg) {
    //Write code change value ofglobal variable here   
    sharedVar+=10;
    return NULL;
}
int main() {
    pthread_t thread;      

    // Write code to create thread here
    pthread_create(&thread, NULL, threadFunc, NULL);
    pthread_join(thread, NULL);

    //Write code to wait for thread to terminate here
    printf("Main: sharedVar = %d\n", sharedVar);
    return 0;
}