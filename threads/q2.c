#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

float average;
float sum,maximum;

typedef struct
{
int *numbers;
int count;
}threadData;

void* arraysum(void *args)
{
 threadData *t=(threadData*)args;
 for(int i=0;i<t->count;i++)
 {
 sum+=t->numbers[i];
 }
return NULL;
}

void* arraymax(void *args)
{  
   threadData *t=(threadData*)args;
   maximum=t->numbers[0];
   for (int i = 0; i < t->count; i++) {
        if (t->numbers[i] > maximum) {
            maximum = t->numbers[i];
        }
    }
    
    return NULL;
}

void* arraysavg(void *args)
{
 threadData *t=(threadData*)args;
 for(int i=0;i<t->count;i++)
 {
 sum+=t->numbers[i];
 }
 
return NULL;
}
