#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25

int main() {
    int fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        close(fd[0]); 

        char message[] = "Hello from parent!";
        write(fd[1], message, sizeof(message));  

        close(fd[1]); // Close the write end of the pipe

        wait(NULL); // Wait for the child process to finish
    } else {  
        close(fd[1]); // Close the unused write end of the pipe

       
        read(fd[0], buffer, BUFFER_SIZE);
        printf("Message from parent: %s\n", buffer);

        close(fd[0]); 
    }

    return 0;
}

