#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<error.h>

static int glob = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *threadFunc(void *arg){
    int loops = *((int*)arg);
    int loc,j,s;
    for(j=0; j<loops; j++){
        s = pthread_mutex_lock(&mutex);
        if(s != 0){
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        loc = glob;
        glob++;
        // printf("Thread %d, local = %d, global = %d\n", (int)pthread_self(), loc, glob);
        s = pthread_mutex_unlock(&mutex);
        if(s != 0){
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }
}


int main(int argc, char *argv[]){
    int numThreads = 4, loops = 100000;
    pthread_t threads[numThreads];
    int rc, i;
    if(argc > 1)
        numThreads = atoi(argv[1]);
    if(argc > 2)
        loops = atoi(argv[2]);

    for(i=0; i<numThreads; i++){
        rc = pthread_create(&threads[i], NULL, threadFunc, (void*)&loops);
        if(rc){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for(i=0; i<numThreads; i++){
        rc = pthread_join(threads[i], NULL);
        if(rc){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("Final value of global = %d\n", glob);

    return 0;
}
