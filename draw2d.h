#pragma once

#include <stdint.h>

#include "gpu.h"

//seems its BGR not RGB
typedef struct
{
    uint8_t     b;
    uint8_t     g;
    uint8_t     r;
} RGB_t;

typedef struct
{
    uint32_t    x;
    uint32_t    y;
} Point2d;

typedef struct
{
    uint32_t x0;
    uint32_t y0;
    uint32_t x1;
    uint32_t y1;
} Rect_t;

typedef struct
{
    uint32_t    w;
    uint32_t    h;
    uint32_t    x;
    uint32_t    y;
    uint8_t*    data;
} Image_t;

extern void init_draw2d_context(FrameBufferInfo_t* fbi, uint8_t* backbuffer);

extern void flip_buffer(void);

extern void clr_and_drawmonoimg(Image_t* img, RGB_t* rgb);

extern void putpx_24(uint32_t x, uint32_t y, RGB_t* rgb);
extern void putpx_16(uint32_t x, uint32_t y, uint16_t rgb);
extern void putpx_8 (uint32_t x, uint32_t y, uint8_t  rgb);

