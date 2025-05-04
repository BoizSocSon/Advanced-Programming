#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>

#define DIRECTORY_PATH "." // Change this to the desired directory

// Function to handle Ctrl+C signal (SIGINT)
void handle_sigint(int sig) {
    printf("\nProgram is terminated by user\n");
    exit(0);
}

// Function to list files in a directory
void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }

    printf("\nFiles in directory: %s\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    // Register signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);

    while (1) { // Infinite loop, runs until Ctrl+C is pressed
        list_files(DIRECTORY_PATH);
        sleep(60); // Wait for 1 minute
    }

    return 0;
}

