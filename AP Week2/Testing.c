#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int fd = open("Newfile.txt", O_RDWR | O_APPEND);
    if(fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *message = "Hello world!\n";
    ssize_t bytesWritten = write(fd, message, strlen(message));

    if(bytesWritten < 0){
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Wrote %zd bytes to Newfile.txt\n",bytesWritten );
    close(fd);

    return 0;
}