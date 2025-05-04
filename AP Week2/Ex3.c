#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct stat sb;
    if (stat("Ex2.c", &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("File size: %lld bytes\n", (long long) sb.st_size);
    printf("Access mode of the file %d\n", sb.st_mode);
    return 0;
}