#pragma once

#include <stdint.h>

#define PCM_BASE                0x20203000

//control status register flags and masks
#define PCM_RAM_STANDBY         0x2000000       //RAM standby ???
#define PCM_CLOCK_SYNC          0x1000000       //help determine when 2 pcm clock cycles have occured
#define PCM_RXSIGN_EXT          0x0800000       //sign extend received data
#define PCM_RX_FULL             0x0400000       //0 - can accept more data, 1 - full
#define PCM_TX_EMPTY            0x0200000       //0 - not empty, 1 - empty
#define PCM_RX_HAS_DATA         0x0100000       //indicates RX FIFO has data
#define PCM_TX_CAN_ACCEPT       0x0080000       //tx fifo can accept data
#define PCM_RX_NEEDS_READ       0x0040000       //rx fifo needs to be read (possible overflow)
#define PCM_TX_NEEDS_WRITE      0x0020000       //tx fifo needs data written (underflow)
#define PCM_RX_ERROR            0x0010000       //rx under/overflow error
#define PCM_TX_ERROR            0x0008000       //tx under/overflow error
#define PCM_RX_SYNC             0x0004000       //rx fifo out of sync
#define PCM_TX_SYNC             0x0002000       //tx fifo out of sync
/*          BITS 10-12 RESERVED                 */
#define PCM_DMA_DREQ_ENABLE     0x0000200       //generate tx/rx dma requests

/* 2 bits.  00 - single sample
            01 - under half full ?? (doc is engrish)
            10 - atleast over half
            11 - full
*/
#define PCM_RX_THRESHOLD        0x0000180       //threshold at which the rx fifo sets needs reading flag

/* 2 bits.  00 - empty
            01 - less than half full
            10 - over half
            11 - full
*/
#define PCM_TX_THRESHOLD        0x0000060       //threshold at which tx fifo needs writing flag is set


#define PCM_RX_FIFO_CLEAR       0x0000010       //clear rx fifo
#define PCM_TX_FIFO_CLEAR       0x0000008       //clear tx fifo
#define PCM_TX_ON               0x0000004       //turn on tx transmission
#define PCM_RX_ON               0x0000002       //turn on rx receiving
#define PCM_ENABLE_AUDIO        0x0000001       //enable the pcm audio device




//mode register flags and masks
#define PCM_CLOCK_DISABLE       0x10000000      //cleanly disable clock
#define PCM_PDM_DECIMATION      0x08000000      //pdm decimation factor 0- 16, 1 - 32
#define PCM_PDM_INPUT_ENABLE    0x04000000      //enable pdm input filter, rx must be on
#define PCM_RX_FRAME_PACKED     0x02000000      //receive frame packed mode
#define PCM_TX_FRAME_PACKED     0x01000000      //transmit frame packed mode
#define PCM_CLOCK_MODE          0x00800000      // 0 -master, 1 - slave
#define PCM_CLOCK_INVERT        0x00400000      // 0 -rising edge, 1 - falling
#define PCM_FRAME_SYNCMODE      0x00200000      // 0 - master, 1 - slave 
#define PCM_FRAME_SYNCINVERT    0x00100000

/*  BITS 10-19 MASK */
#define PCM_FRAME_LENGTH        0x000FFC00      //only used in frame sync master mode

/* BITS 0-9 MASK */
#define PCM_FRAMESYNC_LENGTH    0x000003FF      //only used in frame sync master mode



//T/RXC register flags/masks
#define PCM_TRXC_CHAN1_WEXTEND  0x80000000     
#define PCM_TRXC_CHAN1_ENABLE   0x40000000

/* BITS 20-29 MASK */
#define PCM_TRXC_CHAN1_POS      0x3FF00000  //channel 1 position in bit clocks

/* BITS 16-19 MASK */
#define PCM_TRXC_CHAN1_WIDTH    0x000F0000  //channel 1 width in bit clocks

#define PCM_TRXC_CHAN2_WEXTEND  0x00008000     
#define PCM_TRXC_CHAN2_ENABLE   0x40004000

/* BITS 20-29 MASK */
#define PCM_TRXC_CHAN2_POS      0x00003FF0  //channel 1 position in bit clocks

/* BITS 16-19 MASK */
#define PCM_TRXC_CHAN2_WIDTH    0x0000000F  //channel 1 width in bit clocks



//DREQ register flags/masks
/* BITS 24-30 MASK */
#define PCM_DREQ_TX_PANIC       0x7F000000 //if level drops below this, DMA panic
/* BIT 23 RESERVED */

/* BITS 16-22 MASK */
#define PCM_DREQ_RX_PANIC       0x007F0000 //if level is above, DMA panic

/* BIT 15 RESERVED */

#define PCM_DREQ_TX_REQ_LEVEL   0x00007F00 //asserts DMA request when data level is below level

/* BIT 7 RESERVED */

#define PCM_DREQ_RX_REQ_LEVEL   0x0000007F //asserts DMA request when level is above this 


//interrupt register flags
#define PCM_RX_ERROR_INT        0x8 
#define PCM_TX_ERROR_INT        0x4
#define PCM_RX_READ_INT         0x2 
#define PCM_TX_WRITE_INT        0x1

//interrupt status and clear flags
#define PCM_RX_ERROR_CLR        0x8
#define PCM_TX_ERROR_CLR        0x4
#define PCM_RX_READ_CLR         0x2
#define PCM_TX_WRITE_CLR        0x1

typedef volatile struct
{
    uint32_t reg_ctrl_stat;     //pcm control and status
    uint32_t reg_fifo_data;     //pcm fifo data. 
    uint32_t reg_mode;          //pcm mode
    uint32_t reg_rxc;           //receive config
    uint32_t reg_txc;           //transmit config
    uint32_t reg_dreq;          //pcm DMA request level
    uint32_t reg_inten;         //pcm interrupt enables
    uint32_t reg_intstc;        //pcm interrupt status and clear
    uint32_t reg_gray;          //pcm gray mode control (for receiving)
} PcmRegisterMap_t;

typedef struct
{
    uint32_t    bitspersample;
    uint32_t    channels;
    uint32_t    interleaved;
    uint32_t*   data;
    uint32_t    size;   //in bytes
} PcmFormat_t;

extern PcmRegisterMap_t* get_pcm_reg_map(void);

extern void pcm_init(PcmFormat_t* pcm);
extern void pcm_update(void);