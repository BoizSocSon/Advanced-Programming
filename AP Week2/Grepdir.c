#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RESET "\033[0m"

int search_in_file(const char *filename, const char *word) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) return 0;

    char buffer[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    int bytes_read, line_pos = 0;
    int found = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || line_pos >= BUFFER_SIZE - 1) {
                line[line_pos] = '\0';
                if (strstr(line, word)) {
                    found = 1;
                    break;
                }
                line_pos = 0;
            } else {
                line[line_pos++] = buffer[i];
            }
        }
    }

    close(fd);
    return found;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./grepdir <word> <directory>\n", 37);
        return 1;
    }

    DIR *dir = opendir(argv[2]);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular files only
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s/%s", argv[2], entry->d_name);

            if (search_in_file(filepath, argv[1])) {
                write(STDOUT_FILENO, COLOR_YELLOW, strlen(COLOR_YELLOW));
                write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
                write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
                write(STDOUT_FILENO, "\n", 1);
            }
        }
    }

    closedir(dir);
    return 0;
}