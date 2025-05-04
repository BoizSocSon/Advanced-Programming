#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <threads.h>
#include <pthread.h>

int gob_counters = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *IncreaseCounter(void *arg);
void *DecreaseCounter(void *arg);

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, IncreaseCounter, NULL);
    pthread_create(&thread2, NULL, DecreaseCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final Counter: %d\n", gob_counters);

    pthread_mutex_destroy(&lock);
    
    return 0;
}

void *IncreaseCounter(void *arg){
    pthread_mutex_lock(&lock);
    int loops = 100;
    while(loops >= 0){
        gob_counters++;
        // printf("Counter: %d\n", gob_counters);
        // sleep(1);
        loops--;
    }
    pthread_mutex_unlock(&lock);
}
void *DecreaseCounter(void *arg){
    pthread_mutex_lock(&lock);
    int loops = 50;
    while(loops >= 0){
        gob_counters--;
        // printf("Counter: %d\n", gob_counters);
        // sleep(1);
        loops--;
    }
    pthread_mutex_unlock(&lock);

}