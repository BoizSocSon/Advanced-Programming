#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // File descriptors for the pipe
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Fork process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process: Executes "ls"
        close(pipefd[0]); // Close unused read end of pipe

        // Redirect stdout to pipe's write end
        dup2(pipefd[1], STDOUT_FILENO);
        
        close(pipefd[1]); // Close original write end

        execlp("ls", "ls", NULL); // Execute "ls"
        perror("Exec ls failed");
        exit(1);
    } else {  // Parent process: Executes "wc -l"
        close(pipefd[1]); // Close unused write end of pipe

        // Redirect stdin to pipe's read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Close original read end

        execlp("wc", "wc", "-l", NULL); // Execute "wc -l"
        perror("Exec wc failed");
        exit(1);
    }

    return 0;
}
