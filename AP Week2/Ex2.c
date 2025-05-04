#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10 // Maximum number of arguments to search in

// Function to search for a string in an array of strings
int searchString(char **arr, int rows, const char *target) {
    for (int i = 0; i < rows; i++) {
        if (strcmp(arr[i], target) == 0) {
            return i;  // Return the index where the string is found
        }
    }
    return -1;  // Return -1 if not found
}

int main(int argc, char **argv) {
    char buf[512];  // Buffer to hold data read from the file
    int fd;         // File descriptor
    int nbytes;     // Number of bytes read

    // Try to open the file
    fd = open("Newfile.txt", O_RDWR | O_CREAT | O_APPEND, 0775);
    if (fd < 0) {
        perror("open failed");
        return EXIT_FAILURE;
    }

    // Search for "1" and "2" in command-line arguments
    if (searchString(argv, argc, "1") >= 0) {
        printf("Please enter the contents to be saved in the file:\n");
        char input_string[100];
        fgets(input_string, sizeof(input_string), stdin);
        
        // Move file pointer to the beginning before writing
        lseek(fd, 0, SEEK_SET);
        
        // Write the user input to the file
        write(fd, input_string, strlen(input_string));
        printf("Content written to file successfully.\n");

    } else if (searchString(argv, argc, "2") >= 0) {
        printf("2 found in command-line arguments\n");
		char path[100];
		printf("Enter the file path to be copied:\n");
		fgets(path, 100, stdin);
		path[strcspn(path, "\n")] = '\0';
		printf("%s", path);
		int fd2 = open(path, O_RDONLY);
		nbytes = read(fd2, buf, sizeof(buf) - 1);
		if (nbytes > 0) {
			buf[nbytes] = '\0';  // Null-terminate the buffer
			printf("File content: %s\n", buf);
		} else {
			printf("File is empty or read error occurred\n");
			close(fd2);
			exit(EXIT_FAILURE);
		}

		lseek(fd, 0 , SEEK_SET);
		write(fd, buf, strlen(buf));
        printf("Content written to file successfully.\n");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
