#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "/tmp/myfifo"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char message[BUFFER_SIZE];

    // Create the named pipe (FIFO)
    mkfifo(FIFO_NAME, 0666);

    // Open the named pipe for both reading and writing
    fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1) {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    // Producer: Write data to the named pipe
    printf("Enter message to write: ");
    fgets(message, BUFFER_SIZE, stdin);
    write(fd, message, strlen(message) + 1);

    // Consumer: Read data from the named pipe
    printf("Message received: ");
    read(fd, message, BUFFER_SIZE);
    printf("%s", message);

    // Close the file descriptor
    close(fd);

    // Remove the named pipe
    //unlink(FIFO_NAME);

    return 0;
}


