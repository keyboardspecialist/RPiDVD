#include "pcm.h"


static PcmRegisterMap_t*    pcm_register_map = (PcmRegisterMap_t*)PCM_BASE;

static uint32_t*        read_ptr;
static PcmFormat_t*     pcm_fmt;
PcmRegisterMap_t*
get_pcm_reg_map(void)
{
    return pcm_register_map;
}


void
pcm_init(PcmFormat_t* pcm)
{
    if(pcm->data == 0)
        return;
    
    pcm_fmt = pcm;
    
    //turn PCM block on
    pcm_register_map->reg_ctrl_stat |= PCM_ENABLE_AUDIO;    
    
    
    //setup frame and channel settings
    
    if(pcm->channels > 1 && pcm->bitspersample <= 16)
        pcm_register_map->reg_mode |= PCM_TX_FRAME_PACKED;
    
    pcm_register_map->reg_mode |= (PCM_FRAME_LENGTH & ((pcm->bitspersample * pcm->channels) << 8));
    pcm_register_map->reg_mode |= (PCM_FRAMESYNC_LENGTH & (pcm->bitspersample));
    
    pcm_register_map->reg_txc |=  PCM_TRXC_CHAN1_ENABLE;
    pcm_register_map->reg_txc &= ~PCM_TRXC_CHAN1_POS;       
    pcm_register_map->reg_txc |= (PCM_TRXC_CHAN1_WIDTH & (pcm->bitspersample << 24));
    
    
    if(pcm->channels > 1)
    {
        pcm_register_map->reg_txc |=  PCM_TRXC_CHAN2_ENABLE;
        pcm_register_map->reg_txc |= (PCM_TRXC_CHAN2_POS & (pcm->bitspersample << 4));
        pcm_register_map->reg_txc |= (PCM_TRXC_CHAN2_WIDTH & (pcm->bitspersample));
    }
    
    //notify only when FIFO is full
    pcm_register_map->reg_ctrl_stat |= (PCM_TX_THRESHOLD & (3 << 5));
    
    //clear FIFO buffers and set clock sync so we can wait while it does its thing
    pcm_register_map->reg_ctrl_stat = PCM_RX_FIFO_CLEAR 
                                    | PCM_TX_FIFO_CLEAR
                                    | PCM_CLOCK_SYNC;
    
    while(!(pcm_register_map->reg_ctrl_stat & PCM_CLOCK_SYNC))
    {
        /*wait 2 PCM cycles*/;
    }
    
    
    read_ptr = pcm->data;
    //prime TX FIFO
    while((pcm_register_map->reg_ctrl_stat & PCM_TX_CAN_ACCEPT) &&
            (read_ptr - pcm->data) * 4 < pcm->size)
    {
        pcm_register_map->reg_fifo_data = *read_ptr++;
    }
    
    //turn transmission on
    pcm_register_map->reg_ctrl_stat |= PCM_TX_ON;
}


void
pcm_update(void)
{
    while((pcm_register_map->reg_ctrl_stat & PCM_TX_CAN_ACCEPT) /*&&
            (read_ptr - pcm_fmt->data) * 4 < pcm_fmt->size*/)
    {
        pcm_register_map->reg_fifo_data = *read_ptr++;
    }
}
























