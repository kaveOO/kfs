#pragma once

#include "io.h"

// Forward declaration of interrupt registers (defined where IRQ/ISR code lives)
struct interrupt_registers;

typedef void (*irq_handler_t)(struct interrupt_registers *regs);

// Small IRQ installation API (provided by IRQ/IDT code). We declare it here
// so keyboard can register its handler. A proper IRQ implementation should
// live in a dedicated interrupts/irq source file.
void irq_install_handler(int irq, irq_handler_t handler);

void init_keyboard();
void keyboard_handler(struct interrupt_registers *regs);
// Simple polling loop (fallback) that reads port 0x60 and writes keys to screen.
void keyboard_poll_loop(void);
