#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHARED_MEM_SIZE 128
#define SHM_NAME "/my_shared_memory"

int main() {
    int shm_fd;
    char *shm_ptr;

    // Create a shared memory object
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory segment
    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory segment into the address space of the process
    shm_ptr = (char *)mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        printf("Child process writing to shared memory...\n");
        sprintf(shm_ptr, "Hello from the child process!");
        printf("Child process wrote: %s\n", shm_ptr);
    } else { // Parent process
        sleep(1); // Wait for child to write to shared memory
        printf("Parent process reading from shared memory...\n");
        printf("Parent process read: %s\n", shm_ptr);
    }

    // Unmap the shared memory segment
    if (munmap(shm_ptr, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close the shared memory object
    if (close(shm_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Unlink the shared memory object
    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
