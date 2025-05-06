//23020845 Hoàng Nhật Nam

// 2.1 Write a C program to: 
// Creates a file named Data.txt. 
// Reads content from the keyboard and writes it to the file. 
// 2.2 Extend your program to: 
// Read the content of Data.txt. 
// Write the content in reverse order to a new file named Data_reversed.txt.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void writingContents(){
    char buffer[1024];
    printf("Enter your contents: ");
    fgets(buffer, sizeof(buffer), stdin);
    int fd = open("Data.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(fd < 0){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    write(fd, buffer, strlen(buffer));
    close(fd);
}

void reversedContents(){
    char buffer[1024];
    int fd = open("Data.txt", O_RDONLY);
    if(fd < 0){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int bytes_read = read(fd, buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    char reversed[1024];
    int i = 0;
    for(i = bytes_read - 1; i >= 0; i--){
        reversed[i] = buffer[i];
    }
    int fdr = open("Data_reversed.txt", O_CREAT | O_APPEND | O_TRUNC | O_RDWR, 0644);
    if(fdr < 0){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    write(fdr, reversed, sizeof(reversed));
    close(fd);
    close(fdr);
    printf("Reversed content saved to Data_reversed.txt\n");

}

int main(){
    int options;
    printf("Enter options\n");
    scanf("%d", &options);
    getchar();
    if(options == 1){
        writingContents();
    } else if(options == 2){
        reversedContents();
    }
    return 0;
}


