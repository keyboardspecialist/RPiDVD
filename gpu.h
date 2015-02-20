#pragma once 

#include <stdint.h>

//mailbox channel 8 property request codes

#define GPU_ALLOC_BUFFER    0x00040001
#define GPU_FREE_BUFFER     0x00048001

#define GPU_BLANK_SCREEN    0x00040002

#define GPU_GET_PHYS_DIMS   0x00040003
#define GPU_SET_PHYS_DIMS   0x00048003
#define GPU_TEST_PHYS_DIMS  0x00044003

#define GPU_GET_VIRT_DIMS   0x00040004
#define GPU_SET_VIRT_DIMS   0x00048004
#define GPU_TEST_VIRT_DIMS  0x00044004

#define GPU_GET_DEPTH       0x00040005
#define GPU_SET_DEPTH       0x00048005
#define GPU_TEST_DEPTH      0x00044005

#define GPU_GET_PIX_ORDER   0x00040006
#define GPU_SET_PIX_ORDER   0x00048006
#define GPU_TEST_PIX_ORDER  0x00044006

#define GPU_GET_ALPHA_MODE  0x00040007
#define GPU_SET_ALPHA_MODE  0x00048007
#define GPU_TEST_ALPHA_MODE 0x00044007

#define GPU_GET_PITCH       0x00040008

#define GPU_GET_VIRT_OFFS   0x00040009
#define GPU_SET_VIRT_OFFS   0x00048009
#define GPU_TEST_VIRT_OFFS  0x00044009

#define GPU_GET_OVERSCAN    0x0004000A
#define GPU_SET_OVERSCAN    0x0004800A
#define GPU_TEST_OVERSCAN   0x0004400A

#define GPU_GET_PALETTE     0x0004000B
#define GPU_SET_PALETTE     0x0004800B
#define GPU_TEST_PALETTE    0x0004400B

#define GPU_SET_CURSOR_INFO     0x00008011
#define GPU_SET_CURSOR_STATE    0x00008010

typedef struct 
{
    int32_t     m_phys_width;
    int32_t     m_phys_height;
    int32_t     m_virt_width;
    int32_t     m_virt_height;
    int32_t     m_pitch;
    int32_t     m_bitdepth;
    int32_t     m_x_offset;
    int32_t     m_y_offset;
    int32_t*    m_framebuffer;
    int32_t     m_size;
} FrameBufferInfo_t;


extern FrameBufferInfo_t*  gpu_init_framebuffer( FrameBufferInfo_t* infos );
/*
extern void gpu_set_phys_dims( const uint32_t width, const uint32_t height );
extern void gpu_get_phys_dims( uint32_t* width, uint32_t* height );
extern void gpu_test_phys_dims( uint32_t width, uint32_t height, uint32_t* result );
*/
