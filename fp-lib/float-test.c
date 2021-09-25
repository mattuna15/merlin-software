#include <stdio.h>
#include "ieee754.h"
#include <math.h>

extern volatile uint32_t *fpu_res1;
extern volatile uint32_t *fpu_res2;

int main(void)
{

    
    for (int i=1; i<5; i++) {

        double s =  (i/2.345) + (i*2.345);

        printf("\r\ns= %.3f",s);
        printf("\r\n");

    }
    

    printf("\r\n");
}
