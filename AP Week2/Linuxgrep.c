#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RESET "\033[0m"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./linuxgrep <word> <filename>\n", 38);
        return 1;
    }

    int fd = open(argv[2], O_RDONLY);
    if (fd == -1) { 
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    int bytes_read, line_pos = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || line_pos >= BUFFER_SIZE - 1) {
                line[line_pos] = '\0';
                char *match = strstr(line, argv[1]);
                if (match) {
                    char *ptr = line;
                    while ((match = strstr(ptr, argv[1])) != NULL) {
                        write(STDOUT_FILENO, ptr, match - ptr);
                        write(STDOUT_FILENO, COLOR_YELLOW, strlen(COLOR_YELLOW));
                        write(STDOUT_FILENO, argv[1], strlen(argv[1]));
                        write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
                        ptr = match + strlen(argv[1]);
                    }
                    write(STDOUT_FILENO, ptr, strlen(ptr));
                    write(STDOUT_FILENO, "\n", 1);
                }
                line_pos = 0;
            } else {
                line[line_pos++] = buffer[i];
            }
        }
        // printf("Line position %d\nByteread %d\n", line_pos, bytes_read);
    }

    close(fd);
    return 0;
}
