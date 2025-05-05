#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define numsreader 5
#define numswriter 2

int item = 0;
int readercount = 0;
sem_t mutex, rwmutex;
FILE *fp;

void *reader_thread(void *arg) {
    int id = *((int *)arg);
    for (int i = 0; i < 5; i++) {
        sem_wait(&mutex);
        readercount++;
        if (readercount == 1) {
            sem_wait(&rwmutex);  
        }
        sem_post(&mutex);

        
        fseek(fp, 0, SEEK_SET);
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("Reader %d: %s", id, buffer);
        }

        sem_wait(&mutex);
        readercount--;
        if (readercount == 0) {
            sem_post(&rwmutex);  
        }
        sem_post(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void *writer_thread(void *arg) {
    int id = *((int *)arg);
    for (int i = 0; i < 5; i++) {
        sem_wait(&rwmutex);
        item++;
        fseek(fp, 0, SEEK_END); 
        fprintf(fp, "Writer %d wrote: %d\n", id, item);
        printf("Writer %d wrote: %d\n", id, item);
        fflush(fp);
        sem_post(&rwmutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[numsreader], writers[numswriter];
    int reader_ids[numsreader], writer_ids[numswriter];

    sem_init(&mutex, 0, 1);
    sem_init(&rwmutex, 0, 1);

    fp = fopen("text.txt", "a+");
    if (fp == NULL) {
        perror("File opening failed");
        return 1;
    }

    for (int i = 0; i < numswriter; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer_thread, &writer_ids[i]);
    }
    for (int i = 0; i < numsreader; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader_thread, &reader_ids[i]);
    }

    for (int i = 0; i < numsreader; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < numswriter; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rwmutex);
    fclose(fp);

    return 0;
}


