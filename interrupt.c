#include "interrupt.h"


static InterruptController_t* irq_controller = (InterruptController_t*)IRQ_BASE;


InterruptController_t*
get_irq_controller(void)
{
    return irq_controller;
}


__attribute__((naked, aligned(32)))

static void
interrupt_vectors(void)
{
    asm volatile
    (
        "b bad_exception\n" //reset
        "b bad_exception\n" //undef 
        "b interrupt_swi\n"
        "b interrupt_prefetch_abort\n"
        "b interrupt_data_abort\n"
        "b bad_exception\n" //unused
        "b interrupt_irq\n"
        "b bad_exception\n" //ignore FIQ
    );
}


__attribute__((naked))

void
bad_exception(void)
{
    while(1);
}


__attribute__((interrupt ("SWI")))

void
interrupt_swi(void)
{
    register uint32_t address;
    register uint32_t swi;
    
    //read link reg
    asm volatile("mov %0, lr" : "=r" (address));
    
    address -= 4;
    
    //SWI is in lower 24 bits
    swi = *((uint32_t *)address) & 0x00FFFFFF;
    
    //TODO: Everything else
}


__attribute__((interrupt ("IRQ")))

void
interrupt_irq(void)
{
    register uint32_t pending = irq_controller->irq_pending_basic;
    
    if(pending & IRQ_BASIC_ARM_TIMER)
    {
    }
}


__attribute__((interrupt ("ABORT")))

void
interrupt_data_abort(void)
{
    register uint32_t address;
    register uint32_t far;
    
    asm volatile("mov %0, lr" : "=r" (address));
    
    //read fault address register
    asm volatile("mrc p15, 0, %0, c6, c0, 0" : "=r" (far));
    
    //TODO: Output failure and halt
}


__attribute__((interrupt ("ABORT")))

void
interrupt_prefetch_abort(void)
{
    register uint32_t address;
    
    asm volatile("mov %0, lr" : "=r" (address));
    
    //TODO:Output failure and halt
}


void
interrupt_init(void)
{
    asm volatile("mcr p15, 0, %0, c12, c0, 0" : : "r" (&interrupt_vectors));
    asm volatile("cpsie i");
}
























