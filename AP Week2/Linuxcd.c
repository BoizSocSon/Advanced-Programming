#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("chdir");
        return 1;
    }

    printf("Directory changed to: %s\n", argv[1]);

    return 0;
}
