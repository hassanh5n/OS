#include <stdio.h>
#include "dollar.h"
#include "converter1.h"

int main()
{
    int result1=pkrtodollar(500);
    int result2=dollartopkr(500);
    printf("%d \n",result1);
    printf("%d \n",result2);


}