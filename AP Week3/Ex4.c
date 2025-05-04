#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define CMDSIZ 128
#define MAXARGS 10

extern char **environ;

void process_command(char *cmdbuf);

int main(int argc, char *argv[]) {
    int logout = 0, cmdsiz;
    char cmdbuf[CMDSIZ];

    while (!logout) {
        write(1, "myshell> ", 9);
        cmdsiz = read(0, cmdbuf, CMDSIZ);
        
        if (cmdsiz <= 0) continue; // Handle EOF or read error
        cmdbuf[cmdsiz - 1] = '\0'; // Remove newline character
        printf("%s\n", cmdbuf);
        if (strcmp("logout", cmdbuf) == 0)
            logout = 1;
        else
            process_command(cmdbuf);
    }

    return 0;
}

void process_command(char *cmdbuf) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) { // Child process
        char *args[MAXARGS];
        int i = 0;

        // Tokenize command input
        char *token = strtok(cmdbuf, " ");
        while (token != NULL && i < MAXARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Execute command
        execvp(args[0], args);
        perror("Execution failed"); // If execvp fails
        exit(1);
    }
    else { // Parent process
        wait(NULL); // Wait for child to finish
    }
}
