
extern int  __bss_start__   ;
extern int  __bss_end__     ;


extern void _kmain( unsigned int r0, unsigned int r1, unsigned int atags );

void 
_cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
{
    int* bss        = &__bss_start__;
    int* bss_end    = &__bss_end__  ;
    
    /* BSS Section initialization */
    while( bss < bss_end )
    {
        *bss++ = 0;
    }
    
    _kmain( r0, r1, r2 );
    
    while(1)
    {
        /* TRAP */
    }
}