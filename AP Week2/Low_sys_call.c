// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <unistd.h>

// #define BUFFER_SIZE 1024

// void write_from_keyboard(const char *filename) {
//     int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE);
//     }

//     char buffer[BUFFER_SIZE];
//     printf("Enter file content (Press Ctrl+D to save and exit):\n");
//     ssize_t bytes_read;
//     while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
//         write(fd, buffer, bytes_read);
//     }

//     close(fd);
// }

// void copy_from_file(const char *source, const char *destination) {
//     int src_fd = open(source, O_RDONLY);
//     if (src_fd < 0) {
//         perror("Error opening source file");
//         exit(EXIT_FAILURE);
//     }

//     int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (dest_fd < 0) {
//         perror("Error opening destination file");
//         close(src_fd);
//         exit(EXIT_FAILURE);
//     }

//     char buffer[BUFFER_SIZE];
//     ssize_t bytes_read;
//     while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
//         write(dest_fd, buffer, bytes_read);
//     }

//     close(src_fd);
//     close(dest_fd);
// }

// int main() {
//     int choice;
//     char filename[100], sourcefile[100];

//     printf("Select an option:\n1. Write from keyboard\n2. Copy from another file\nChoice: ");
//     scanf("%d", &choice);
//     getchar(); // Consume newline left by scanf

//     printf("Enter the filename: ");
//     scanf("%s", filename);

//     if (choice == 1) {
//         write_from_keyboard(filename);
//     } else if (choice == 2) {
//         printf("Enter source file: ");
//         scanf("%s", sourcefile);
//         copy_from_file(sourcefile, filename);
//     } else {
//         printf("Invalid choice.\n");
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "Hello.txt"
#define CONTENT_SIZE 10000000  // 10 million characters

void write_to_file() {
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(CONTENT_SIZE);
    if (!buffer) {
        perror("Memory allocation failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    memset(buffer, 'A', CONTENT_SIZE);  // Fill buffer with 'A'
    write(fd, buffer, CONTENT_SIZE);    // Write all at once

    free(buffer);
    close(fd);
}

int main() {
    write_to_file();
    printf("File '%s' has been created with %d characters.\n", FILE_NAME, CONTENT_SIZE);
    return 0;
}
