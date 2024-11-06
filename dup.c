#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 100

int main() {
    // Open Sample.txt in append mode
    int fd_old = open("Sample.txt",O_WRONLY |O_APPEND| O_CREAT);
    if (fd_old < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Duplicate the file descriptor
    int fd_new = dup(fd_old);
    if (fd_new < 0) {
        perror("Failed to duplicate file descriptor");
        return 1;
    }

    // Close the old file descriptor
    close(fd_old);

    // Read input from console (fd = 0 is standard input)
    char buffer[MAX_INPUT_SIZE];
    int i = 0;
    char ch;
    
    printf("Enter input (ends with $):\n");

    // Read characters until we encounter '$'
    // read(fd_old, &ch, 1) ;
    while (read(1, &ch, 1) && ch != '$') {
        // printf("%d\n" , )  ;
        // buffer[i++] = ch;
        write(fd_new, &ch, 1);
    }
    // buffer[i] = '\0'; // Null-terminate the string

    // Write the captured input to the file
    // if ( < 0) {
    //     perror("Failed to write to file");
    // }
    
    // Close the new file descriptor
    close(fd_new);

    return 0;
}
