#include "types.h"
#include "io.h"

// Forward declare the interrupt registers struct used by handlers
struct interrupt_registers;

// Very small IRQ table stub so keyboard can register handlers.
// A full implementation would setup the IDT and hardware PIC remapping.

typedef void (*irq_handler_t)(struct interrupt_registers *regs);
static irq_handler_t irq_routines[16];

void irq_install_handler(int irq, irq_handler_t handler)
{
    if (irq < 0 || irq >= 16) return;
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    if (irq < 0 || irq >= 16) return;
    irq_routines[irq] = 0;
}

// Called by the assembly IRQ entry with the IRQ number in AL (not yet implemented)
void irq_handler_dispatch(int irq, struct interrupt_registers *regs)
{
    if (irq < 0 || irq >= 16) return;
    if (irq_routines[irq])
        irq_routines[irq](regs);
    // send EOI to master PIC
    outb(0x20, 0x20);
}
