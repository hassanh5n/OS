#include <stdio.h>
#include <pthread.h>

#define Numsthread 2

int sharedcount=0;
pthread_mutex_t mutex;
void *func(void *arg)
{
 int threadid=(*(int*)arg);
 pthread_mutex_lock(&mutex);
 for(int i=0;i<1000;i++)
 {
  sharedcount++;
 }
 pthread_mutex_unlock(&mutex);
 printf("thread id %d = %d\n",threadid,sharedcount);
}

int main()
{
pthread_t threads[Numsthread];
pthread_mutex_init(&mutex,NULL);
for(int i=0;i<2;i++)
{
 pthread_create(&threads[i],NULL,func,&i);
}
for(int i=0;i<2;i++)
{
 pthread_join(threads[i],NULL);
}
pthread_mutex_destroy(&mutex);
printf("Total = %d\n",sharedcount);
return 0;

}
