.section ".text.startup"

.global _start
.global _get_stack_pointer

_start:

    ldr     sp, =(128 * (1024 * 1024))
    sub     sp, sp, #0x4
    
    b       _cstartup
    
_spin:
    
    b       _spin
    
    
_get_stack_pointer:

	str		sp, [sp]
	ldr		r0, [sp]


	mov		pc, lr
    