#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size 10000000

int main()
{
    float *A = (float*) malloc(size * sizeof(float));
    float *B = (float*) malloc(size * sizeof(float));
    float *C = (float*) malloc(size * sizeof(float));
   
    for(int i=0;i<size;i++)
    {
     A[i]=1.0f;
     B[i]=1.0f;
    }
    
    clock_t start=clock();
    
    for(int i=0;i<size;i++)
    {
     C[i]=A[i]+B[i];
    }
    clock_t end=clock();
    double time=(double)(end-start)/ CLOCKS_PER_SEC;
    printf("Total time taken is %.8f \n",time);
    free(A);
    free(B);
    free(C);
 


}
