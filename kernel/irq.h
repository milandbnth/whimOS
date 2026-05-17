#ifndef IRQ_H
#define IRQ_H

#include "idt.h"   // reuses registers_t

// I/O port helpers
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

typedef void (*irq_handler_t)(registers_t *);

void irq_init(void);
void irq_register(int irq, irq_handler_t handler);

#endif