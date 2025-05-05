#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define producersnum 2
#define consumersnum 2
#define itemsperproducer 5
#define buffersize 3

pthread_mutex_t mutex;
sem_t empty,full;
int itemid=0;
int buffer[buffersize];
int in = 0, out = 0;
void *prod(void *arg)
{
    int item;
  int threadid=*((int*)arg);
  for (int i = 0; i < itemsperproducer; i++)
  {
     pthread_mutex_lock(&mutex);
     item=++itemid;
     pthread_mutex_unlock(&mutex);
     sem_wait(&empty);
     pthread_mutex_lock(&mutex);
     
     buffer[in]=item;
     printf("Producer %d produced item %d at index %d\n", threadid, item, in);
     in=(in+1)%buffersize;
     pthread_mutex_unlock(&mutex);
     sem_post(&full);
  }
  pthread_exit(NULL);
  
}

void *cons(void *arg)
{
    int n=(itemsperproducer*producersnum)/consumersnum;
    int itemout;
    int threadid=*((int*)arg);
    for(int i=0;i<n;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        itemout=buffer[out];
        printf("Consumer %d consumed item %d from index %d\n", threadid, itemout, out);
        out=(out+1)%buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t consumer[consumersnum],producer[producersnum];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty, 0, buffersize);
    sem_init(&full, 0, 0);

    for(int i=0;i<producersnum;i++)
    {
        pthread_create(&producer[i],NULL,prod,&i);
    }
    for(int i=0;i<consumersnum;i++)
    {
        pthread_create(&consumer[i],NULL,cons,&i);
    }
    for(int i=0;i<producersnum;i++)
    {
        pthread_join(producer[i],NULL);
    }
    for(int i=0;i<consumersnum;i++)
    {
        pthread_join(consumer[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
