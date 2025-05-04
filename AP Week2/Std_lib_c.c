// #include <stdio.h>
// #include <stdlib.h>

// #define BUFFER_SIZE 1024

// void write_from_keyboard(const char *filename) {
//     FILE *file = fopen(filename, "w");
//     if (!file) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE);
//     }

//     char buffer[BUFFER_SIZE];
//     printf("Enter file content (Press Ctrl+D to save and exit):\n");
//     while (fgets(buffer, BUFFER_SIZE, stdin)) {
//         fputs(buffer, file);
//     }

//     fclose(file);
// }

// void copy_from_file(const char *source, const char *destination) {
//     FILE *src = fopen(source, "r");
//     if (!src) {
//         perror("Error opening source file");
//         exit(EXIT_FAILURE);
//     }

//     FILE *dest = fopen(destination, "w");
//     if (!dest) {
//         perror("Error opening destination file");
//         fclose(src);
//         exit(EXIT_FAILURE);
//     }

//     char buffer[BUFFER_SIZE];
//     size_t bytes;
//     while ((bytes = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
//         fwrite(buffer, 1, bytes, dest);
//     }

//     fclose(src);
//     fclose(dest);
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
#include <string.h>

#define FILE_NAME "Hello.txt"
#define CONTENT_SIZE 10000000  // 10 million characters

void write_to_file() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(CONTENT_SIZE);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    memset(buffer, 'A', CONTENT_SIZE);  // Fill buffer with 'A'
    fwrite(buffer, 1, CONTENT_SIZE, file);  // Write all at once

    free(buffer);
    fclose(file);
}

int main() {
    write_to_file();
    printf("File '%s' has been created with %d characters.\n", FILE_NAME, CONTENT_SIZE);
    return 0;
}
