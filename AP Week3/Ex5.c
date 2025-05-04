#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> // Required for wait()

#define MSG_SIZE 32

int main() {
    int pipe1[2], pipe2[2]; // Two pipes: pipe1 (child -> parent), pipe2 (parent -> child)
    pid_t pid;
    char parent_msg[] = "Hello children";
    char child_msg[] = "Hello parent";
    char buffer[MSG_SIZE];

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    // Fork process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        // Send message to parent
        if (write(pipe1[1], child_msg, strlen(child_msg) + 1) == -1) {
            perror("Write to pipe1 failed");
            exit(1);
        }
        close(pipe1[1]); // Close write end after sending

        // Read message from parent
        memset(buffer, 0, MSG_SIZE);
        if (read(pipe2[0], buffer, MSG_SIZE) == -1) {
            perror("Read from pipe2 failed");
            exit(1);
        }
        printf("Child received: %s\n", buffer);
        close(pipe2[0]); // Close read end

    } else {  // Parent process
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2

        // Read message from child
        memset(buffer, 0, MSG_SIZE);
        if (read(pipe1[0], buffer, MSG_SIZE) == -1) {
            perror("Read from pipe1 failed");
            exit(1);
        }
        printf("Parent received: %s\n", buffer);
        close(pipe1[0]); // Close read end

        // Send message to child
        if (write(pipe2[1], parent_msg, strlen(parent_msg) + 1) == -1) {
            perror("Write to pipe2 failed");
            exit(1);
        }
        close(pipe2[1]); // Close write end

        // Wait for child to finish
        wait(NULL);
    }

    return 0;
}
