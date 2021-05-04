#include "leon3_ev_handling.h"
#include "leon3_hw_irqs.h"
#include "leon3_bprint.h"


uint32_t _rdtbr();

asm(".text\n"
"_rdtbr:\n"
"    retl \n"
"    mov %tbr, %o0");


typedef void (*pfunc_t)(void);


#define SPARC_NUM_HW_IRQS 0xF

static pfunc_t hw_irq_handler[SPARC_NUM_HW_IRQS];

//void leon3_sparc_set_trap_handler(uint32_t trap_num, uint32_t handler_routine)
void leon3_sparc_set_trap_handler(uint32_t trap_num, void (* handl_routine) (void))
{
	uint32_t handler_routine=(uint32_t)handl_routine;
    uint32_t * trap_address;
    uint32_t tbr = _rdtbr();

    // This are the instructions we want to code:
    // A1 48 00 00  rd  %psr, %l0
    // 29 00 80 0f  sethi  %hi(handler_routine), %l4
    // 81 c5 21 a0  jmp  %l4 + %lo(handler_routine)
    // a6 10 20 05  mov trap_num, %l3

    trap_address = (uint32_t *) ((tbr & ~0x0fff) | ((uint32_t) trap_num << 4));
    *trap_address = 0xA1480000UL;
    trap_address++;
    *trap_address = (0x29000000UL | (handler_routine >> 10));
    trap_address++;
    *trap_address = (0x81C52000UL | ((handler_routine & ((1 << 10) - 1))));
    trap_address++;
    *trap_address = (0xA6102000UL | (trap_num & 0x1FFF));
}

int32_t leon3_install_handler(uint32_t trap_num, void (* handl_routine) (void))
{
    // do not modify sytem traps
	if ((trap_num < 0x11))
    {
        return LEON3_ERR_TRAP_HANDLER;
    }

    if ((trap_num > 0x1F))
    {
        leon3_sparc_set_trap_handler(trap_num,  handl_routine);
    }
    else
    {
        leon3_sparc_set_trap_handler(trap_num, leon3_sparc_isr);
        hw_irq_handler[trap_num - 0x11] = handl_routine;
    }
    return LEON3_ERR_SUCCESS;
}

void leon3_sparc_irqhandler_entry(uint32_t hw_irq_level)

{

#ifdef VERBOSE_TRAP_HANDLER
	leon3_print_string("hw irq level ");
	leon3_print_uint32(hw_irq_level- 0x10);
	//leon3_print_uint32(hw_irq_level);
	leon3_print_string("\n");
#endif

    if(hw_irq_handler[hw_irq_level - 0x11])
	//if(hw_irq_handler[hw_irq_level])
    {
    	hw_irq_handler[hw_irq_level - 0x11]();
		//hw_irq_handler[hw_irq_level]();
    }
}




