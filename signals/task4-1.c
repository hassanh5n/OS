#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct 
{
 int *array;
 int size;
}threaddata;

void *average(void  *arg)
{
    int sum=0;
    threaddata *td=(threaddata*)arg;
    for (int i = 0; i < td->size; i++)
    {
        sum+=td->array[i];
    }
    int n=td->size;
    float avg;
    avg=(float)sum/n;
    printf("Average:%f\n",avg);
    
}



int main(int argc,char *argv[])
{
    int n;
    n=argc-1;
    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        array[i]=atoi(argv[i+1]);
    }
    threaddata th={array,n};
    
    pthread_t minit,maxt,avgt;
    
    pthread_create(&avgt,NULL,average,&th);
    pthread_join(avgt,NULL);
    return 0;
    
}