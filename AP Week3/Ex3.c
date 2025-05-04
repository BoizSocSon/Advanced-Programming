#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) { 
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process executing ls command...\n");
        char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
            perror("getenv failed");
            exit(1);
        }
        execl("/bin/ls", "ls", home_dir, (char *) NULL);
        perror("execl failed"); // This executes only if execl fails
        exit(1);
    }
    else {
        // Parent process
        wait(NULL); // Wait for child process to complete
        printf("Parent process finished.\n");
    }

    return 0;
}
