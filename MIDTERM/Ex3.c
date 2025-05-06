//23020845 Hoàng Nhật Nam
// 3.1 Write a program that creates a child process, where the parent process waits until the child finishes before continuing. 
// 3.2 Write a C program that: 
// The child process calculates the sum of numbers from 1 to N (user input) and sends this result (sum1) to the parent. 
// -The parent process calculates the sum from N+1 to M (sum2) (M is user input, M > N). 
// The parent then calculates the total sum from 1 to M using suml and sum2.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

void Function1(){
    pid_t pid = fork();
    if(pid == 0){
        int number = 0;
        for(int i = 0; i < 100; i++){
            number += i;
        }
        printf("%d\n", number);
    } else {
        wait(NULL);
        printf("Parent process finished\n");
    }
}

// Funtion 2
void Function2(){
    int fd[2];
    int N, M;
    printf("Enter N and M: ");
    scanf("%d %d", &N, &M);
    if(pipe(fd) == -1){
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if(pid == 0){
        close(fd[0]);
        int sum1 = 0;
        for(int i = 1; i <= N; i++){
            sum1 += i;
        }
        write(fd[1], &sum1, sizeof(sum1));
        close(fd[1]);
    } else {
        wait(NULL);
        close(fd[1]);
        int sum1;
        int sum2 = 0;
        read(fd[0], &sum1, sizeof(sum1));
        printf("sum1 value: %d\n", sum1);
        for(int i = N + 1; i <= M; i++){
            sum2 += i;
        }
        printf("sum2 value: %d\n", sum2);
        int sum3 = sum1 + sum2;
        printf("Sum from 1 to %d = %d\n", M, sum3);
        printf("Parent process finished\n");
    }
}

int main(){
    int options;
    printf("Enter options\n");
    scanf("%d", &options);
    getchar();
    if(options == 1){
        Function1();
    } else if(options == 2){
        Function2();
    }
    return 0;
}