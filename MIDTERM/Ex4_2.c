//23020845 Hoàng Nhật Nam

// 4.2 Write a program to simulate a shared bank account starting with a balance of $1000 
// Thread 1 deposits money into the account. 
// Thread 2 withdraws money from the account. 
// Each thread repeats this 5 times. 
// Afterthat, the main thread prints the final account balance.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int account_balance = 1000;

void* deposit(void* arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        printf("Thread %d depositing...\n", thread_id);
        account_balance += 100;
        printf("Thread %d deposited $100, new balance: %d\n", thread_id, account_balance);
    }

    pthread_exit(NULL);
}

void* withdraw(void* arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        printf("Thread %d withdrawing...\n", thread_id);
        if (account_balance >= 100) {
            account_balance -= 100;
            printf("Thread %d withdrew $100, new balance: %d\n", thread_id, account_balance);
        } else {
            printf("Thread %d attempted to withdraw but insufficient funds\n", thread_id);
        }
    }

    pthread_exit(NULL);
}


int main() {
    pthread_t thread1, thread2;
    int thread_ids[2] = {1, 2};
    int rc;

    rc = pthread_create(&thread1, NULL, deposit, (void*)&thread_ids[0]);
    if (rc) {
        printf("Error: Unable to create thread 1\n");
        exit(1);
    }
    rc = pthread_create(&thread2, NULL, withdraw, (void*)&thread_ids[1]);
    if (rc) {
        printf("Error: Unable to create thread 2\n");
        exit(1);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final account balance: %d\n", account_balance);

    return 0;
}