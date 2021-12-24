#include <stdio.h>
#include "ieee754.h"
#include <math.h>

int main(void)
{
    double s;

    printf("\r\nFPU Test\r\n");
    for (int i=1; i<100; i++) {
        s = sqrt(i*2.345);
        printf("\r\n%d %.6f\r\n",i,s);
    }

    printf("\r\n");
}
