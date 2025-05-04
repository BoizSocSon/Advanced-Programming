#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// # BUFFERSIZE 100 
static int idata = 1000; //Alocated in data segment

void main(){
    int istack = 150; //Alocated in stack segment
    int fd = open("Hello.txt", O_RDWR);
    if(fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    } 

    pid_t childPid;
    switch(childPid = fork()){
        case -1:
            printf("Error when creating child process\n");
        case 0:
            printf("The value of idata is: %d, The value of istack is: %d\n", idata, istack);
            idata = 500;
            istack = 75;

            printf("The new value of idata is: %d, The new value of istack is: %d\n", idata, istack);
            lseek(fd, 6, SEEK_SET);
            break;
        default:
            wait(NULL);
            printf("The value of idata is: %d, The value of istack is: %d\n", idata, istack);
            char buffer[512];
            ssize_t bytesRead = read(fd, buffer, sizeof(buffer)-1);
            if(bytesRead < 0){
                perror("read");
                close(fd);
                exit(EXIT_FAILURE);
            }
            buffer[bytesRead] = '\0';
            printf("Read %zd bytes:\n %s\n", bytesRead, buffer);
            break;
    }
    close(fd);
}
