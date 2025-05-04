#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./linuxecho <string> <filename>\n", 40);
        return 1;
    }

    int fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    write(fd, argv[1], strlen(argv[1]));
    write(fd, "\n", 1);
    close(fd);

    return 0;
}
