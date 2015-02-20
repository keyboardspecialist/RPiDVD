#pragma once

#include <stdint.h>

#define IRQ_BASE    0x2000B200

#define IRQ_BASIC_ARM_TIMER         0x01
#define IRQ_BASIC_ARM_MAILBOX       0x02
#define IRQ_BASIC_ARM_DOORBELL_0    0x04
#define IRQ_BASIC_ARM_DOORBELL_1    0x08
#define IRQ_BASIC_GPU_0_HALTED      0x10
#define IRQ_BASIC_GPU_1_HALTED      0x20
#define IRQ_BASIC_ACCESS_ERROR_1    0x40
#define IRQ_BASIC_ACCESS_ERROR_0    0x80

typedef volatile struct
{
    uint32_t irq_pending_basic;
    uint32_t irq_pending_1;
    uint32_t irq_pending_2;
    uint32_t fiq_control;
    uint32_t enable_irqs_1;
    uint32_t enable_irqs_2;
    uint32_t enable_irqs_basic;
    uint32_t disable_irqs_1;
    uint32_t disable_irqs_2;
    uint32_t disable_irqs_basic;
} InterruptController_t;



extern void interrupt_init(void);
extern InterruptController_t* get_irq_controller(void);