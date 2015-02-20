#include "mailbox.h"
#include "debug.h"

static volatile uint32_t* sv_mailbox_base      = (uint32_t *)MAILBOX_BASE;
static volatile uint32_t* sv_mailbox_status    = (uint32_t *)MAILBOX_STATUS;
static volatile uint32_t* sv_mailbox_write     = (uint32_t *)MAILBOX_WRITE;

void
mailbox_read( uint32_t channel, uint32_t* data )
{
    if( channel > 0xF )
        return; //TODO: emit error

    while( 1 )
    {
        if( (*sv_mailbox_status & MAILBOX_EMPTY) == 0 )
        {
            uint32_t mail       = *sv_mailbox_base;
            uint32_t chanrecv   = mail & 0xF;
            
            if( chanrecv == channel )
            {
                *data = mail & 0xFFFFFFF0;
                break;
            }
        }
    }
}

void
mailbox_write( uint32_t channel, uint32_t data )
{
    //data must be aligned 16
    if( data & 0xF )
        return; //TODO: emit error
        
    if( channel > 0xF )
        return; //TODO: emit error

    while( 1 )
    {
        if( (*sv_mailbox_status & MAILBOX_FULL) == 0 )
        {
            *sv_mailbox_write = data | channel;
            
            break;
        }
       
    }
}