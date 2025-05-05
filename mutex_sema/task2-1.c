#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define STRING_LENGTH 60

pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
sem_t mutex, rw_mutex;
int readers_count = 0;
FILE *file;

// Generate a random lowercase character
char generateRandomChar() {
    return (char)('a' + rand() % 26);
}

// Reader thread function
void *reader(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        fseek(file, 0, SEEK_SET);
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fprintf(stdout, "Reader %ld: %s", (long)arg, buffer);
        }

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        usleep(1000);
    }
    pthread_exit(NULL);
}

// Writer thread function
void *writer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&rw_mutex);

        char randomString[STRING_LENGTH + 1];
        for (int j = 0; j < STRING_LENGTH; j++) {
            randomString[j] = generateRandomChar();
        }
        randomString[STRING_LENGTH] = '\0';

        fseek(file, 0, SEEK_END);
        fprintf(file, "%s\n", randomString);
        fprintf(stdout, "Writer %ld: %s\n", (long)arg, randomString);
        fflush(file);

        sem_post(&rw_mutex);

        usleep(1000);
    }
    pthread_exit(NULL);
}

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Open file
    file = fopen("text.txt", "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)(long)i);
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)(long)i);
    }

    // Join threads (not reachable unless loops are removed)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    fclose(file);

    return 0;
}

