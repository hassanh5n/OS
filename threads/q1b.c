#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define size 10000000
#define threadcount 10

float *A,*B,*C;

typedef struct
{
 int start;
 int end;

}threadData;

void* arraycal (void *args)
{
 threadData *t=(threadData*)args;
 for(int i=t->start;i<t->end;i++)
 {
  C[i]=A[i]+B[i];
 }
 return NULL;

}

int main()
{
     A = (float*) malloc(size * sizeof(float));
     B = (float*) malloc(size * sizeof(float));
     C = (float*) malloc(size * sizeof(float));
   
    for(int i=0;i<size;i++)
    {
     A[i]=1.0f;
     B[i]=1.0f;
    }
    
   pthread_t threads[threadcount];
   threadData th[threadcount];
   
   int chunks=(size/threadcount);
   clock_t start=clock();
   
   for(int i=0;i<threadcount;i++)
   {
    th[i].start=i*chunks;
    th[i].end=(i+1)*chunks;
    pthread_create(&threads[i],NULL,arraycal,&th[i]);
   
   } 
   for(int i=0;i<threadcount;i++)
   {
    pthread_join(threads[i],NULL);
   }
  
   
   clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Parallel execution time: %.6f seconds\n", time_taken);
    free(A);
    free(B);
    free(C);

    return 0;
 }
