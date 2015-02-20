#include "rpi_gpio.h"
#include "gpu.h"
#include "pcm.h"
#include "draw2d.h"
#include "debug.h"


#include "monoimg.h"

static FrameBufferInfo_t fbi1920 __attribute__((aligned (16))) =  {
                                            1920,
                                            1080,
                                            1920,
                                            1080,
                                            0,
                                            24,
                                            0,
                                            0,
                                            0,
                                            0
                                        };

#if 0                                      
extern int _pcm_start;
extern int _pcm_end;    
  
void
do_audio(void)
{
    PcmFormat_t pcm;
    
    pcm.size = (uint32_t)(&_pcm_end - &_pcm_start);
    pcm.data = (uint32_t*)&_pcm_start;
    
    pcm.interleaved = 1;
    pcm.channels = 2;
    pcm.bitspersample = 16;
    
    pcm_init(&pcm);
    while(1)
    {
        pcm_update();
    }
}
#endif         

//you made me do this Broadcom
static uint8_t backbuffer[1920 * 1080 * 3];


//stack overflow gift
static unsigned long x=123456789, y=362436069, z=521288629;

unsigned long xorshf96(void) {          //period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}
                               
void
_kmain( unsigned int r0, unsigned int r1, unsigned int atags )
{

    FrameBufferInfo_t* fbi = &fbi1920;

#if 0    
    do_audio();
#endif
  
    if( !gpu_init_framebuffer( fbi ) )
        DEBUG_FLASH_BRK();

#if 0
    if( (fbi = gpu_init_framebuffer( 0 )) == 0 )
        DEBUG_FLASH_BRK();
#endif    

    init_draw2d_context(fbi, backbuffer);

    RGB_t* clr = (RGB_t*)palette[0];
    uint32_t clr_idx = 0;
    Image_t img;
    
    img.x = xorshf96() % 1400 + 400;
    img.y = xorshf96() % 700 + 200;
    img.w = 200;
    img.h = 200;
    img.data = header_data;
   
    int32_t dx, dy;
    dx = -5;
    dy = -5;
    
    while( 1 )
    {
        clr_and_drawmonoimg(&img, clr);
        
        uint32_t nx, ny;
        nx = img.x + dx;
        ny = img.y + dy;
        if(nx <= 0)
        {
            dx = -dx;
            clr_idx = (clr_idx + 1) % 6;
            clr = (RGB_t*)palette[clr_idx];
        }
        else if(nx >= (fbi->m_phys_width - img.w))
        {
            dx = -dx;
            clr_idx = (clr_idx + 1) % 6;
            clr = (RGB_t*)palette[clr_idx];
        }
        else
        {
            img.x = nx;
        }
        
        if(ny <= 0)
        {
            dy = -dy;
            clr_idx = (clr_idx + 1) % 6;
            clr = (RGB_t*)palette[clr_idx];
        }
        else if(ny >= (fbi->m_phys_height - img.h))
        {
            dy = -dy;
            clr_idx = (clr_idx + 1) % 6;
            clr = (RGB_t*)palette[clr_idx];
        }
        else
        {
            img.y = ny;
        }
    }

    
    while(1)
    {
        /* TRAP */
    }
}

