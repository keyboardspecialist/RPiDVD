#pragma once

#include <stdint.h>

#define ARM_TIMER_BASE                  0x2000B400

#define ARM_TIMER_CTRL_23BIT            0x01
#define ARM_TIMER_CTRL_PRESCALE_1       0x00
#define ARM_TIMER_CTRL_PRESCALE_16      0x04
#define ARM_TIMER_CTRL_PRESCALE_256     0x08

#define ARM_TIMER_CTRL_INT_ENABLE       0x20
#define ARM_TIMER_CTRL_INT_DISABLE      0x00

#define ARM_TIMER_CTRL_ENABLE           0x80
#define ARM_TIMER_CTRL_DISABLE          0x00


typedef volatile struct
{
    uint32_t    load;
    uint32_t    value;
    uint32_t    control;
    uint32_t    irq_clear;
    uint32_t    raw_irq;
    uint32_t    masked_irq;
    uint32_t    reload;
    uint32_t    predivider;
    uint32_t    freerunning_counter;
} ArmTimer_t;


extern ArmTimer_t* get_arm_timer(void);