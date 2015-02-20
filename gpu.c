
#include "gpu.h"
#include "mailbox.h"

#include "debug.h"




static FrameBufferInfo_t fbi_default 
       __attribute__((aligned (16))) =  {
                                            1024,
                                            768,
                                            1024,
                                            768,
                                            0,
                                            16,
                                            0,
                                            0,
                                            0,
                                            0
                                        };
                                        
                                        
FrameBufferInfo_t*
gpu_init_framebuffer( FrameBufferInfo_t* infos )
{
    FrameBufferInfo_t* fbi_info = (infos == 0) ? &fbi_default : infos;
    
    if( fbi_info->m_phys_width  > 4096 ||
        fbi_info->m_phys_height > 4096 ||
        fbi_info->m_virt_width  > 4096 ||
        fbi_info->m_virt_height > 4096 ||
        fbi_info->m_bitdepth    > 24 )
    {
        return 0;
    }
    
    volatile uint32_t mailbuffer[256] __attribute__((aligned(16)));
    
    uint32_t idx = 1;
    mailbuffer[idx++] = 0;
    
    mailbuffer[idx++] = GPU_SET_PHYS_DIMS;
    mailbuffer[idx++] = 8;
    mailbuffer[idx++] = 8;
    mailbuffer[idx++] = fbi_info->m_phys_width;
    mailbuffer[idx++] = fbi_info->m_phys_height;
    
    mailbuffer[idx++] = GPU_SET_VIRT_DIMS;
    mailbuffer[idx++] = 8;
    mailbuffer[idx++] = 8;
    mailbuffer[idx++] = fbi_info->m_virt_width;
    mailbuffer[idx++] = fbi_info->m_virt_height;
    
    mailbuffer[idx++] = GPU_SET_DEPTH;
    mailbuffer[idx++] = 4;
    mailbuffer[idx++] = 4;
    mailbuffer[idx++] = fbi_info->m_bitdepth;
    
    //we need this request to ensure the changes take affect
    mailbuffer[idx++] = GPU_ALLOC_BUFFER;
    mailbuffer[idx++] = 8;
    mailbuffer[idx++] = 4;
    mailbuffer[idx++] = 16; //alignment
    mailbuffer[idx++] = 0;  //response
    
    mailbuffer[idx++] = 0;  //terminator
    
    mailbuffer[0] = idx * 4; //size in bytes
    
    uint32_t t = 0;
    
    mailbox_write( 8, (uint32_t)mailbuffer );
    mailbox_read ( 8, &t );
    
    if( mailbuffer[1] != 0x80000000 )
        DEBUG_FLASH_BRK();
    
    uint32_t c = 2;
    while((t = mailbuffer[c]))
    {
        if( t == GPU_ALLOC_BUFFER ) //end tag
            break;
            
        c += 3 + (mailbuffer[c+1] >> 2); //skip to next tag
        
        if( c > idx )   //
            DEBUG_FLASH_BRK();
    }
    
    //response val is response size plus MSB set
    if( mailbuffer[c + 2] != 0x80000008 )
        DEBUG_FLASH_BRK();
        
    //alloc response has frame buffer base address and size in bytes
    fbi_info->m_framebuffer = (int32_t*)mailbuffer[c + 3];
    fbi_info->m_size        = mailbuffer[c + 4];
    
    //finally get pixel pitch
    mailbuffer[0] = 7 * 4;
    mailbuffer[1] = 0;
    mailbuffer[2] = GPU_GET_PITCH;
    mailbuffer[3] = 4;
    mailbuffer[4] = 0;
    mailbuffer[5] = 0;
    mailbuffer[6] = 0;
    
    mailbox_write( 8, (uint32_t)mailbuffer );
    mailbox_read ( 8, &t );
    
    
    if( mailbuffer[4] != 0x80000004 )
        DEBUG_FLASH_BRK();
        
    fbi_info->m_pitch = mailbuffer[5];
    
    
    if( fbi_info->m_framebuffer )
        return fbi_info;
    else
        return 0;
}                                        

/*
void
gpu_set_phys_dims( const uint32_t width, const uint32_t height )
{
    volatile uint32_t mailbuffer[
}
*/                       































