#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
    pid_t childPid = fork();
    if(childPid == 0){
        printf("Child process executing ls command...\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process finished.\n");
    }
}