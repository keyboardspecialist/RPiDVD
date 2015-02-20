#include "debug.h"

volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

volatile unsigned int tim;

void
_flash_brk(void)
{
    gpio[GPIO_GPFSEL4] |= (1 << 21);
    /* Never exit as there is no OS to exit to! */
    while(1)
    {

        /* Set the GPIO16 output high ( Turn OK LED off )*/
        gpio[GPIO_GPSET1] = (1 << 15);

        for(tim = 0; tim < 500000; tim++)
            ;

        /* Set the GPIO16 output low ( Turn OK LED on )*/
        gpio[GPIO_GPCLR1] = (1 << 15);

        for(tim = 0; tim < 500000; tim++)
            ;

        /* Set the GPIO16 output high ( Turn OK LED off )*/
        gpio[GPIO_GPSET1] = (1 << 15);
    }
}