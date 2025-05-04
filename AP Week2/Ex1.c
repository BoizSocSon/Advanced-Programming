#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];

    // Create and write to the file
    fd = open("Hello.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    write(fd, "Hello! What is your name?", 25);  // Write content
    close(fd);

    // a) Read the full content of Hello.txt
    fd = open("Hello.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Error reading file");
        return 1;
    }
    buffer[bytes_read] = '\0';  // Null terminate the string
    printf("Full content: %s\n", buffer);
    close(fd);

    // b) Read from the 7th byte onward using lseek
    fd = open("Hello.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    lseek(fd, 6, SEEK_SET);  // Move to the 7th byte (index 6)
    
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Error reading file");
        return 1;
    }
    buffer[bytes_read] = '\0';
    printf("Content from 7th byte: %s\n", buffer);

    close(fd);
    return 0;
}
