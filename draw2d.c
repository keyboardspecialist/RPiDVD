#include "draw2d.h"


static FrameBufferInfo_t* draw2d_fbi = 0;

static uint8_t*     draw2d_framebuffer = 0;
static uint8_t*     draw2d_backbuffer = 0;
static int32_t      draw2d_pitch = 0;

static Rect_t       draw2d_dirty;
static Rect_t       draw2d_update;
/*
    Pointer and bounds checcking should be done prior to calling these
    Minimizing checks for speed
*/

void
init_draw2d_context(FrameBufferInfo_t* fbi, uint8_t* backbuf)
{
    draw2d_fbi = fbi;
    
    draw2d_framebuffer  = (uint8_t*)(draw2d_fbi->m_framebuffer);
    draw2d_pitch        = draw2d_fbi->m_pitch;
    
    draw2d_backbuffer   = backbuf;
    
    draw2d_dirty.x0 = draw2d_dirty.x1 = draw2d_dirty.y0 = draw2d_dirty.y1 = 0;
    draw2d_update.x0 = draw2d_update.x1 = draw2d_update.y0 = draw2d_update.y1 = 0;
}


void
clr_drect24(void)
{
    uint32_t i,j;

    for(i = draw2d_dirty.y0; i < draw2d_dirty.y1; i++)
    {
        for(j = draw2d_dirty.x0; j < draw2d_dirty.x1; j++)
        {
            draw2d_backbuffer[i * draw2d_pitch + j * 3 + 0] = 0;
            draw2d_backbuffer[i * draw2d_pitch + j * 3 + 1] = 0;
            draw2d_backbuffer[i * draw2d_pitch + j * 3 + 2] = 0;
        }
    }
    
}

void
cpy_rect(Rect_t* to, Rect_t* frm)
{
    to->x0 = frm->x0;
    to->x1 = frm->x1;
    to->y0 = frm->y0;
    to->y1 = frm->y1;
}

void
flip_buffer(void)
{
    
}

/* only update rect area */
void
flip_rect24(void)
{
    uint32_t i, j;
    
    for(i = draw2d_update.y0; i < draw2d_update.y1; i++)
    {
        for(j = draw2d_update.x0; j < draw2d_update.x1; j++)
        {
            draw2d_framebuffer[i * draw2d_pitch + j * 3 + 0] = draw2d_backbuffer[i * draw2d_pitch + j * 3 + 0];
            draw2d_framebuffer[i * draw2d_pitch + j * 3 + 1] = draw2d_backbuffer[i * draw2d_pitch + j * 3 + 1];
            draw2d_framebuffer[i * draw2d_pitch + j * 3 + 2] = draw2d_backbuffer[i * draw2d_pitch + j * 3 + 2];
        }
    }
}

void
clr_and_drawmonoimg(Image_t* img, RGB_t* rgb)
{
    uint32_t dw,dh;
    dw = (draw2d_dirty.x1 - draw2d_dirty.x0);
    dh = (draw2d_dirty.y1 - draw2d_dirty.y0);
    
    if( (dw + dh) > 0 )
    {
        clr_drect24();
        cpy_rect(&draw2d_update, &draw2d_dirty);
    }
    
    uint32_t i,j;
    for(i = 0; i < img->h; i++)
    {
        for(j = 0; j < img->w; j++)
        {
            if(!img->data[i * img->h + j])
                putpx_24(img->x + j, img->y + i, rgb); 
        }
    }
    
    if(img->x < draw2d_update.x0)
        draw2d_update.x0 = img->x;
        
    if(img->y < draw2d_update.y0)
        draw2d_update.y0 = img->y;
        
    if(draw2d_update.x1 < (img->x + img->w))
        draw2d_update.x1 = img->x + img->w;
        
    if(draw2d_update.y1 < (img->y + img->h))
        draw2d_update.y1 = img->y + img->h;
        
    draw2d_dirty.x0 = img->x;
    draw2d_dirty.y0 = img->y;
    draw2d_dirty.x1 = img->x + img->w;
    draw2d_dirty.y1 = img->y + img->h;
    
    flip_rect24();
}

void
putpx_24(uint32_t x, uint32_t y, RGB_t* rgb)
{
    draw2d_backbuffer[ y * draw2d_pitch + x * 3 + 0 ] = rgb->r;
    draw2d_backbuffer[ y * draw2d_pitch + x * 3 + 1 ] = rgb->g;
    draw2d_backbuffer[ y * draw2d_pitch + x * 3 + 2 ] = rgb->b;
}

void
putpx_16(uint32_t x, uint32_t y, uint16_t rgb)
{
}

void
putpx_8(uint32_t x, uint32_t y, uint8_t rgb)
{
}