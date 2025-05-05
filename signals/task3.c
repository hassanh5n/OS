#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 100000

int global_array[ARRAY_SIZE];         
sem_t semaphore;                    
volatile sig_atomic_t exit_critical = 0;
void alarm_handler(int signum) {
    exit_critical = 1;               
}
void initialize_array() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        global_array[i] = rand() % 1000;
    }
}
void* sum_array(void* arg) {
    int thread_id = *(int*)arg;
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    int sum = 0;
    sem_wait(&semaphore);               
    printf("Thread %d entered critical section.\n", thread_id);
    signal(SIGALRM, alarm_handler);       
    alarm(5);                              
    while (!exit_critical) {
        pause(); 
    }
    for (int i = start; i < end; ++i) {
        sum += global_array[i];
    }
    printf("Thread %d exiting critical section.\n", thread_id);
    sem_post(&semaphore);                 
    return (void*)(long)sum;
}
int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    void* thread_results[NUM_THREADS];
    long total_sum = 0;
    initialize_array();
    sem_init(&semaphore, 0, 1);  
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, sum_array, &thread_args[i]);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &thread_results[i]);
        total_sum += (long)thread_results[i];
    }
    printf("Total sum of array elements: %ld\n", total_sum);
    sem_destroy(&semaphore);
    return 0;
}

